#define _CRT_SECURE_NO_WARNINGS
#include"temperature.h"
#include<stdlib.h>
#include<iostream>
#include<math.h>
#define min(x,y) (((x)<(y))?(x):(y))
#define max(x,y) (((x)>(y))?(x):(y))
typedef struct _node {
	int  sign;
	long long L;
	long long R;
	long long  U;
	long long  D;
	int  node;
	long long sum;
	struct _node* ch1;
	struct _node* ch2;
}node;
typedef int  (*_cmp)(const void *, const void *);
typedef long long  point[3];
_cmp cmp[2];
inline int  cmp_x(const void *, const void *);
inline int  cmp_y(const void *, const void *);
void build(node*, point*,const int );
long long total(const node*, const long long , const long long , const long long , const long long ,int *);
int  main() {
	cmp[0] = cmp_x;
	cmp[1] = cmp_y;
	point* station;
	node* root = (node*)malloc(sizeof(node));
	root->sign = 0;
	int  x1, x2, y1, y2;
	int  n = GetNumOfStation();
	int  status;
	station = (point*)malloc(n*sizeof(point));
	const int  N = n;
	long long temp;
	for (;n--;) {
		GetStationInfo(n, &x1, &x2, &y1);
		station[n][0] = (long long)x1;
		station[n][1] = (long long)x2;
		station[n][2] = (long long)y1;
	}
		
	build(root, station, N);
	long long X1, X2, Y1, Y2;
	for (status = GetQuery(&x1, &y1, &x2, &y2);status;status = GetQuery(&x1, &y1, &x2, &y2)) {
		X1 = max(x1, root->L);
		X2 = min(x2, root->R);
		Y1 = max(y1, root->D);
		Y2 = min(y2, root->U);
		temp = total(root, X1, X2, Y2, Y1, &n);
		Response(n ? (int)(temp / n) : 0);
	}
	return 0;
}
inline int  cmp_x(const void* p, const void * q) {
	if (((point*)p)[0][0] - ((point*)q)[0][0])
		return (int)(((point*)p)[0][0] - ((point*)q)[0][0]);
	if (((point*)p)[0][1] - ((point*)q)[0][1])
		return (int)(((point*)p)[0][1] - ((point*)q)[0][1]);
	return (int)(((point*)p)[0][2] - ((point*)q)[0][2]);
}
inline int  cmp_y(const void* p, const void * q) {
	if (((point*)p)[0][1] - ((point*)q)[0][1])
		return (int)(((point*)p)[0][1] - ((point*)q)[0][1]);
	if (((point*)p)[0][0] - ((point*)q)[0][0])
		return (int)(((point*)p)[0][0] - ((point*)q)[0][0]);
	return (int)(((point*)p)[0][2] - ((point*)q)[0][2]);
}
void build(node* root, point*list,const int  n) {
	if (!n) return;
	if (list[0][0]==list[n-1][0]&&list[0][1]==list[n-1][1]) {
		root->sum = 0;
		for (int i = 0;i < n;i++) {
			root->sum += (int)list[i][2];
		}
		root->ch1 = root->ch2 = NULL;
		root->D = root->U = list[0][1];
		root->L = root->R = list[0][0];
		root->node = n;
		root->sign = -1;
	}
	else {
		qsort(list, n, sizeof(point), cmp[root->sign]);
		root->ch1 = (node*)malloc(sizeof(node));
		root->ch2 = (node*)malloc(sizeof(node));
		if (root->sign&&list[0][1] == list[n - 1][1]) root->sign ^= 1;
		if (!root->sign&&list[0][0] == list[n - 1][0]) root->sign ^= 1;
		root->ch1->sign = root->ch2->sign = root->sign ^ 1;
		build(root->ch1, list, n >> 1);
		build(root->ch2, list + (n >> 1), n - (n >> 1));
		root->D = min(root->ch1->D, root->ch2->D);
		root->U = max(root->ch1->U, root->ch2->U);
		root->L = min(root->ch1->L, root->ch2->L);
		root->R = max(root->ch1->R, root->ch2->R);
		root->node = root->ch1->node + root->ch2->node;
		root->sum = root->ch1->sum + root->ch2->sum;
	}
}
long long total(const node* root, const long long  l, const long long  r, const long long  u, const long long  d,int * count) {
	if (l > r || u < d) {
		*count = 0;
		return 0;
	}
	if (root->L == l&&root->R == r&&root->U == u&&root->D == d) {
		*count = root->node;
		return root->sum;
	}
	else if (root->L<=l&&root->R>=r&&root->U >= u&&root->D <= d) {
		if (root->sign >= 0) {
			long long tmp;
			int count1 = 0, count2 = 0;
			if (root->sign) {
				//by y
				if ((root->ch1->U >= u&&root->ch1->U!=root->ch2->D)|| root->ch1->U > u) {
					// in ch1(lower)
					tmp = total(root->ch1, max(l, root->ch1->L), min(root->ch1->R, r), min(root->ch1->U, u), max(d, root->ch1->D), count);
					return tmp;
				}
				else if ((root->ch2->D <= d&&root->ch1->U != root->ch2->D)|| root->ch2->D < d) {
					//in ch2(upper)
					tmp = total(root->ch2, max(l, root->ch2->L), min(root->ch2->R, r), min(root->ch2->U, u), max(d, root->ch2->D), count);
					return tmp;
				}
				else {
					long long ave1 = total(root->ch1, max(l,root->ch1->L), min(root->ch1->R,r), root->ch1->U, max(d,root->ch1->D), &count1);
					long long ave2 = total(root->ch2, max(l, root->ch2->L), min(root->ch2->R, r), min(u,root->ch2->U), root->ch2->D, &count2);
					*count = count1 + count2;
					return ave1 + ave2;
				}
			}
			else {
				//by x
				if ((root->ch1->R >= r&&root->ch1->R != root->ch2->L)|| root->ch1->R > r) {
					// in ch1(left)
					tmp = total(root->ch1, max(l, root->ch1->L), min(root->ch1->R, r), min(root->ch1->U, u), max(d, root->ch1->D), count);
					return tmp;
				}
				else if ((root->ch2->L <= l&&root->ch1->R != root->ch2->L)|| root->ch2->L < l) {
					//in ch2(right)
					tmp = total(root->ch2, max(l, root->ch2->L), min(root->ch2->R, r), min(root->ch2->U, u), max(d, root->ch2->D), count);
					return tmp;
				}
				else {
					int  count1, count2;
					long long ave1 = total(root->ch1, max(root->ch1->L,l),root->ch1->R, min(root->ch1->U, u), max(d, root->ch1->D), &count1);
					long long ave2 = total(root->ch2, root->ch2->L, min(root->ch2->R,r), min(root->ch2->U, u), max(root->ch2->D, d), &count2);
					*count = count1 + count2;
					return ave1 + ave2;
				}
			}
		}
		else {
			*count = 1;
			return root->sum;
		}
	}	
	else {
		*count = 0;
		return 0;
	}
}