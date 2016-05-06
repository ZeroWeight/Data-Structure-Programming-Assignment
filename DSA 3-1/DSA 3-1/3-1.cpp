#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct _list {
	int num;
	struct _list* list;
} list;
typedef int D[2];//0 for value and 1 for time stamp
typedef int E[3];//[0] start [1] end [2] price
D value[100001];//from 1~n cities call by rank value[0] is never uesd
list way[100001];//keep a record of the way for best
static int in[100001];//from 1~n cities call by rank keep a record of IN_INDEX in[0] is never used
static int from[10000];//keep a record of the route
static int route_value;
static int start_choose;
int N, M;
int time_stamp;
E edge[1000000];// keep the record of edge
int cmp(const void*, const void *);
int find_max(int);
int bin_search_start(int,int,int);
int main() {
	register int n, m;
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	scanf("%d %d", &n, &m);
	N = n;
	M = m;
	for (--m;~m;--m) {
		scanf("%d %d %d", &edge[m][0], &edge[m][1], &edge[m][2]);
		++in[edge[m][1]];
	}
	qsort(edge, M,sizeof(E), cmp);
	for (n;n;--n) {
		if (!in[n]) {
			++time_stamp;
			value[n][1] = time_stamp;
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
	int start=bin_search_start(0,n,M);
	if (!(~start)) {
		value[n][0] = 0;
		way[n].list = NULL;
		way[n].num = -1;
		value[n][1] = time_stamp;
		return 0;
	}
	int max = 0;
	int temp;
	int rank;
	for (;edge[start][0] == n;++start) {
		if (value[edge[start][1]][1]) temp = value[edge[start][1]][0] + edge[start][2];
		else {
			value[edge[start][1]][0] = find_max(edge[start][1]);
			temp = value[edge[start][1]][0] + edge[start][2];
			value[edge[start][1]][1] = time_stamp;
		}
		if (max<temp) {
			max = temp;
			rank = edge[start][1];
		}
	}
	value[n][0] = max;
	way[n].num = rank;
	way[n].list = &way[rank];
	return max;
}
int bin_search_start(int s,int n,int e) {
	if (s == e) {
		if (edge[s][0] == n) return s;
		else return -1;
	}
	if (edge[(s + e) >> 1][0] < n) return bin_search_start((((s + e) >> 1) + 1), n, e);
	return bin_search_start(s, n, (s + e) >> 1);
}