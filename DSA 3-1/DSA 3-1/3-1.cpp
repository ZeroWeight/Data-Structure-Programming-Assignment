#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//#include<algorithm>
typedef int D[2];//0 for value and 1 for time stamp
D value[100001];//from 1~n cities call by rank
int in[100001];//from 1~n cities call by rank keep a record of IN_INDEX
int from[10000];//keep a record of the route
int route_value;
int start_choose;
int N, M;
int time_stamp;
int route_num;//a index of number of node
typedef int E[3];//[0] start [1] end [2] price
E edge[100000];// keep the record of edge
int cmp(const void*, const void *);
int find_max(int);
void show_route(int);
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
	for (--n;~n;--n) {
		if (!in[n]) {
			++time_stamp;
			m=find_max(n);//find the max route start from n;
		}
		if (m > route_value) {
			route_value = m;
			start_choose = n;
		}
	}
	show_route(start_choose);
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
		if (value[n][1] == time_stamp) return value[n][0];
		else return 0;
	}
	int max = 0;
	int temp;
	for (;edge[start][0] == n;++start) {
		if (value[edge[start][1]][1] != time_stamp &&
			value[edge[start][1]][0] < value[edge[start][0]][0] + edge[start][2]) {
			value[edge[start][1]][1] = time_stamp;
			value[edge[start][1]][0] = value[edge[start][0]][0] + edge[start][2];
			/*from[edge[start][1]] = edge[start][0];*/
			temp = find_max(edge[start][1]);
			if (max<temp) {
				max = temp;
			}
		}
	}
	return max;
}
void show_route(int n) {
	int start = bin_search_start(0,n,M);
	if (!(~start)) return;
	for (;edge[start][0] == n;++start) {
		if (value[edge[start][1]][1] != time_stamp ||
			value[edge[start][1]][0] < value[edge[start][0]][0] + edge[start][2]) {
			value[edge[start][1]][1] = time_stamp;
			value[edge[start][1]][0] = value[edge[start][0]][0] + edge[start][2];
			from[edge[start][1]] = edge[start][0];
		}
	}
	int max_rank = 0;
	int i = N - 1;
	for (i;~i;--i) {
		if (value[i] >= value[max_rank]) max_rank = i;
	}
	int buffer[100000];
	int buffer_num = 0;
	for (;from[max_rank];++buffer_num) {
		buffer[buffer_num] = max_rank;
		max_rank = from[max_rank];
	}
	for (--buffer_num;~buffer_num;--buffer_num) {
		printf("%d/t", buffer[buffer_num]);
	}
}
int bin_search_start(int s,int n,int e) {
	if (s == e) {
		if (edge[s][0] == n) return s;
		else return -1;
	}
	if (edge[(s + e) >> 1][0] < n) return bin_search_start((((s + e) >> 1) + 1), n, e);
	return bin_search_start(s, n, (s + e) >> 1);
}