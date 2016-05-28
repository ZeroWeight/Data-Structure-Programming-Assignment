#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
int main() {
	srand(time(0));
	FILE* answer, *sheet;
	answer=fopen("J:/answer.txt", "w");
	sheet = fopen("J:/sheet.txt", "w");
	int n, k;
	n = rand() % 9999999 + 1;
	int* data = new int[n];
	k = rand() % (n - 1) + 1;
	fprintf(sheet,"%d\n", n);
	fprintf(sheet,"%d\n", k);
	for (int i = 0;i < n;i++) {
		data[i] = rand();
		fprintf(sheet,"%d\n", data[i]);
	}
	std::sort(data, data + n);
	for (int i = k;i--;) {
		fprintf(answer, "%d\n", data[i]);
	}
}