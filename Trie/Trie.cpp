
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct trie_node {
	int value = 0;
	trie_node *children[26] = { 0 };
};

void insert(trie_node *current, char key[]);
void search(trie_node *root, const char key[]);

int main()
{
	ifstream input;
	input.open("input.txt");

	char inputString[100];
	trie_node *root = new trie_node;

	while (input >> inputString) {
		insert(root, inputString);
	}

	input.close();

	cout << "Enter a word or word stem: ";
	cin >> inputString;

	cout << "Here are all of the words containing the word or word stem: " << endl;
	search(root, inputString);
	cout << endl;

	return 0;
}

// Move level by level and create nodes. The last node for that word will
// have value set to 1 and all the array elements point to nothing unless
// it is a word stem
void insert(trie_node *current, char key[])
{
	int index;
	for (int level = 0; level < strlen(key); level++)
	{
		index = (int)key[level] - (int)'a';
		if (!current->children[index])
			current->children[index] = new trie_node;
		current = current->children[index];
	}

	current->value = 1;
}

void search(trie_node *root, const char key[])
{
	int index = 0;
	trie_node *current = root;

	for (int level = 0; level < strlen(key); level++)
	{
		index = (int)key[level] - (int)'a';
		if (current) {
			current = current->children[index];
		}
	}

	if (current)
	{
		if (current->value) cout << key << endl;

		// go through all of the characters and go down all the other paths
		for (int i = 0; i < 25; i++) {
			if (current->children[i]) {
				char newCharacter[2] = { char('a' + i), '\0' };
				char newString[100];
				strcpy(newString, key);
				search(root, strcat(newString, newCharacter));
			}
		}
		
	} else {
		cout << "No matching words found." << endl;
	}
}
