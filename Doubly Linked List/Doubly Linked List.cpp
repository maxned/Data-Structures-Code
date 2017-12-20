
#include <iostream>
#include <fstream>

using namespace std;

struct node {
	int item;
	node *next;
	node *prev;
};

node* deleteCurrentNode(node *nodeToDelete);

int main()
{
	node *list = nullptr;

	ifstream input;
	input.open("input.txt");

	int value;

	while (input >> value)
	{
		node *newNode = new node;
		newNode->item = value;
		newNode->next = NULL;

		if (!list) {
			newNode->prev = NULL;
			list = newNode;
		} else {

			node *current = list;
			while (current->next != NULL) {
				current = current->next;
			}

			newNode->prev = current;
			current->next = newNode;
		}
	}

	input.close();


	cout << "Which item do you want to delete from the beginning?" << endl;
	cin >> value;

	// make the first item in list be the item to be deleted
	for (int i = value; i > 1; i--) {
		list = list->next;
	}

	list = deleteCurrentNode(list);


	cout << "Which item do you want to delete from the end?" << endl;
	cin >> value;

	// move list to tail
	while (list->next != NULL) {
		list = list->next;
	}

	for (int i = value; i > 1; i--) {
		list = list->prev;
	}

	list = deleteCurrentNode(list);


	// move list to head
	while (list->prev != NULL) {
		list = list->prev;
	}

	ofstream output;
	output.open("output.txt");

	while (list != NULL) {
		output << list->item << " ";
		list = list->next;
	}

	output.close();

	return 0;
}

node* deleteCurrentNode(node *nodeToDelete)
{
	node *nextNode = nodeToDelete->next;
	node *previousNode = nodeToDelete->prev;

	if (previousNode && previousNode->next) previousNode->next = nextNode;
	if (nextNode && nextNode->prev) nextNode->prev = previousNode;

	delete nodeToDelete;

	if (nextNode != NULL) {
		return nextNode;
	} else {
		return previousNode;
	}
}
