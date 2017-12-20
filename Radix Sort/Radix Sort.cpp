
#include <iostream>

using namespace std;

struct node {
	int item;
	node *next;
};

void radixSortAscending(int *&unsortedArray, node **&arrayWithQueues);
void radixSortDescending(int *&unsortedArray, node **&arrayWithStacks);
void displayArray(int *array);
void resetArray(int *&array);
void queueStackUpArray(node **&array);
void enqueue(int item, struct node *&front);
void dequeue(struct node *&front);
void push(int item, struct node *&top);
void pop(struct node *&top);

int main()
{
	int *unsortedArray = nullptr;
	resetArray(unsortedArray);

	cout << "Original Array: ";
	displayArray(unsortedArray);

	node **arrayWithQueueStacks = nullptr;
	queueStackUpArray(arrayWithQueueStacks);

	radixSortAscending(unsortedArray, arrayWithQueueStacks);

	cout << "Sorted Ascending Array: ";
	displayArray(unsortedArray);

	resetArray(unsortedArray);
	radixSortDescending(unsortedArray, arrayWithQueueStacks);

	cout << "Sorted Descending Array: ";
	displayArray(unsortedArray);

	return 0;
}

void radixSortAscending(int *&unsortedArray, node **&arrayWithQueues)
{
	// find largest integer in the unsorted array
	int maxInt = 0;
	for (int i = 0; i < 11; i++) {
		if (maxInt < unsortedArray[i]) maxInt = unsortedArray[i];
	}

	int M = 10;
	int N = 1;

	while (N <= maxInt)
	{
		// sort objects by the digit
		for (int i = 0; i < 11; i++) {
			int digit = unsortedArray[i] % M;
			digit /= N;
			enqueue(unsortedArray[i], arrayWithQueues[digit]);
		}

		int count = 0;
		for (int i = 0; i < 10; i++) {

			while (arrayWithQueues[i]) {
				unsortedArray[count] = arrayWithQueues[i]->item;
				dequeue(arrayWithQueues[i]);
				count++;
			}
		}

		M *= 10;
		N *= 10;
	}
}

void radixSortDescending(int *&unsortedArray, node **&arrayWithStacks)
{
	// find largest integer in the unsorted array
	int maxInt = 0;
	for (int i = 0; i < 11; i++) {
		if (maxInt < unsortedArray[i]) maxInt = unsortedArray[i];
	}

	int M = 10;
	int N = 1;

	while (N <= maxInt)
	{
		// sort objects by the digit
		for (int i = 0; i < 11; i++) {
			int digit = unsortedArray[i] % M;
			digit /= N;
			enqueue(unsortedArray[i], arrayWithStacks[digit]);
		}

		int count = 0;
		for (int i = 9; i >= 0; i--) {

			while (arrayWithStacks[i]) {
				unsortedArray[count] = arrayWithStacks[i]->item;
				pop(arrayWithStacks[i]);
				count++;
			}
		}

		M *= 10;
		N *= 10;
	}
}

void displayArray(int *array)
{
	for (int i = 0; i < 11; i++) {
		cout << array[i] << (i == 10 ? "\n" : ", ");
	}

	cout << endl;
}

void resetArray(int *&array)
{
	int OGArray[11] = { 94, 191, 845, 52, 1, 1934, 0, 32, 193, 8410, 8 };

	if (array) delete [] array;
	array = new int[11];

	for (int i = 0; i < 11; i++) {
		array[i] = OGArray[i];
	}
}

void queueStackUpArray(node **&array)
{
	if (array) {
		for (int i = 0; i < 10; i++) {
			delete array[i];
		}

		delete [] array;
	}

	array = new node*[10];

	for (int i = 0; i < 10; i++) {
		node *queue = NULL;
		array[i] = queue;
	}
}

void enqueue(int item, struct node *&front)
{
	struct node *newNode = new node;

	newNode->item = item;
	newNode->next = NULL;
	if (front) {

		node *current = front;
		while (current->next)
			current = current->next;

		current->next = newNode;

	} else {
		front = newNode;
	}
}

void dequeue(struct node *&front)
{
	struct node *temp;

	if (front) {
		temp = front;
		front = front->next;
		delete temp;
	}
}

void push(int item, struct node *&top)
{
	struct node *newNode = new node;

	newNode->item = item;
	newNode->next = top;
	top = newNode;
}

void pop(struct node *&top)
{
	struct node *temp;
	if (top) {
		temp = top;
		top = top->next;
		delete temp;
	}
}
