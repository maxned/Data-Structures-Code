
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct node {
	char name[30] = { '\0' };
	node *next = nullptr;
};

struct BinaryTree {
	char name[30] = { '\0' };
	node *names = nullptr;
	BinaryTree *left = nullptr;
	BinaryTree *right = nullptr;
};

BinaryTree* searchTree(BinaryTree *leaf, char *key, node *&searchPath);
void addDuplicateName(BinaryTree *foundLeaf, char *name);
void insert(BinaryTree *&leaf, char *name);

int main()
{
	ifstream input;
	input.open("input.txt");

	BinaryTree *root = nullptr;
	node *nullNode = nullptr;

	char name[30];

	while (input >> name)
	{
		BinaryTree *foundLeaf = searchTree(root, name, nullNode);

		if (foundLeaf) {
			addDuplicateName(foundLeaf, name);
		} else {
			insert(root, name);
		}
	}

	input.close();

	cout << "Enter the name that you want to search for (case insensitive): " << endl;
	cin >> name;

	node *searchPath = new node;
	BinaryTree *foundName = searchTree(root, name, searchPath);
	if (foundName) {
		cout << endl << "Congratulations! The name you searched for was found." << endl;

		cout << "The search path consisted of the following: ";
		while (searchPath) {
			cout << searchPath->name << ((searchPath->next) ? ", " : "");
			searchPath = searchPath->next;
		}

		cout << endl;

		node *duplicates = foundName->names;
		int count = 0;
		while (duplicates) {
			duplicates = duplicates->next;
			count++;
		}

		cout << "The name has " << count << ((count == 1) ? " duplicate " :" duplicates ") << "and " << count + 1 << ((count + 1 == 1) ? " total iteration." :" total iterations.") << endl << endl;

	} else {
		cout << "The name \"" << name << "\" was not found. Sorry!" << endl;
	}

	return 0;
}

BinaryTree* searchTree(BinaryTree *leaf, char *key, node *&searchPath)
{
	BinaryTree *found = nullptr;
	if (leaf != NULL)
	{
		if (searchPath)
		{
			if (searchPath->name[0] == '\0') {
				strcpy(searchPath->name, leaf->name);
			} else {
				node *current = searchPath;
				while (current->next)
					current = current->next;

				node *newNode = new node;
				strcpy(newNode->name, leaf->name);
				current->next = newNode;
			}
		}

		if (strcasecmp(key, leaf->name) == 0)
			found = leaf;
		else if (strcasecmp(key, leaf->name) < 0)
			found = searchTree(leaf->right, key, searchPath);
		else
			found = searchTree(leaf->left, key, searchPath);
	}

	return found;
}

void addDuplicateName(BinaryTree *foundLeaf, char *name)
{
	node *duplicateNameNode = new node;
	strcpy(duplicateNameNode->name, name);

	node *currentDuplicateNameNode = foundLeaf->names;

	if (!currentDuplicateNameNode) {
		foundLeaf->names = duplicateNameNode;
	} else {
		while (currentDuplicateNameNode->next)
			currentDuplicateNameNode = currentDuplicateNameNode->next;

		currentDuplicateNameNode->next = duplicateNameNode;
	}
}

void insert(BinaryTree *&leaf, char *name)
{
	if (leaf == NULL) {
		leaf = new BinaryTree;
		strcpy(leaf->name, name);
	} else if ((strcasecmp(name, leaf->name) < 0))
		insert(leaf->right, name);
	else
		insert(leaf->left, name);
}
