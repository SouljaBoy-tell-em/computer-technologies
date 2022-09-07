#include <stdio.h>


typedef struct {

    int command;
    int x;
    int y;
    char col;

} Point;


int main (void) {

    int n, i, j;
    char ch;
    scanf ("%d", &n);
    
    Point point[n];
    char color[n];

    for (i = 0; i < n; i++) {

        scanf ("%d", &point[i].command);
        scanf ("%d", &point[i].x);
        scanf ("%d", &point[i].y);
        
    	while ((ch = getchar ()) && ch == ' ')
    		continue;
         
        if (ch == '\n') {
        	
        	point[i].col = ' ';
        	continue;
        	
        }
        
        point[i].col = ch;

    }

    for (i = 0; i < n; i++) {

        if (point[i].command == 2) {

            for (j = i-1; j >= 0; j--) {

                if ((point[i].x == point[j].x) && (point[i].y == point[j].y) && (point[j].command == 1)) {

                    putchar (point[j].col);
                    putchar ('\n');
                    break;

                }

            }
            
            if (j == -1) {
            	
            	putchar ('n');
            	putchar ('\n');
            	
            }

        }

    }

    return 0;

}
