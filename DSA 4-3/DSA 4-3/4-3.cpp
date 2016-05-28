#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_
#include<stdio.h>
#include<malloc.h>
void build(int*, int);
void fix(int*, int, int);
inline void swap(int*a, int*b) { int temp = *a;*a = *b;*b = temp; }
int main() {
	int n, k;
#ifndef _DEBUG_
	fread(&n, sizeof(int), 1, stdin);
#endif
#ifdef _DEBUG_
	scanf("%d", &n);
#endif
#ifndef _DEBUG_
	fread(&k, sizeof(int), 1, stdin);
#endif
#ifdef _DEBUG_
	scanf("%d", &k);
#endif
	int *data = new int[k + 1];
#ifndef _DEBUG_
	fread(data + 1, sizeof(int), n, stdin);
#endif
#ifdef _DEBUG_
	for (int i = 1;i < k + 1;i++) {
		scanf("%d", data + i);
	}
#endif
	build(data, k);
	for (int i = n - k;i--;) {
#ifndef _DEBUG_
		fread(data, sizeof(int), 1, stdin);
#endif
#ifdef _DEBUG_
		scanf("%d", data);
#endif
		if (data[0] < data[1]) {
			data[1] = data[0];
			fix(data, 1, k);
		}
	}
	for (;k--;) {
		printf("%d\n", data[1]);
		data[1] = data[k+1];
		fix(data, 1, k);
	}
	return 0;
}
void fix(int *a, int i, int size)
{
	int lch = i<<1; 
	int rch = lch + 1;
	int temp = i;
	if (i <= (size >>1))
	{
		if (lch <= size&&a[lch]>a[temp])
		{
			temp = lch;
		}
		if (rch <= size&&a[rch]>a[temp])
		{
			temp = rch;
		}
		if (temp != i)
		{
			swap(a+i, a+temp);
			fix(a, temp, size);
		}
	}
}
void build(int *a, int size)
{
	int i;
	for (i = (size>>1);i;--i) 
	{
		fix(a, i, size);
	}
}