
#include <iostream>
#include <cmath>

using namespace std;

struct tree {
	char item;
	tree *left = nullptr;
	tree *right = nullptr;
};

struct stacktree {
	struct tree *item;
	stacktree *previous;
};

stacktree* processExpression(char *expression);
int resultOf(tree *expression);
int evaluate(int left, int right, char op);
bool isOperator(char character);
void displayInInfixNotation(tree *expression);
void push(tree *item, struct stacktree *&bottom);
void pop(struct stacktree *&bottom);

int main()
{
	cout << "Enter your postfix expression in one line and press enter." << endl;

	char expression[100];
	cin >> expression;

	stacktree *expressionTree = processExpression(expression);

	cout << "Here is the result of your expression: " << resultOf(expressionTree->item) << endl;

	cout << "Here is your expression in infix notation: ";
	displayInInfixNotation(expressionTree->item);
	cout << endl;

	return 0;
}

stacktree* processExpression(char *expression)
{
	stacktree *expressionTree = nullptr;

	while (*expression != '\0')
	{
		if (isOperator(*expression)) {

			tree *operatorTree = new tree;
			operatorTree->item = *expression;

			operatorTree->right = expressionTree->item;
			pop(expressionTree);

			operatorTree->left = expressionTree->item;
			pop(expressionTree);

			push(operatorTree, expressionTree);

		} else {

			tree *operandTree = new tree;
			operandTree->item = *expression;

			push(operandTree, expressionTree);
		}

		expression++;
	}

	return expressionTree;
}

int resultOf(tree *expression)
{
	if (!expression) return 0;

	int left = resultOf(expression->left);
	int right = resultOf(expression->right);

	if (isOperator(expression->item))
		return (evaluate(left, right, expression->item));
	else
		return expression->item - '0';
}

int evaluate(int left, int right, char op)
{
	switch (op) {
		case '*':
			return left * right;
		case '/':
			return left / right;
		case '+':
			return left + right;
		case '-':
			return left - right;
		case '^':
			return pow(left, right);
		default: return 0;
	}
}

bool isOperator(char character)
{
	if (character == '^' || character == '*' || character == '/' || character == '+' || character == '-')
		return true;

	return false;
}

void displayInInfixNotation(tree *expression)
{
	if (expression) {
		if (isOperator(expression->item)) cout << "(";
		displayInInfixNotation(expression->left);
		cout << expression->item;
		displayInInfixNotation(expression->right);
		if (isOperator(expression->item)) cout << ")";
	}
}

void push(tree *item, struct stacktree *&bottom)
{
	struct stacktree *newNode = new stacktree;

	newNode->item = item;
	newNode->previous = bottom;
	bottom = newNode;
}

void pop(struct stacktree *&bottom)
{
	struct stacktree *temp;
	if (bottom) {
		temp = bottom;
		bottom = bottom->previous;
		delete temp;
	}
}
