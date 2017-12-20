
#include <iostream>
#include <fstream>

using namespace std;

void quickSort(int a[], int start, int end);
int partition(int a[], int first, int last);
void display(int *array, int size);
int numDigits(int value);
int addFives(int value, int totalDigits);

struct node {
	int item;
	node *next;
};

void radixSortDescending(int *&unsortedArray, node **&arrayWithStacks, int size);
void queueStackUpArray(node **&array);
void enqueue(int item, struct node *&front);
void pop(struct node *&top);

int main()
{
	ifstream input;
	input.open("input.txt");

	int *originalArray = new int[10];
	int value, count = 0;

	while (input >> value) {
		originalArray[count] = value;
		count++;
	}

	input.close();

	cout << "Original Unsorted Array: ";
	display(originalArray, count);

	quickSort(originalArray, 0, count - 1);

	cout << "Quicksort Sorted Array: ";
	display(originalArray, count);

	// largest value is now first because of descending order
	int largestValue = originalArray[0];
	int digits = numDigits(largestValue);

	for (int i = 0; i < count; i++) {
		originalArray[i] = addFives(originalArray[i], digits);
	}

	cout << "Fived Sorted Array: ";
	display(originalArray, count);

	node **arrayWithQueueStacks = nullptr;
	queueStackUpArray(arrayWithQueueStacks);

	radixSortDescending(originalArray, arrayWithQueueStacks, count);

	cout << "Radix Sorted Descending Array: ";
	display(originalArray, count);

	return 0;
}

void quickSort(int a[], int start, int end)
{
	int pIndex;

	// If start == end, we have only one item. No sorting needed.
	// If start > end, then there is nothing to process.
	if (start >= end)
		return;

	pIndex = partition(a, start, end);	// pIndex is used for partioning
	quickSort(a, start, pIndex - 1);	// to the left of the pivot
	quickSort(a, pIndex + 1, end);		// to the right of the pivot
}

int partition(int a[], int first, int last)
{
	int pivot = last;
	int lower = first;
	int upper = last - 1;

	while (lower <= upper)	// While they don't cross over
	{
		// check the left-hand side against the pivot
		while (a[lower] >= a[pivot] && lower <= upper) {
			lower++;
		}

		// If cross over, pass done
		if (lower > upper) break;

		swap(a[lower], a[pivot]);	// swap the pivot
		pivot = lower;              // identify new pivot location
		lower++;

		// Check the right-hand side against the pivot
		while (a[upper] <= a[pivot] && upper >= lower) {
			upper--;
		}

		// If cross over, pass done
		if (upper < lower) break;

		swap(a[upper], a[pivot]);	// swap the pivot
		pivot = upper;				// identify new pivot location
		upper--;
	}

	return pivot;
}

void display(int *array, int size)
{
	for (int i = 0; i < size; i++) {
		cout << array[i] << (i < size - 1 ? ", " : "");
	}

	cout << endl << endl;
}

int numDigits(int value)
{
	if (!value) return 0;
	return 1 + numDigits(value/10);
}

int addFives(int value, int totalDigits)
{
	char number[totalDigits + 1];
	int digits = numDigits(value);

	for (int i = digits - 1; i >= 0; i--) {
		number[i] = value % 10 + '0';
		value /= 10;
	}

	for (int i = digits; i < totalDigits; i++) {
		number[i] = '5';
	}

	number[totalDigits] = '\0';

	int newValue = 0;
	int factor = 1;

	for (int i = totalDigits - 1; i >= 0; i--) {
		newValue += (number[i] - '0') * factor;
		factor *= 10;
	}

	return newValue;
}

void radixSortDescending(int *&unsortedArray, node **&arrayWithStacks, int size)
{
	// find largest integer in the unsorted array
	int maxInt = 0;
	for (int i = 0; i < size; i++) {
		if (maxInt < unsortedArray[i]) maxInt = unsortedArray[i];
	}

	int M = 10;
	int N = 1;

	while (N <= maxInt)
	{
		// sort objects by the digit
		for (int i = 0; i < size; i++) {
			int digit = unsortedArray[i] % M;
			digit /= N;
			enqueue(unsortedArray[i], arrayWithStacks[digit]);
		}

		int count = 0;
		for (int i = 9; i >= 0; i--) {

			while (arrayWithStacks[i]) {
				unsortedArray[count] = arrayWithStacks[i]->item;
				pop(arrayWithStacks[i]);
				count++;
			}
		}

		M *= 10;
		N *= 10;
	}
}

void queueStackUpArray(node **&array)
{
	if (array) {
		for (int i = 0; i < 10; i++) {
			delete array[i];
		}

		delete [] array;
	}

	array = new node*[10];

	for (int i = 0; i < 10; i++) {
		node *queue = NULL;
		array[i] = queue;
	}
}

void enqueue(int item, struct node *&front)
{
	struct node *newNode = new node;

	newNode->item = item;
	newNode->next = NULL;
	if (front) {

		node *current = front;
		while (current->next)
			current = current->next;

		current->next = newNode;

	} else {
		front = newNode;
	}
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
