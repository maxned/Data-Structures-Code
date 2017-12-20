
#include <iostream>
#include <fstream>

using namespace std;

struct node {
	char item;
	int value;
	node *next;
};

void infixToPostfix(char *infix);
void push(int value, struct node *&top);
void push(char item, struct node *&top);
void pop(struct node *&top);
void enqueue(int item, struct node *&front, struct node *&rear);
void dequeue(struct node *&front, struct node *&rear);
void traverse(node *front);
void evaluatePostfix();

node *stack = NULL;
node *queueFront = NULL;
node *queueRear = NULL;

int main()
{
	ifstream input;
	input.open("input.txt");

	char infix[101]; // no one will be crazy enough to type in a 100 character infix expression
	input >> infix;
	input.close();

	cout << "Infix: " << infix << endl;

	infixToPostfix(infix); // postfix equation stored in queue
	cout << "Postfix: "; traverse(queueFront);

	evaluatePostfix();
	cout << "Result: " << stack->value << endl;

	return 0;
}

void infixToPostfix(char *infix)
{
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
}

void evaluatePostfix()
{
	while (queueFront != NULL)
	{
		if (queueFront->item == '*' || queueFront->item == '/' || queueFront->item == '+' || queueFront->item == '-')
		{
			int op2 = stack->value;
			pop(stack);

			int op1 = stack->value;
			pop(stack);

			int result;

			switch (queueFront->item) {
				case '*':
					result = op1 * op2;
					break;

				case '/':
					result = op1 / op2;
					break;

				case '+':
					result = op1 + op2;
					break;

				case '-':
					result = op1 - op2;
					break;

				default:
					result = 0;
					break;
			}

			push(result, stack);
			
		} else {
			push((int)(queueFront->item - '0'), stack);
		}

		dequeue(queueFront, queueRear);
	}
}

void push(char item, struct node *&top)
{
	struct node *newNode = new node;

	newNode->item = item;
	newNode->next = top;
	top = newNode;
}

void push(int value, struct node *&top)
{
	struct node *newNode = new node;

	newNode->value = value;
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

void dequeue(struct node *&front, struct node *&rear)
{
	struct node *temp;

	if (front) {
		temp = front;
		front = front->next;
		delete temp;
		if (!front)
			rear = NULL;
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
