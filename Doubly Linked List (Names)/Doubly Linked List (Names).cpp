
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct node {
	char name[99];
	node *next;
	node *prev;
};

node* deleteCurrentNode(node *nodeToDelete);

int main()
{
	node *list = nullptr;

	ifstream input;
	input.open("input.txt");

	char name[99];
	bool deleteNode = false;

	while (input >> name)
	{
		if (!strcmp("delete", name)) {	// delete keyword
			deleteNode = true;

		} else if (deleteNode) {		// right after delete keyword (delete the node with this name

			// move list to point to the head just in case
			while (list && list->prev != NULL) {
				list = list->prev;
			}

			bool nameFound = true;

			while (list && strcmp(list->name, name) != 0) {
				list = list->next;

				if (list && !list->next && strcmp(list->name, name) != 0) {
					nameFound = false;
					break;
				}
			}

			if (list && nameFound)
				list = deleteCurrentNode(list);

			deleteNode = false;

		} else {

			node *newNode = new node;
			strcpy(newNode->name, name);

			if (!list) {
				newNode->prev = NULL;
				newNode->next = NULL;
				list = newNode;

			} else {

				// move list to head
				while (list->prev != NULL) {
					list = list->prev;
				}
				node *head = list;

				// move list to tail
				node *tail = list;
				while (tail->next != NULL) {
					tail = tail->next;
				}


				if (strcmp(newNode->name, head->name) < 0) {

					newNode->prev = NULL;
					newNode->next = head;
					head->prev = newNode;

				} else if (strcmp(newNode->name, tail->name) > 0) {

					newNode->prev = tail;
					newNode->next = NULL;
					tail->next = newNode;

				} else {

					node *current = head;

					// we want the previous name to be < 0 and the next name to be > 0
					// check if the current name is < 0 and the next is >= 0 then add the new node right after the current one

					while (!(strcmp(current->name, newNode->name) < 0 && strcmp(current->next->name, newNode->name) >= 0)) {
						current = current->next;
					}

					newNode->prev = current;
					newNode->next = current->next;
					current->next->prev = newNode;
					current->next = newNode;
				}
			}
		}
	}

	input.close();

	ofstream output;
	output.open("output.txt");

	// move list to head
	while (list && list->prev != NULL) {
		list = list->prev;
	}

	node *current = list;
	while (current != NULL) {
		output << current->name << endl;
		current = current->next;
	}

	output << "----------" << endl;

	// move list to tail
	while (list && list->next != NULL) {
		list = list->next;
	}

	current = list;
	while (current != NULL) {
		output << current->name << endl;
		current = current->prev;
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
