#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define abs(x) ((x)>0?(x):-(x))
int cmp(const void*, const void*);
class village {
public:
	short x;//refined
	long w;
};
int main() {
	int n,x,j;
	unsigned long min = 0;
	long w=0;
	register int i;//refined
	village* p;
	scanf("%d", &n);
	p = new village[n];
	x = n;
	for (i = 0;i < n;i++) {
		scanf("%d %lld ", &p[i].x, &p[i].w);
	}
	qsort(p, n, sizeof(village), cmp);
	//because we have to go over the n size no less than O(n)
	for (i = 0;i < n;i++) {
		w -= p[i].w;
	}
	for (i = 1;i < n;i++) {
		w += 2 * p[i-1].w;
		if (w >= 0) {
			x = i-1;
			break;
		}
	}
	for (i = 0;i < n;i++) {
		min += abs(p[x].x - p[i].x)*p[i].w;
	}
	//unable to shrink
	printf("%d\n%lu ", p[x].x, min);
	return 0;
}
int cmp(const void *p1, const void *p2)
{
	return ((village*)p1)->x - ((village*)p2)->x;
}
