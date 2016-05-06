#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int main() {
	int m = 0;
	int N, M;
	scanf("%d", &N);
	scanf("%d", &M);
	m += N;
	m *= 100;
	m += M;
	;
	exit(m);
	int temp;
	for (int j = 0;j < M;j++) {
		scanf("%d", &temp);
		m += temp;
		m *= 100;
		scanf("%d", &temp);
		m += temp;
		m *= 100;
		scanf("%d", &temp);
		m += temp;
		m *= 100;
	}
	exit(m);
}