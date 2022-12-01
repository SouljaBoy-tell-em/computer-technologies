#include <iostream>
#include <string>
#include <map>


#define MAXLENTITLE 100


using namespace std;


typedef struct info {

	int  * answer;
	char ** word1;
	char ** word2;
	int N;
} INFO;


void createInfoBlock (INFO * infoblock);
void getDictionary (INFO * infoblock);
void InitializeMap (map <char, int> (&mp));


int main (void) {

	int N = 0;
	cin >> N;

	INFO infoblock = {};
	infoblock.N = N;
	createInfoBlock (&infoblock);
	getDictionary (&infoblock);

	return 0;
}


void createInfoBlock (INFO * infoblock) {

	int i = 0;

	infoblock->answer = (int * )   calloc (infoblock->N, sizeof (char));
	for (i = 0; i < infoblock->N; i++)
		infoblock->answer[i] = 0;

	infoblock->word1   = (char **) calloc (infoblock->N, sizeof (char *));
	for (i = 0; i < infoblock->N; i++)
		infoblock->word1[i] = (char * ) calloc (MAXLENTITLE, sizeof (char));

	infoblock->word2   = (char **) calloc (infoblock->N, sizeof (char *));
	for (i = 0; i < infoblock->N; i++)
		infoblock->word2[i] = (char * ) calloc (MAXLENTITLE, sizeof (char));

	for (i = 0; i < infoblock->N; i++) {

		cin >> infoblock->word1[i];
		cin >> infoblock->word2[i];
	}
}


void InitializeMap (map <char, int> (&mp), char * word) {

	char i = '\0';
	for (i = 'a'; i < 'z'; i++)
		mp[i] = 0;

	int numSymbol = 0;
	while ( * (word + numSymbol) != '\0') {

		mp[( * (word + numSymbol))] += 1;
		numSymbol++;
	}
}


void getDictionary (INFO * infoblock) {

	map <char, int> mp1;
	map <char, int> mp2;

	cout << endl << endl;

	int i = 0;
	for (i = 0; i < infoblock->N; i++) {

		InitializeMap (mp1, infoblock->word1[i]);
		InitializeMap (mp2, infoblock->word2[i]);

		cout << i + 1 << ":\n\n";
		cout << "word1: " << infoblock->word1[i] << endl;
		cout << "word2: " << infoblock->word2[i] << endl;


		if (mp1 == mp2)
			cout << "YES\n";

		else 
			cout << "NO\n";

		cout << endl << endl;
	}
}