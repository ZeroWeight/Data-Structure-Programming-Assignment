#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//#include<algorithm>
int value[100001];//from 1~n cities
typedef int E[3];//[0] start [1] end [2] price
E edge[100000];
int cmp(const void*, const void *);
int main() {
	register int n, m;
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	scanf("%d %d", &n, &m);
	const int N = n;
	const int M = m;
	for (--m;~m;--m) {
		scanf("%d %d %d", &edge[m][0], &edge[m][1], &edge[m][2]);
	}
	qsort(edge, M,sizeof(E), cmp);
	for (m = M - 1;~m;m--) {
		printf("%d %d %d\n", edge[m][0], edge[m][1], edge[m][2]);
	}
	return 0;
}
int cmp(const void * p, const void * q) {
	if (((*(E*)p))[0] < ((*(E*)q))[0]) return -1;
	else if (((*(E*)p))[0] > ((*(E*)q))[0]) return 1;
	else if (((*(E*)p))[1] < ((*(E*)q))[1]) return -1;
	else if (((*(E*)p))[1] > ((*(E*)q))[1]) return 1;
	else return 0;
}