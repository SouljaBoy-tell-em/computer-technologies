#include <iostream>
#include <cstdlib>

using namespace std;


enum graph_dump_commands {

	HEAD,
	FIRSTLY
};


const char * GREEN = "green";
const char * RED = "red";
const char * ORANGE = "orange";

#define CHECK_ERROR(condition, message_error, error_code) \
            do {                                          \
               if (condition) {                           \
                   printf ("%s", message_error);          \
                   return error_code;                     \
               }                                          \
            } while(false)


typedef int Elem_t;

typedef struct node {

	Elem_t value;
	struct node * parent;
	struct node * left;
	struct node * right;
} Node;

typedef struct {

	Node * head;
	int size;
} Tree;


int AddItem (Tree * tree, Elem_t item);
int AddNode (Node * head, Node * mem, Node * parent);
int graphDump (Node * head);
void graphDumpDrawNode (Node * currentNode, FILE * graphDumpFile, int * commandGraphDump);


int main (void) {

	int N 		= 0;
	Elem_t item = 0;
	cout << "Input amount of array elements:" << endl;
	cin >> N;
	cout << "Then input elements of array:" << endl;

	Tree tree = {};

	int i = 0;
	for (i = 0; i < N; i++) {

		cin >> item;
		AddItem (&tree, item);
	}

	graphDump (tree.head);

	return 0;
}


int AddItem (Tree * tree, Elem_t item) {

	Node * mem = (Node * ) malloc (sizeof (Node));
	CHECK_ERROR(!mem, "Problem with allocating memory for mem.", EXIT_FAILURE);

	mem->value = item;
	mem->left  = NULL;
	mem->right = NULL;
	mem->parent = NULL;

	if (!tree->size) {

		tree->head = mem;
		tree->size++;

		return EXIT_SUCCESS;
	}

	else {

		AddNode (tree->head, mem, NULL);
		tree->size++;
	}

	return EXIT_SUCCESS;
}


int AddNode (Node * head, Node * mem, Node * parent) {

	if (mem->value > head->value) {

		if (head->right == NULL) {

			head->right = mem;
			(head->right)->parent = head;
			return EXIT_SUCCESS;
		}

		else {

			head->parent = parent;
			AddNode (head->right, mem, head);
			return EXIT_SUCCESS;
		}

		return EXIT_SUCCESS;
	}

	if (mem->value < head->value) {

		if (head->left == NULL) {

			head->left = mem;
			(head->left)->parent = head;
			return EXIT_SUCCESS;
		}

		else {

			head->parent = parent;
			AddNode (head->left, mem, head);
			return EXIT_SUCCESS;
		}

		return EXIT_SUCCESS;
	}

	else {

		cout << "So element already contains in tree." << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


int graphDump (Node * head) {

	FILE * graphDumpFile = fopen ("graphsort.txt", "w");
	CHECK_ERROR(!graphDumpFile, "Problem with opening graphDump.txt.\n", EXIT_FAILURE);

	int commandGraphDump = HEAD;
	fprintf (graphDumpFile, "digraph G {\n rankdir=L\n");
	graphDumpDrawNode (head, graphDumpFile, &commandGraphDump);
	fprintf (graphDumpFile, "}");
	fclose (graphDumpFile);

	return EXIT_SUCCESS;
}


void graphDumpDrawNode (Node * currentNode, FILE * graphDumpFile, int * commandGraphDump) {

	if (currentNode != NULL) {

		if (( * commandGraphDump) != HEAD) {

			if (( * commandGraphDump) == FIRSTLY)
				fprintf (graphDumpFile, "block%d [shape=record, color=\"%s\", label=\"%d\"];\n",  
				(currentNode->parent)->value, ORANGE, (currentNode->parent)->value);

			if ((currentNode->parent)->left == currentNode)
				fprintf (graphDumpFile, "block%d [shape=record, color=\"%s\", label=\"%d\"];\n",
				currentNode->value, 			  GREEN,           currentNode->value);

			if ((currentNode->parent)->right == currentNode)
				fprintf (graphDumpFile, "block%d [shape=record, color=\"%s\", label=\"%d\"];\n",  
				currentNode->value, 				RED,    	   currentNode->value);

			fprintf (graphDumpFile, "block%d -> block%d\n",
				(currentNode->parent)->value, 				   currentNode->value);

		}

		( * commandGraphDump)++                                                ;
		graphDumpDrawNode (currentNode->left, graphDumpFile,  commandGraphDump);
		graphDumpDrawNode (currentNode->right, graphDumpFile, commandGraphDump);
	}
}