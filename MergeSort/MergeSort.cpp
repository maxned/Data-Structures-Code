
#include <iostream>

using namespace std;

struct node {
	int item;
	node *next;
	node *prev;
};

#define ArraySize 10
int unsortedArray[ArraySize] = { 5, 382, 6, 95, 4, 8, 39, 0, 21, 45 };

node* mergeSort(node *head);
void split(node *head, node *&a, node *&b);
node* merge(node *a, node *b);
void initLinkedList(node *&head, int *array, int arraySize);
void pop(struct node *&top);
void enqueue(int item, struct node *&front);
void displayList(node *list);

int main()
{
	node *unsortedList = nullptr;
	initLinkedList(unsortedList, unsortedArray, ArraySize);

	cout << "Unsorted List:" << endl;
	displayList(unsortedList);

	node *sortedList = mergeSort(unsortedList);

	cout << "Sorted List: " << endl;
	displayList(sortedList);

	return 0;
}

node* mergeSort(node *head)
{
	if (!head)
		return NULL;

	if (!head->next)
		return head;

	node *a, *b;

	split(head, a, b);

	a = mergeSort(a);
	b = mergeSort(b);

	return merge(a, b);
}

void split(node *head, node *&a, node *&b)
{
	int nodeCount = 0;

	node *current = head;
	while (current) {
		nodeCount++;
		current = current->next;
	}

	nodeCount /= 2;

	a = head;

	for (int i = 0; i < nodeCount; i++) {
		head = head->next;
	}

	b = head;

	head->prev->next = NULL;
	head->prev = NULL;
}

node* merge(node *a, node *b)
{
	node *merged = nullptr;

	while (a && b) {
		if (a->item > b->item) {
			enqueue(b->item, merged);
			pop(b);
		} else {
			enqueue(a->item, merged);
			pop(a);
		}
	}

	while (a) {
		enqueue(a->item, merged);
		pop(a);
	}

	while (b) {
		enqueue(b->item, merged);
		pop(b);
	}

	return merged;
}

void initLinkedList(node *&head, int *array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		node *newNode = new node;
		newNode->item = array[i];
		newNode->next = NULL;

		if (!head) {
			newNode->prev = NULL;
			head = newNode;

		} else {

			node *current = head;
			while (current->next) {
				current = current->next;
			}

			newNode->prev = current;
			current->next = newNode;
		}
	}
}

void pop(struct node *&top)
{
	struct node *temp;
	if (top) {
		temp = top;
		top = top->next;
		if (top) top->prev = NULL;
		delete temp;
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

		newNode->prev = current;
		current->next = newNode;

	} else {
		newNode->prev = NULL;
		front = newNode;
	}
}

void displayList(node *list)
{
	node *current = list;

	while (current) {
		cout << current->item << (current->next ? ", " : "");
		current = current->next;
	}

	cout << endl << endl;
}
