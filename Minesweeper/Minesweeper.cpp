
#include <iostream>

using namespace std;

int mineArray[10][10] = {
	{1,1,1,1,0,1,1,1,0,0},
	{1,0,0,1,0,1,0,1,0,0},
	{1,1,1,1,0,0,0,1,0,0},
	{1,0,0,1,0,0,1,0,0,1},
	{1,1,0,1,0,1,0,1,0,1},
	{1,0,1,1,1,0,1,0,1,0},
	{1,0,0,1,0,0,1,0,0,1},
	{1,0,1,1,1,1,1,1,0,0},
	{1,1,1,1,1,0,0,0,0,1},
	{1,1,0,1,1,0,1,0,0,1}
};

struct node {
	int value = -1;
	node *top = nullptr;
	node *bottom = nullptr;
	node *left = nullptr;
	node *right = nullptr;
};

void populateMineList(node *&minesweeper, int mineArray[10][10]);
void displayMineList(node *minesweeper);
void minesweep(int row, int column, node *&minesweeper);
void eliminateSurroundingMines(node *&mine);

int main()
{
	node *minesweeper = nullptr;
	populateMineList(minesweeper, mineArray);

	cout << "Here is a minesweeper list:" << endl;
	displayMineList(minesweeper);

	cout << endl << "Choose a row followed by a column. Both are 0-indexed." << endl;

	int row;
	int column;
	cin >> row >> column;

	while (row > 9 || column > 9 || row < 0 || column < 0) {
		cout << "Selected row or column is invalid. Please choose again." << endl;
		cin >> row >> column;
	}

	minesweep(row, column, minesweeper);

	cout << endl << "Here is the minesweeped list based on your selection." << endl;
	displayMineList(minesweeper);

	return 0;
}

node *previousTopRight = nullptr;

void populateMineList(node *&minesweeper, int mineArray[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			node *newNode = new node;
			newNode->value = mineArray[i][j];

			if (!minesweeper) {
				minesweeper = newNode;
				if (previousTopRight) {
					minesweeper->top = previousTopRight->left;
					minesweeper->top->bottom = minesweeper;
				}

			} else {

				if (minesweeper->top)
					newNode->top = minesweeper->top->right;

				if (newNode->top)
					newNode->top->bottom = newNode;

				newNode->left = minesweeper;
				minesweeper->right = newNode;

				minesweeper = newNode;
			}
		}

		// move back to the left
		while (minesweeper->left)
			minesweeper = minesweeper->left;

		if (i != 9) {
			// move down and save previous top right cell
			previousTopRight = minesweeper->right;
			minesweeper = minesweeper->bottom;
		} else {
			// reset back to cell 0,0
			while (minesweeper->top)
				minesweeper = minesweeper->top;
		}
	}
}

void displayMineList(node *minesweeper)
{
	node *current = minesweeper;

	while (current)
	{
		node *current2 = current;
		while (current2) {
			cout << current2->value;
			current2 = current2->right;
		}

		cout << endl;
		current = current->bottom;
	}
}

void minesweep(int row, int column, node *&minesweeper)
{
	node *startingPoint = minesweeper;

	for (int i = 0; i < row; i++)
		startingPoint = startingPoint->bottom;

	for (int i = 0; i < column; i++)
		startingPoint = startingPoint->right;

	eliminateSurroundingMines(startingPoint);
}

void eliminateSurroundingMines(node *&mine)
{
	mine->value = 0;

	if (mine->top && mine->top->value == 1)
		eliminateSurroundingMines(mine->top);

	if (mine->bottom && mine->bottom->value == 1)
		eliminateSurroundingMines(mine->bottom);

	if (mine->right && mine->right->value == 1)
		eliminateSurroundingMines(mine->right);

	if (mine->left && mine->left->value == 1)
		eliminateSurroundingMines(mine->left);
}
