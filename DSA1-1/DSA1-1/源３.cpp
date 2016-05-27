#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int main() {
	int n;
	int i;
	char x;
	int temp;
	int* arr1;
	int* arr2;
	int* arr3;
	bool* player;
	register int*cur1;
	scanf("%d", &n);
	arr1 = new int[n+10];
	arr2 = new int[n+10];
	arr3 = new int[n+10];
	player = new bool[n+10];
	for (cur1 = arr1;cur1 - arr1 < n;cur1++) {
		scanf("%d", cur1);
	}
	for (cur1 = arr2;cur1 - arr2 < n;cur1++) {
		scanf("%d", cur1);
	}
	for (cur1 = arr3;cur1 - arr3 < n;cur1++) {
		scanf("%d", cur1);
	}
	int m;
	scanf("%d", &m);
	while (true) {
	s1:
		if (player[*arr1]) {
			if (*arr1==m) {
				putchar('A');
				break;
			}
			player[*arr1] = false;
			arr1++;
		}
		else {
			arr1++;
			goto s1;
		}
	s2:
		if (player[*arr2]) {
			if (*arr2 == m) {
				putchar('B');
				break;
			}
			player[*arr2] = false;
			arr2++;
		}
		else {
			arr2++;
			goto s2;
		}
	s3:
		if (player[*arr3]) {
			if (*arr3 == m ) {
				putchar('C');
				break;
			}
			player[*arr3] = false;
			arr3++;
		}
		else {
			arr3++;
			goto s3;
		}
	}
	return 0;
}