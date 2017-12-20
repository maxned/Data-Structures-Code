
#include <iostream>
#include <fstream>

using namespace std;

void stringCopy(char *A, char *B);
bool stringCompare(char *A, char *B);
void stringConcatenation (char *A, char *B);
int stringPosition(char *A, char B);
int stringLength(char *A);

int main()
{
	ifstream in("in.txt");

	// we will limit string length to 1000 characters plus the null character
	char *string1 = new char[1001];
	char *string2 = new char[1001];

	char temp;
	int j;

	for (int i = 0; i < 5; i++) {

		// populate string 1 with the first item
		j = 0;
		while (in.get(temp) && temp != ' ' && temp != '\n' && temp != '\t' && temp != '\r') {
			string1[j] = temp;
			j++;
		}
		string1[j] = '\0';

		// populate string 2 with the second item
		j = 0;
		while (in.get(temp) && temp != ' ' && temp != '\n' && temp != '\t' && temp != '\r') {
			string2[j] = temp;
			j++;
		}
		string2[j] = '\0';

		// functions to call after populating the strings based on the line from the in.txt file
		switch (i) {
			case 0:
				cout << "Original Strings:\nString 1: " << string1 << "\nString 2: " << string2 << endl;
				stringCopy(string1, string2);
				cout << "stringCopy\n";
				cout << "String 1: " << string1 << "\nString 2: " << string2 << endl << endl << endl;
				break;
			case 1:
				cout << "Original Strings:\nString 1: " << string1 << "\nString 2: " << string2 << endl;
				cout << "stringCompare" << endl << "Equal: " << stringCompare(string1, string2) << endl;
				cout << "String 1: " << string1 << "\nString 2: " << string2 << endl << endl << endl;
				break;

			case 2:
				cout << "Original Strings:\nString 1: " << string1 << "\nString 2: " << string2 << endl;
				stringConcatenation(string1, string2);
				cout << "stringConcatenation\n";
				cout << "String 1: " << string1 << "\nString 2: " << string2 << endl << endl << endl;;
				break;
			case 3:
				cout << "Original Strings:\nString 1: " << string1 << "\nString 2: " << string2 << endl;
				cout << "stringPosition: " << stringPosition(string1, *string2) << endl << endl << endl;
				break;
			case 4:
				cout << "Original String:\nString 1: " << string1 << string2 << endl;
				cout << "stringLength: " << stringLength(string1) << endl;
				cout << "String 1: " << string1 << endl << endl;
				;
				break;
			default:
				break;
		}
	}

	in.close();
	delete [] string1;
	delete [] string2;

	return 0;
}

void stringCopy(char *A, char *B)
{
	for (int i = 0; B[i] != '\0'; i++) {
		A[i] = B[i];
		if (B[i + 1] == '\0') A[i + 1] = '\0'; // check if the next character in B is the null character and if so, add it to A
	}
}

bool stringCompare(char *A, char *B)
{
	// assume they are the same and if not, change to false
	bool same = true;

	for (int i = 0; A[i] != '\0' || B[i] != '\0'; i++) {
		if (A[i] != B[i]) same = false;
	}

	return same;
}

void stringConcatenation(char *A, char *B)
{
	int i = 0;
	while (A[i] != '\0') {
		i++;
	}

	int j = 0;
	while (B[j] != '\0' ) {
		A[i + j] = B[j];
		j++;
	}
	A[i + j] = B[j]; // add the null character from the end of B
}

int stringPosition(char *A, char B)
{
	for (int i = 0; A[i] != '\0'; i++) {
		if (A[i] == B) return i;
	}

	return -1;
}

int stringLength(char *A)
{
	int length = 0;
	while (A[length] != '\0') {
		length++;
	}

	// lets assume that the string will be smaller than the following biggest number
	int shift = 1;
	if (length > 9) shift++;
	if (length > 99) shift++;
	if (length > 999) shift++;

	// now we shift the string to the right by shift to make space for the length
	for (int i = length; i >= 0; i--) {
		A[i + shift] = A[i];
	}

	int fullLength = length;

	// store the string length in the original string
	for (int i = shift - 1; i >= 0; i--) {
		A[i] = (length % 10) + '0';
		length /= 10;
	}

	return fullLength;
}
