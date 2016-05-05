#include<stdio.h>
#include<stdlib.h>
//declare the structure
typedef struct _node {
	Edge* point;
	int count;
	int be_pointed;
} Node;

int main() {
	//enlarge buffer
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	//basic data read in
	register int n, m;
	scanf("%d %d", &n, &m);
	//varaibles??
	
	//whole data read in
	//find the Node without a point
	//start from this node, find the longest route
	//compare
}