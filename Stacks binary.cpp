
#include <iostream>

using namespace std;

void fillStackWithBinaryRepresentation(uint64_t number);
void fillStackWithHexRepresentation(uint64_t number);

char *stack;
int stackCounter = 0;

int main()
{
	uint64_t number;

	stack = new char[64];

	while (cin >> number) {
		fillStackWithBinaryRepresentation(number);
		cout << "Binary: ";
		while (stackCounter >= 0) {
			cout << stack[--stackCounter];
		}
		stackCounter = 0;

		cout << endl;

		fillStackWithHexRepresentation(number);
		cout << "Hex: ";
		while (stackCounter >= 0) {
			cout << stack[--stackCounter];
		}
		stackCounter = 0;

		cout << endl << endl;
	}

	delete [] stack;

	return 0;
}

void fillStackWithBinaryRepresentation(uint64_t number)
{
	do {
		stack[stackCounter] = number % 2 + '0';
		stackCounter++;
	} while ((number /= 2) > 0);
}

void fillStackWithHexRepresentation(uint64_t number)
{
	do {
		stack[stackCounter] = number % 16 + ((number % 16 > 9) ? '7' : '0');
		stackCounter++;
	} while ((number /= 16) > 0);
}
