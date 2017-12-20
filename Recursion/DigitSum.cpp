
#include <iostream>

using namespace std;

int sumDigits(int input);

int main()
{
	int input;
	cin >> input;

	cout << sumDigits(input) << endl;

	return 0;
}

int sumDigits(int input)
{
	if (input == 0)
		return 0;

	return (input % 10) + sumDigits(input/10);
}
