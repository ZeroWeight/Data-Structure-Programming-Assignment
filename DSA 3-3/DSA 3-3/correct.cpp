#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int a[50000][3];
	for (;--n;) {
		scanf("%d %d %d", &a[n][0], &a[n][1], &a[n][2]);
	}
	for (;--m;) {
		int x1, x2, x3, x4;
		scanf("%d %d %d %d", &x1, &x2, &x3, &x4);
		int sum = 0;
		int node = 0;
		for (int i = 0;i < 50000;i++) {
			if (a[i][0] >= x1&&a[i][0] <= x3&&a[i][1] >= x2&&a[i][1] <= x4) {
				node++;
				sum += a[i][2];
			}
		}
		if (node)
			printf("%d\n", sum / node);
		else
			printf("0\n");
	}
}