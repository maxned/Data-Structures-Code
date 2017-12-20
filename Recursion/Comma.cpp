
#include <iostream>

using namespace std;

void commer(int input, int count, char *output, char *original);

int main()
{
	int input;
	cin >> input;

	char commad[100];
	commer(input, 0, commad, commad);

	cout << commad << endl;

	return 0;
}

void commer(int input, int count, char *output, char *original)
{
	if (input > 0) {

		if (count == 3) {
			count = 0;
			*output = ',';
		} else {
			*output = '0' + (input % 10);
			input /= 10;
			count++;
		}

		commer(input, count, output + 1, original);

	} else {
		*output = '\0';

		// reverse the number due to above algorithm
		char temp[100];

		count = 0;
		while(original[count] != '\0') {
			temp[count] = original[count];
			count++;
		}

		for (int i = count; i >= 0; i--) {
			original[count - i] = temp[i - 1];
		}
	}
}
