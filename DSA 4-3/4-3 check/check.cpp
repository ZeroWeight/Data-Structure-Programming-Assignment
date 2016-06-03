#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
int main() {
	srand(time(0));
	FILE* answer, *sheet;
	answer=fopen("J:/answer.txt", "w");
#ifndef _DEBUG_
	sheet = fopen("J:/sheet.txt", "wb");
#endif
#ifdef _DEBUG_
	sheet = fopen("J:/sheet.txt", "w");
#endif
	int n, k;
	n = rand() % 9999999 + 1;
	int* data = (int*)malloc(n*sizeof(int));
	k = rand() % (n - 1) + 1;
#ifndef _DEBUG_
	fwrite(&n, sizeof(int), 1, sheet);
	fwrite(&k, sizeof(int), 1, sheet);
#endif
#ifdef _DEBUG_
	fprintf(sheet, "%d\n%d\n", n, k);
#endif
	for (int i = 0;i < n;i++) {
		data[i] = rand();
#ifndef _DEBUG_
		fwrite(data + i, sizeof(int), 1, sheet);
#endif
#ifdef _DEBUG_
		fprintf(sheet, "%d\n", data[i]);
#endif
	}
	std::sort(data, data + n);
	for (int i = k;i--;) {
		fprintf(answer, "%d\n", data[i]);
	}
	fclose(answer);
	fclose(sheet);
}