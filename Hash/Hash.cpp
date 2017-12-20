
#include <iostream>
#include <fstream>
#include <cmath>

#define TableSize 10

using namespace std;

int insertModuloDivision(int *bucket, int item);
int insertDoubleHashing(int *bucket, int item, int addressOfCollision);
int insertQuadraticProbing(int *bucket, int item, int addressOfCollision);
int insertLinearProbing(int *bucket, int item);

int searchModuloDivision(int *bucket, int item);
int searchDoubleHashing(int *bucket, int item, int addressOfCollision);
int searchQuadraticProbing(int *bucket, int item, int addressOfCollision);
int searchLinearProbing(int *bucket, int item);

int main()
{
	ifstream input;
	input.open("input.txt");

	int item;
	int bucket[TableSize];

	for (int i = 0; i < TableSize; i++) {
		bucket[i] = INT_MAX;
	}

	int count = 0;

	for (int i = 0; input >> item; i++) {
		int collisions = 0;
		collisions = insertModuloDivision(bucket, item);
		count = i;

		if (collisions == 1) {
			cout << "There has been 1 collision while inserting \"" << item << "\"." << endl;
		} else {
			cout << "There have been " << collisions << " collisions while inserting \"" << item << "\"." << endl;
		}
	}

	input.close();


	while (1)
	{
		cout << endl << "Please enter a value to search for in the table: ";
		cin >> item;

		int found = searchModuloDivision(bucket, item);

		if (found >= 4) {
			cout << "The value was not found in the list. Please try again." << endl;
		} else {
			cout << "The value was found in the list. Good job." << endl;
		}
	}

	return 0;
}

#pragma mark - Hashing

int insertModuloDivision(int *bucket, int item)
{
	int addressToInsert = item % TableSize;

	if (bucket[addressToInsert] != INT_MAX) {
		return 1 + insertDoubleHashing(bucket, item, addressToInsert);
	} else {
		bucket[addressToInsert] = item;
	}

	return 0;
}

int insertDoubleHashing(int *bucket, int item, int addressOfCollision)
{
	int addressToInsert = addressOfCollision - (item % addressOfCollision);

	if (bucket[addressToInsert] != INT_MAX) {
		return 1 + insertQuadraticProbing(bucket, item, addressToInsert);
	} else {
		bucket[addressToInsert] = item;
	}

	return 0;
}

int insertQuadraticProbing(int *bucket, int item, int addressOfCollision)
{
	int addressToInsert = 0;

	for (int i = 1; i < 4; i++)
	{
		addressToInsert = (addressOfCollision + (int)pow(i, 2)) % TableSize;

		if (bucket[addressToInsert] == INT_MAX) {
			bucket[addressToInsert] = item;
			return 0;
		}
	}

	return 1 + insertLinearProbing(bucket, item);
}

int insertLinearProbing(int *bucket, int item)
{
	for (int i = 0; i < TableSize; i++)
	{
		if (bucket[i] == INT_MAX) {
			bucket[i] = item;
			break;
		}
	}

	return 0;
}

#pragma mark - Searching

int searchModuloDivision(int *bucket, int item)
{
	int addressToInsert = item % TableSize;

	if (bucket[addressToInsert] != item) {
		return 1 + searchDoubleHashing(bucket, item, addressToInsert);
	}

	return 0;
}

int searchDoubleHashing(int *bucket, int item, int addressOfCollision)
{
	int addressToInsert = addressOfCollision - (item % addressOfCollision);

	if (bucket[addressToInsert] != item) {
		return 1 + searchQuadraticProbing(bucket, item, addressToInsert);
	}

	return 0;
}

int searchQuadraticProbing(int *bucket, int item, int addressOfCollision)
{
	int addressToInsert = 0;

	for (int i = 1; i < 4; i++)
	{
		addressToInsert = (addressOfCollision + (int)pow(i, 2)) % TableSize;

		if (bucket[addressToInsert] == item) {
			return 0;
		}
	}

	return 1 + searchLinearProbing(bucket, item);
}

int searchLinearProbing(int *bucket, int item)
{
	for (int i = 0; i < TableSize; i++)
	{
		if (bucket[i] == item) {
			return 0;
		}
	}

	return 1;
}
