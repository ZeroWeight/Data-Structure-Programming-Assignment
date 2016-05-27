#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int main() {
	int n;
	int i;
	char x;
	int temp;
	bool** arr1;
	bool** arr2;
	bool** arr3;
	bool* player;
	register bool**cur1;
	scanf("%d", &n);
	arr1 = new bool*[n];
	arr2 = new bool*[n];
	arr3 = new bool*[n];
	player = (bool*)calloc(n, sizeof(bool));
	for (cur1=arr1;cur1-arr1 < n;cur1++) {
		scanf("%d", &temp);
		*cur1 = player + temp - 1;
	}
	for (cur1 = arr2;cur1 - arr2 < n;cur1++) {
		scanf("%d", &temp);
		*cur1 = player + temp - 1;
	}
	for (cur1 = arr3;cur1 - arr3 < n;cur1++) {
		scanf("%d", &temp);
		*cur1 = player + temp - 1;
	}
	int m;
	scanf("%d", &m);
	while (true) {
	s1:
		if (!**arr1) {
			if (*arr1 - player == m - 1) {
				putchar('A');
				break;
			}
			**arr1 = true;
			arr1++;
		}
		else {
			arr1++;
			goto s1;
		}
	s2:
		if (!**arr2) {
			if (*arr2 - player == m - 1) {
				putchar('B');
				break;
			}
			**arr2 = true;
			arr2++;
		}
		else {
			arr2++;
			goto s2;
		}
	s3:
		if (!**arr3) {
			if (*arr3 - player == m - 1) {
				putchar('C');
				break;
			}
			**arr3 = true;
			arr3++;
		}
		else {
			arr3++;
			goto s3;
		}
	}
	return 0;
}