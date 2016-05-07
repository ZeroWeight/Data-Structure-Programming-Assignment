#define _CRT_SECURE_NO_WARNINGS
#include"temperature.h"
#include<stdlib.h>
#include<algorithm>
typedef struct _node {
	int sign;
	int L;
	int R;
	int U;
	int D;
	int node;
	int ave;
	struct _node* ch1;
	struct _node* ch2;
}node;
typedef int (*_cmp)(const void *, const void *);
typedef int point[3];
_cmp cmp[2];
int sign;
inline int cmp_x(const void *, const void *);
inline int cmp_y(const void *, const void *);
void build(node*, point*, int);
int average(const node*, const int, const int, const int, const int,int*);
int main() {
	cmp[0] = cmp_x;
	cmp[1] = cmp_y;
	point* station;
	node root;
	int x1, x2, y1, y2;
	int n = GetNumOfStation();
	int status;
	station = (point*)malloc(sizeof(n*sizeof(point)));
	for (;n--;)
		GetStationInfo(n, &station[n][0], &station[n][1], &station[n][2]);
	build(&root, station, n);
	for (status = GetQuery(&x1, &y1, &x2, &y2);status;status = GetQuery(&x1, &y1, &x2, &y2)) {
		Response(average(&root, x1, x2, y1, y2,&n));
	}
	return 0;
}
inline int cmp_x(const void* p, const void * q) {
	if (((point*)p)[0] - ((point*)q)[0])
		return ((point*)p)[0] - ((point*)q)[0];
	return ((point*)p)[1] - ((point*)q)[1];
}
inline int cmp_y(const void* p, const void * q) {
	if (((point*)p)[1] - ((point*)q)[1])
		return ((point*)p)[1] - ((point*)q)[1];
	return ((point*)p)[0] - ((point*)q)[0];
}
void build(node* root, point*list, int n) {
	if (!n) return;
	if (n == 1) {
		root->ave = list[0][2];
		root->ch1 = root->ch2 = NULL;
		root->D = root->U = list[0][1];
		root->L = root->R = list[0][0];
		root->node = 1;
		root->sign = -1;
	}
	else {
		qsort(list, n, sizeof(point), cmp[sign]);
		root->ch1 = (node*)malloc(sizeof(node));
		root->ch2 = (node*)malloc(sizeof(node));
		root->sign = sign;//0 x, 1,y;
		sign ^= 1;
		build(root->ch1, list, n >> 1);
		build(root->ch2, list + (n >> 1) + 1, n - (n >> 1));
		root->D = std::min(root->ch1->D, root->ch2->D);
		root->U = std::max(root->ch1->U, root->ch2->U);
		root->L = std::min(root->ch1->L, root->ch2->L);
		root->R = std::max(root->ch1->R, root->ch2->R);
		root->node = root->ch1->node + root->ch2->node;
		root->ave = root->ch1->ave*root->ch1->node + root->ch2->ave*root->ch2->node;
		root->ave /= root->node;
	}
}
int average(const node* root, const int l, const int r, const int u, const int d,int* count) {
	if (root->L<l&&root->R>r&&root->U > u&&root->D < d) {
		if (root->sign > 0) {
			if (root->sign) {
				//by y
				if (root->ch1->U >= u) {
					// in ch1(lower)
					return average(root->ch1, l, r, u, d,count);
				}
				else if (root->D <= d) {
					//in ch2(upper)
					return average(root->ch2, l, r, u, d, count);
				}
				else {
					int count1, count2;
					int ave1 = average(root->ch1, l, r, root->ch1->U, d, &count1);
					int ave2 = average(root->ch2, l, r, u, root->ch2->D, &count2);
					*count = count1 + count2;
					return (ave1*count1 + ave2*count2) / (*count);
				}
			}
			else {
				//by x
				if (root->ch1->R >= r) {
					// in ch1(left)
					return average(root->ch1, l, r, u, d, count);
				}
				else if (root->ch2->L <= l) {
					//in ch2(right)
					return average(root->ch2, l, r, u, d, count);
				}
				else {
					int count1, count2;
					int ave1 = average(root->ch1, l,root->ch1->R,u,d, &count1);
					int ave2 = average(root->ch2, root->ch2->L, r, u, d, &count2);
					*count = count1 + count2;
					return (ave1*count1 + ave2*count2) / (*count);
				}
			}
		}
		else return root->ave;
	}
	else if (root->L == l&&root->R == r&&root->U == u&&root->D == d) {
		*count = root->node;
		return root->ave;
	}
		
	else {
		*count = 0;
		return 0;
	}
}