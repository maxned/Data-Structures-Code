
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct node
{
	char name[30];
	node *next;
};

node* populateList(node *head, char *data);
void split(node *head, int count);
void merge(node *list1, node *list2);
void traverse(node *list1, node *list2);

node *myList;
node *myList2;
node *myList3;
node *myList4;

int main()
{
	ifstream input;
	input.open("inputSplit.txt");

	char name[30];

	// make a linked list (myList) from the names in inputSplit.txt
	int count = 0;
	while (input >> name)
	{
		myList = populateList(myList, name);
		count++;
	}

	split(myList, count);
	traverse(myList, myList2);
	input.close();
	input.clear();

	input.open("inputMerge.txt");

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {

			input >> name;
			if (i == 0) {
				myList3 = populateList(myList3, name);
			} else {
				myList4 = populateList(myList4, name);
			}
		}
	}

	merge(myList3, myList4);
	traverse(myList3, NULL);

	input.close();

	return 0;
}

node* populateList(node *head, char *data)
{
	node *current = head;

	while (current != NULL && current->next != NULL) {
		current = current->next;
	}

	node *newNode = new node;
	strncpy(newNode->name, data, 30);
	newNode->next = NULL;

	if (head == NULL) {
		head = newNode;
	} else {
		current->next = newNode;
	}

	return head;
}

void split(node *head, int count)
{
	int number = count / 2;
	node *current = head;

	// get second half of linked list
	while (number > 0) {
		current = current->next;
		number--;
	}

	myList2 = current;

	// get first half of linked list
	number = count / 2;
	current = head;
	while (number > 1) {
		current = current->next;
		number--;
	}
	current->next = NULL;
}

void merge(node *list1, node *list2)
{
	node *current = list1;
	while (current->next != NULL) {
		current = current->next;
	}

	current->next = list2;
}

void traverse(node *list1, node *list2)
{
	ofstream output;

	if (list1 && list2) {
		output.open("outputSplit.txt");
	} else {
		output.open("outputMerge.txt");
	}

	node *current = list1;
	while (current != NULL) {
		output << current->name << endl;
		current = current->next;
	}

	current = list2;
	while (current != NULL) {
		output << current->name << endl;
		current = current->next;
	}

	output.close();
}
