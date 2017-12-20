
#include <iostream>
#include <fstream>

using namespace std;

struct node {
	int item;
	node *next;
};

void enqueue(int item, struct node *&front, struct node *&rear);
void dequeue(struct node *&front, struct node *&rear);
void traverse(node *front);

int main()
{
	ifstream input;
	input.open("input.txt");

	int number;
	node *front = NULL;
	node *rear = NULL;

	while (input >> number) {
		enqueue(number, front, rear);
	}

	// remove negative numbers from the front of the line until we get to the first positive number
	while (!(front->item >= 0)) dequeue(front, rear);

	// store location of first positive number
	int *firstPositiveNumber = &(front->item);

	dequeue(front, rear);
	enqueue(*firstPositiveNumber, front, rear);

	while (&(front->item) != firstPositiveNumber) {
		if (front->item >= 0) enqueue(front->item, front, rear);
		dequeue(front, rear);
	}

	input.close();

	traverse(front);

	return 0;
}

void enqueue(int item, struct node *&front, struct node *&rear)
{
	struct node *newNode = new node;

	newNode->item = item;
	newNode->next = NULL;
	if (rear) {
		rear->next = newNode;
		rear = newNode;
	} else {
		front = rear = newNode;
	}
}

void dequeue(struct node *&front, struct node *&rear)
{
	struct node *temp;

	if (front) {
		temp = front;
		front = front->next;
		delete temp;
		if (!front)
			rear = NULL;
	}
}

void traverse(node *front)
{
	node *current = front;

	do {
		cout << current->item << endl;
		current = current->next;
	} while (current);
}
