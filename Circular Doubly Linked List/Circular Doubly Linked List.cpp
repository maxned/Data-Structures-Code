
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {
	char name[99];
	node *next;
	node *prev;
};

int main()
{
	node *listHead = nullptr;

	ifstream input;
	input.open("input.txt");

	char *name = new char[99];
	int numberOfNodes = 0;

	while (input >> name)
	{
		node *newNode = new node;
		strcpy(newNode->name, name);

		if (!listHead) {

			newNode->prev = newNode;
			newNode->next = newNode;
			listHead = newNode;

		} else {

			newNode->prev = listHead->prev;
			newNode->next = listHead;

			listHead->prev = newNode;
			newNode->prev->next = newNode;

			listHead = newNode;
		}

		numberOfNodes++;
	}

	input.close();


	int numberOfNodesToDelete;

	while (numberOfNodes) {
		if (numberOfNodes > 1) {
			cout << "There are " << numberOfNodes << " items left in the list. How many would you like to delete?" << endl;
		} else {
			cout << "There is one item left in the list. Enter 1 to delete it." << endl;
		}

		cin >> numberOfNodesToDelete;

		for (int i = 0; i < numberOfNodesToDelete; i++) {

			if (listHead->next == listHead && listHead->prev == listHead) { // one item left
				delete listHead;
			} else {

				node *nextNode = listHead->next;

				listHead->next = listHead->next->next;
				listHead->next->prev = listHead;

				delete nextNode;
			}


			numberOfNodes--;
		}
	}

	cout << "You have deleted all of the available nodes. Bye bye." << endl;


	return 0;
}
