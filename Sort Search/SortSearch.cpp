
#include <iostream>

#define Columns 4
#define Rows 5

void bubbleSort(int **arr, int limit);
void selectionSort(int **arr, int limit);
void insertionSort(int **arr, int size);
int binarySearch(int *arr, int key, int size);
void displayArray();
void populateArray();

int **array;

int main()
{
	populateArray();
	std::cout << "Standard Array:\n";
	displayArray();

	bubbleSort(array, Rows - 1);
	std::cout << "Bubble Sorted First Column:\n";
	displayArray();

	populateArray();

	selectionSort(array, Rows - 1);
	std::cout << "Selection Sorted Second Column:\n";
	displayArray();

	populateArray();

	insertionSort(array, Columns);
	std::cout << "Insertion Sorted Fifth Row:\n";
	displayArray();


	int number;
	std::cout << "What number are you searching for in the 5th row?" << std::endl;
	std::cin >> number;
	std::cout << std::endl;

	int result = binarySearch(array[4], number, Columns);

	if (result < 0) {
		std::cout << "No match found." << std::endl;
	} else {

		for (int i = 0; i < Rows; i++) {
			std::cout << array[i][result] << std::endl;
		}
	}

	return 0;
}

void bubbleSort(int **arr, int limit)
{
	int *temp, index;

	//This loop is used to determine the number of passes
	for (; limit > 0; limit--) {
		for (index = 0; index < limit; index++) {

			// To change to descending order just change the relational operator to <
			if (arr[index][0] > arr[index + 1][0])
			{
				temp = arr[index];
				arr[index] = arr[index + 1];
				arr[index + 1] = temp;
			}
		}
	}
}

void selectionSort(int **arr, int limit)
{
	int *temp, index_of_largest,index;

	// This loop is used to determine the number of passes
	for(; limit > 0; limit--) {
		index_of_largest = 0 ;

		// This loop is used to determine the number of comparisons for each pass
		for (index = 1; index <= limit; index++) {

			// To change to ascending order just change the relational operator to >
			if (arr[index][1] < arr[index_of_largest][1])
				index_of_largest = index; // Store the index of array element
		}

		// Swap element at the end of pass if needed
		if (limit != index_of_largest) {
			temp = arr[limit];
			arr[limit] = arr[index_of_largest];
			arr[index_of_largest] = temp;
		}
	}
}

void insertionSort(int **arr, int size)
{
	int i, j, temp[Rows];

	for (i = 1; i < size; i++)  {
		for (j = i; j > 0 && arr[4][j] < arr[4][j - 1]; j--)
		{
			for (int k = 0; k < Rows; k++) {
				temp[k] = arr[k][j];
				arr[k][j] = arr[k][j - 1];
				arr[k][j - 1] = temp[k];
			}
		}
	}
}

int binarySearch(int *arr, int key, int size)
{
	int high = size - 1, low = 0, mid = -1;
	bool found = false;

	while (high >= low && !found)
	{
		// calculate the midpoint for roughly equal partition
		mid = (high + low ) / 2;

		if (key > arr[mid]) {
			low = mid + 1;
		} else if (key < arr[mid]) {
			high = mid - 1;
		} else {
			found = true;
		}
	}

	if (found) {
		return mid;
	} else {
		return -1;
	}
}

void displayArray()
{
	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++) {
			std::cout << array[i][j] << ((j == 3) ? "" : ", ");
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void populateArray()
{
	if (array) {
		for (int i = 0; i < Rows; i++) {
			delete [] array[i];
		}

		delete [] array;
	}

	array = new int*[Rows];
	for (int i = 0; i < Rows; i++) {
		array[i] = new int[Columns];
	}

	int OGArray[Rows][Columns] = { { 5, 3, 2, 16 },
		{ 9, 8, 10, 17 },
		{ 4, 7, 11, 18 },
		{ 2, 5, 9, 12 },
		{ 7, 9, 4, 10 }
	};

	for (int i = 0; i < Rows; i++) {
		for (int j = 0; j < Columns; j++) {
			array[i][j] = OGArray[i][j];
		}
	}
}
