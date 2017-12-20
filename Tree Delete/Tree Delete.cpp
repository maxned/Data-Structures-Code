
#include <iostream>
#include <fstream>

using namespace std;

struct BinaryTree {
	int value = 0;
	BinaryTree *left = nullptr;
	BinaryTree *right = nullptr;
};

struct queue {
	BinaryTree *leaf;
	queue *next;
};

void insert(BinaryTree *&root, int value);
BinaryTree* searchTree(BinaryTree *root, int key);
BinaryTree* deleteNode(BinaryTree *root, int value);
BinaryTree* minValueNode(BinaryTree *node);

void preOrder(BinaryTree *root, ofstream *out);
void inOrder(BinaryTree *root, ofstream *out);
void postOrder(BinaryTree *root, ofstream *out);

void displayBreadth(BinaryTree *root, ofstream *out);
void enqueue(BinaryTree *leaf, queue *&front);
void dequeue(queue *&front);

int main()
{
	ifstream input;
	input.open("input.txt");

	BinaryTree *tree = nullptr;
	char inputValue[10];
	int value;

	while (input >> inputValue)
	{
		if (strcmp(inputValue, "delete") == 0) {
			input >> value;
		} else {
			value = atoi(inputValue);
		}

		// doesn't hurt to search without the delete keyword because guaranteed not to have duplicates
		// if not found then add a new node
		BinaryTree *foundNum = searchTree(tree, value);
		if (foundNum) {
			tree = deleteNode(tree, value);
		} else {
			insert(tree, value);
		}
	}

	input.close();

	ofstream output;
	output.open("output.txt");

	output << "Pre Order Tree: ";
	preOrder(tree, &output);
	output << endl << endl;

	output << "In Order Tree: ";
	inOrder(tree, &output);
	output << endl << endl;

	output << "Post Order Tree: ";
	postOrder(tree, &output);
	output << endl << endl;

	output << "Breadth Search Format: ";
	displayBreadth(tree, &output);
	output << endl << endl;

	output.close();

	return 0;
}

void insert(BinaryTree *&root, int value)
{
	if (root == NULL) {
		root = new BinaryTree;
		root->value = value;
	} else if (value < root->value)
		insert(root->left, value);
	else
		insert(root->right, value);
}

BinaryTree* searchTree(BinaryTree *root, int key)
{
	BinaryTree *found = nullptr;
	if (root != NULL)
	{
		if (key == root->value)
			found = root;
		else if (key < root->value)
			found = searchTree(root->left, key);
		else
			found = searchTree(root->right, key);
	}

	return found;
}

BinaryTree* deleteNode(BinaryTree *root, int value)
{
	if (!root) return root;

	if (value < root->value) {
		root->left = deleteNode(root->left, value);

	} else if (value > root->value) {
		root->right = deleteNode(root->right, value);

	} else {

		if (!root->left) {
			BinaryTree *temp = root->right;
			delete root;
			return temp;

		} else if (!root->right) {
			BinaryTree *temp = root->left;
			delete root;
			return temp;
		}

		BinaryTree *temp = minValueNode(root->right);
		root->value = temp->value;
		root->right = deleteNode(root->right, temp->value);
	}

	return root;
}

BinaryTree* minValueNode(BinaryTree *node)
{
	BinaryTree *current = node;

	while (current->left)
		current = current->left;

	return current;
}

void preOrder(BinaryTree *root, ofstream *out)
{
	if (root) {
		*out << root->value << " ";
		preOrder(root->left, out);
		preOrder(root->right, out);
	}
}

void inOrder(BinaryTree *root, ofstream *out)
{
	if (root) {
		inOrder(root->left, out);
		*out << root->value << " ";
		inOrder(root->right, out);
	}
}

void postOrder(BinaryTree *root, ofstream *out)
{
	if (root) {
		postOrder(root->left, out);
		postOrder(root->right, out);
		*out << root->value << " ";
	}
}

void displayBreadth(BinaryTree *root, ofstream *out)
{
	queue *currentLevel = nullptr;
	queue *nextLevel = nullptr;

	enqueue(root, currentLevel);

	while (currentLevel)
	{
		BinaryTree *root = currentLevel->leaf;
		*out << root->item << " ";
		dequeue(currentLevel);

		if (root->left)
			enqueue(root->left, nextLevel);

		if (root->right)
			enqueue(root->right, nextLevel);

		if (!currentLevel) {
			currentLevel = nextLevel;
			nextLevel = nullptr;
			*out << endl;
		}
	}
}

void enqueue(BinaryTree *leaf, queue *&front)
{
	struct queue *newNode = new queue;

	newNode->leaf = leaf;
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
