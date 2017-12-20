
#include <iostream>
#include <fstream>

using namespace std;

struct node {
	char item;
	node *next;
};

void push(int item, struct node *&top);
void pop(struct node *&top);
void enqueue(int item, struct node *&front, struct node *&rear);
void traverse(node *front);

int main()
{
	ifstream input;
	input.open("input.txt");

	char infix[101]; // no one will be crazy enough to type in a 100 character infix expression
	input >> infix;
	input.close();

	node *stack = NULL;
	node *queueFront = NULL;
	node *queueRear = NULL;

	for (int i = 0; infix[i] != '\0'; i++)
	{
		if (infix[i] == '(') { // open paranthesis
			push(infix[i], stack);

		} else if (infix[i] == ')') { // close parenthesis

			while (stack->item != '(') {
				enqueue(stack->item, queueFront, queueRear);
				pop(stack);
			}
			pop(stack); // pop the open parenthesis

		} else if (infix[i] == '^' || infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-' || infix[i] == '=') { // operator

			switch (infix[i]) {
				case '^':
					break;

				case '*':
					while (stack != NULL && (stack->item == '^' || stack->item == '*'  || stack->item == '/')) {
						enqueue(stack->item, queueFront, queueRear);
						pop(stack);
					}
					break;

				case '/':
					while (stack != NULL && (stack->item == '^' || stack->item == '*' || stack->item == '/')) {
						enqueue(stack->item, queueFront, queueRear);
						pop(stack);
					}
					break;

				case '+':
					while (stack != NULL && (stack->item == '^' || stack->item == '*' || stack->item == '/' || stack->item == '+' || stack->item == '-')) {
						enqueue(stack->item, queueFront, queueRear);
						pop(stack);
					}
					break;

				case '-':
					while (stack != NULL && (stack->item == '^' || stack->item == '*' || stack->item == '/' || stack->item == '+' || stack->item == '-')) {
						enqueue(stack->item, queueFront, queueRear);
						pop(stack);
					}
					break;

				case '=':
					while (stack != NULL && (stack->item == '^' || stack->item == '*' || stack->item == '/' || stack->item == '+' || stack->item == '-' || stack->item == '(' || stack->item == '=')) {
						enqueue(stack->item, queueFront, queueRear);
						pop(stack);
					}
					break;

				default:
					break;
			}

			push(infix[i], stack);

		} else { // operand
			enqueue(infix[i], queueFront, queueRear);
		}
	}

	while (stack) {
		enqueue(stack->item, queueFront, queueRear);
		pop(stack);
	}

	traverse(queueFront);

	return 0;
}

void push(int item, struct node *&top)
{
	struct node *newNode = new node;

	newNode->item = item;
	newNode->next = top;
	top = newNode;
}

void pop(struct node *&top)
{
	struct node *temp;
	if (top) {
		temp = top;
		top = top->next;
		delete temp;
	}
}

void enqueue(int item, struct node *&front, struct node *&rear)
{
	struct node *newNode = new node;

	newNode->item = item;
	newNode->next = NULL;
	if (rear) {
		rear->next = newNode;
		rear = newNode;
	} else {
		front = rear = newNode;
	}
}

void traverse(node *front)
{
	node *current = front;

	do {
		cout << current->item;
		current = current->next;
	} while (current);

	cout << endl;
}
