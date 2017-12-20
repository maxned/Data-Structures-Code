
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct BinaryTree {
	int item = 0;
	BinaryTree *left = nullptr;
	BinaryTree *right = nullptr;
};

struct queue {
	BinaryTree *leaf;
	queue *next;
};

void insertSorted(int numbers[], int start, int end, BinaryTree *&root);
void insertUnsorted(int array[], int i, int maxCount, BinaryTree *&root);
void arrayFromTree(BinaryTree *root, int array[], int i);
int maxDepth(BinaryTree *node);

void displayArray(int array[], int start, int end);
void inOrder(BinaryTree *root);
void displayBreadth(BinaryTree *root);
void enqueue(BinaryTree *leaf, queue *&front);
void dequeue(queue *&front);

int main()
{
	ifstream input;
	input.open("input.txt");

	int item;
	int numbers[10];
	int count = 0;
	BinaryTree *root = nullptr;

	for (int i = 0; input >> item; i++) {
		numbers[i] = item;
		count = i;
	}

	input.close();

	cout << "The original array looks like this: ";
	displayArray(numbers, 0, count);
	cout << endl << endl;

	insertSorted(numbers, 0, count, root);

	cout << "The binary tree looks like this in breadth level format: " << endl;
	displayBreadth(root);
	cout << endl;

	int depth = maxDepth(root);
	int sizeOfArray = pow(2, depth + 1) - 1;
	int *unsortedNumbers = new int[sizeOfArray];
	int i = 0;
	arrayFromTree(root, unsortedNumbers, i);

	cout << "The unsorted array looks like this: ";
	displayArray(unsortedNumbers, 0, sizeOfArray - 1);
	cout << endl << endl;

	BinaryTree *newRoot = nullptr;
	insertUnsorted(unsortedNumbers, i, sizeOfArray, newRoot);

	cout << "The binary tree from the unsorted array looks like this in breadth level format: " << endl;
	displayBreadth(newRoot);
	cout << endl;

	cout << "The above binary tree in in-order format: ";
	inOrder(newRoot);
	cout << endl << endl;

	return 0;
}

void insertSorted(int numbers[], int start, int end, BinaryTree *&root)
{
	int middle = (start + end) / 2;

	if (start > end)
		return;

	root = new BinaryTree;
	root->item = numbers[middle];

	insertSorted(numbers, start, middle - 1, root->left);
	insertSorted(numbers, middle + 1, end, root->right);
}

void insertUnsorted(int array[], int i, int maxCount, BinaryTree *&root)
{
	if ((2*i + 2) < maxCount)
	{
		if (!root && array[i] != 0) {
			root = new BinaryTree;
			root->item = array[i];
		}

		if (root && !root->left && array[2*i + 1] != 0) {
			root->left = new BinaryTree;
			root->left->item = array[2*i + 1];
		}

		if (root && !root->right && array[2*i + 2] != 0) {
			root->right = new BinaryTree;
			root->right->item = array[2*i + 2];
		}

		insertUnsorted(array, 2*i + 1, maxCount, root->left);
		insertUnsorted(array, 2*i + 2, maxCount, root->right);
	}
}

void arrayFromTree(BinaryTree *root, int array[], int i)
{
	if (root)
	{
		array[i] = root->item;
		array[2*i + 1] = (!root->left) ? 0 : root->left->item;
		array[2*i + 2] = (!root->right) ? 0 : root->right->item;

		arrayFromTree(root->left, array, 2*i + 1);
		arrayFromTree(root->right, array, 2*i + 2);
	}
}

int maxDepth(BinaryTree *node)
{
	if (!node)
		return -1;

	int LDepth = maxDepth(node->left);
	int RDepth = maxDepth(node->right);

	if (LDepth > RDepth)
		return LDepth + 1;
	else
		return RDepth + 1;
}

#pragma mark - Displaying

void displayArray(int array[], int start, int end)
{
	for (int i = start; i < end + 1; i++) {
		cout << array[i] << ((i == end) ? "" : ", ");
	}
}

void inOrder(BinaryTree *root)
{
	if (root) {
		inOrder(root->left);
		cout << root->item << " ";
		inOrder(root->right);
	}
}

void displayBreadth(BinaryTree *root)
{
	queue *currentLevel = nullptr;
	queue *nextLevel = nullptr;

	enqueue(root, currentLevel);

	while (currentLevel)
	{
		BinaryTree *root = currentLevel->leaf;
		cout << root->item << " ";
		dequeue(currentLevel);

		if (root->left)
			enqueue(root->left, nextLevel);

		if (root->right)
			enqueue(root->right, nextLevel);

		if (!currentLevel) {
			currentLevel = nextLevel;
			nextLevel = nullptr;
			cout << endl;
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
