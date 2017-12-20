
#include <iostream>
#include <fstream>

using namespace std;

struct queue {
	int item;
	queue *next;
};

void insert(int *array, int item, int &count);
void remove(int *array, int &count);
void siftUp(int *array, int childIndex);
void siftDown(int *array, int parentIndex, int count);

void displayBreadth(int *array, int count);
void enqueue(int item, queue *&front);
void dequeue(queue *&front);

int main()
{
	ifstream input;
	input.open("input.txt");

	int item;
	int numbers[10];
	int count = 0;

	for (int i = 0; input >> item; i++) {
		insert(numbers, item, count);
	}

	input.close();

	displayBreadth(numbers, count);

	for (int i = 0; i < 5; i++)
	{
		cout << endl;
		remove(numbers, count);
		displayBreadth(numbers, count);
	}

	return 0;
}

void insert(int *array, int item, int &count)
{
	array[count] = item;
	siftUp(array, count);
	count++;
}

void siftUp(int *array, int childIndex)
{
	if (childIndex <= 0) return;

	int parentIndex = (childIndex - 1) / 2;
	int parent = array[parentIndex];
	int child = array[childIndex];

	if (parent > child) {
		array[parentIndex] = child;
		array[childIndex] = parent;

		siftUp(array, parentIndex);
	}
}

void remove(int *array, int &count)
{
	if (count == 0) return;

	array[0] = array[count - 1];
	count--;

	siftDown(array, 0, count);
}

void siftDown(int *array, int parentIndex, int count)
{
	if (parentIndex >= count) return;

	int parent = array[parentIndex];

	int leftChild = 0;
	int rightChild = 0;

	bool leftChildExists = false;
	bool rightChildExists = false;

	if (2*parentIndex + 1 < count) {
		leftChild = array[2*parentIndex + 1];
		leftChildExists = true;
	}

	if (2*parentIndex + 2 < count) {
		rightChild = array[2*parentIndex + 2];
		rightChildExists = true;
	}


	if ((leftChildExists && parent > leftChild) || (rightChildExists && parent > rightChild)) {

		int nextChildIndex = 0;

		if (leftChildExists && rightChildExists) {

			if (leftChild < rightChild) {
				array[parentIndex] = leftChild;
				array[2*parentIndex + 1] = parent;
				nextChildIndex = 2*parentIndex + 1;
			} else {
				array[parentIndex] = rightChild;
				array[2*parentIndex + 2] = parent;
				nextChildIndex = 2*parentIndex + 2;
			}

		} else if (leftChildExists) {

			array[parentIndex] = leftChild;
			array[2*parentIndex + 1] = parent;
			nextChildIndex = 2*parentIndex + 1;

		} else if (rightChildExists) {

			array[parentIndex] = rightChild;
			array[2*parentIndex + 2] = parent;
			nextChildIndex = 2*parentIndex + 2;
		}

		siftDown(array, nextChildIndex, count);
	}
}

#pragma mark - Displaying

void displayBreadth(int *array, int count)
{
	if (count == 0) return;

	queue *currentLevel = nullptr;
	queue *nextLevel = nullptr;

	enqueue(array[0], currentLevel);

	int i = 0;
	while (currentLevel)
	{
		cout << currentLevel->item << " ";
		dequeue(currentLevel);

		if (2*i + 1 < count)
			enqueue(array[2*i + 1], nextLevel);

		if (2*i + 2 < count)
			enqueue(array[2*i + 2], nextLevel);

		if (!currentLevel) {
			currentLevel = nextLevel;
			nextLevel = nullptr;
			cout << endl;
		}

		i++;
	}
}

void enqueue(int item, queue *&front)
{
	struct queue *newNode = new queue;

	newNode->item = item;
	newNode->next = NULL;

	if (front) {

		queue *current = front;
		while (current->next)
			current = current->next;

		current->next = newNode;

	} else {
		front = newNode;
	}
}

void dequeue(queue *&front)
{
	struct queue *temp;

	if (front) {
		temp = front;
		front = front->next;
		delete temp;
	}
}
