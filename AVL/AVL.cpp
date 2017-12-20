
#include <iostream>
#include <fstream>

using namespace std;

struct BinaryTree {
	int item;
	int height = 0;
	BinaryTree *left = nullptr;
	BinaryTree *right = nullptr;
};

struct queue {
	BinaryTree *leaf;
	queue *next;
};

BinaryTree* insert(BinaryTree *node, int key);
BinaryTree* rebalance(BinaryTree *node);
BinaryTree* leftRotate(BinaryTree *x);
BinaryTree* rightRotate(BinaryTree *x);
int getBalance(BinaryTree *node);
int height(BinaryTree *node);

void displayBreadth(BinaryTree *root, ofstream *out);
void enqueue(BinaryTree *leaf, queue *&front);
void dequeue(queue *&front);

int main()
{
	ifstream input;
	input.open("input.txt");

	int item;
	BinaryTree *root = nullptr;

	while (input >> item) {
		root = insert(root, item);
	}

	input.close();

	ofstream output;
	output.open("output.txt");

	displayBreadth(root, &output);

	output.close();

	return 0;
}

BinaryTree* insert(BinaryTree *node, int key)
{
	if (!node) {
		BinaryTree *root = new BinaryTree;
		root->item = key;
		return root;
	}

	if (key < node->item)
		node->left  = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	node = rebalance(node);
	return node;
}

BinaryTree* rebalance(BinaryTree *node)
{
	node->height = max(height(node->left), height(node->right)) + 1;

	if (getBalance(node) < -1)
	{
		if (getBalance(node->right) > 0)
			node->right = rightRotate(node->right);

		return leftRotate(node);
	}

	else if (getBalance(node) > 1)
	{
		if (getBalance(node->left) < 0)
			node->left = leftRotate(node->left);

		return rightRotate(node);
	}

	return node;
}

int getBalance(BinaryTree *node)
{
	int leftHeight = height(node ? node->left : nullptr);
	int rightHeight = height(node ? node->right : nullptr);

	return leftHeight - rightHeight;
}

int height(BinaryTree *node)
{
	return node ? node->height : -1;
}

BinaryTree* leftRotate(BinaryTree *x)
{
	BinaryTree *y = x->right;

	x->right = y->left;
	y->left = x;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

BinaryTree* rightRotate(BinaryTree *x)
{
	BinaryTree *y = x->left;

	x->left = y->right;
	y->right = x;

	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	return y;
}

void displayBreadth(BinaryTree *root, ofstream *out)
{
	queue *currentLevel = nullptr;
	queue *nextLevel = nullptr;

	enqueue(root, currentLevel);

	while (currentLevel)
	{
		BinaryTree *root = currentLevel->leaf;
		*out << root->item << "(" << height(root) << ", " << getBalance(root) << ")  ";
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
