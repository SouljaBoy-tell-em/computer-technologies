#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;


int main (void) {

	int N = 0, i = 0;
	scanf ("%d", &N);

	char ** word = (char ** ) malloc (sizeof (char * ) * N);
	for (i = 0; i < N; i++)
		word[i] = (char * ) malloc (sizeof (char) * 100);

	for (i = 0; i < N; i++)
		scanf ("%s", word[i]);

	int maxcount(1), nn(-1);
	vector<int> v;

    int n, e;
    for (int i = 0; i < N; i++)
    {
        e = word[i][0];
        v.push_back(e);
    }

    for (int i = 0; i < v.size(); i++) {

        int count(0);

        for (int j = i; j < v.size(); j++)

            if (v[i] == v[j])
                count++;

        if (maxcount < count)
        {
            maxcount = count;
            nn = i;
            
        }
    }
    
    if (nn > -1){
        
        cout << (char) v[nn];
    }
    else
        cout << (char) *v.rbegin();
 
 

    return 0;
}