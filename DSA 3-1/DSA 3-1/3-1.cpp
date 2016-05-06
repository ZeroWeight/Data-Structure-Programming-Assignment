#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct _list {
	int num;
	struct _list* list;
} list;
typedef struct _line {
	int to;
	int value;
	struct _line* next;
}line;
typedef int D[2];//0 for value and 1 for time stamp
typedef int E[3];//[0] start [1] end [2] price
D value[100001];//from 1~n cities call by rank value[0] is never uesd
list way[100001];//keep a record of the way for best
static int in[100001];//from 1~n cities call by rank keep a record of IN_INDEX in[0] is never used
line edge[100001];
static int M;
int cmp(const void*, const void *);
int find_max(int);
int main() {
	int route_value=0;
	int N;
	int start_choose;
	register int n, m;
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	scanf("%d %d", &n, &m);
	N = n;
	M = m;
	for (--m;~m;--m) {
		scanf("%d", &n);
		line temp = edge[n];
		scanf("%d", &(edge[n].to));
		scanf("%d", &(edge[n].value));
		edge[n].next = &temp;
	}
	n = N;
	for (n;n;--n) {
		if (!in[n]) {
			value[n][1] = 1;
			m=find_max(n);//find the max route start from n;
		}
		if (m > route_value) {
			route_value = m;
			start_choose = n;
		}
	}
	list temp = way[start_choose];
	printf("%d\t", start_choose);
	for (;temp.num > 0;temp = *temp.list) {
		printf("%d\t", temp.num);
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
int find_max(int n) {
	if (!edge[n].to) {
		value[n][0] = 0;
		way[n].list = NULL;
		way[n].num = -1;
		value[n][1] = 1;
		return 0;
	}
	line* temp;
	int max = 0;
	int tmp;
	int rank;
	for (temp=edge+n;temp->to;temp=temp->next) {
		if (value[temp->to][1]) tmp = value[temp->to][0] + temp->value;
		else {
			value[temp->to][0] = find_max(temp->to);
			tmp = value[temp->to][0] + temp->value;
			value[temp->to][1] = 1;
		}
		if (max<tmp) {
			max = tmp;
			rank = temp->to;
		}
	}
	value[n][0] = max;
	way[n].num = rank;
	way[n].list = &way[rank];
	return max;
}