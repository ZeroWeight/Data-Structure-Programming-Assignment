#include<stdlib.h>
#include<stdio.h>
#include<iostream>
using namespace std;
struct student {
	int name;
	int c[3];
	bool in;
};
int f1(const void*s1, const void*s2);
int f2(const void*s1, const void*s2);
int f3(const void*s1, const void*s2);
int main() {
	int n;
	cin >> n;
	student* s = (student*)malloc(sizeof(student) * 500000);
	student** s1 = (student**)malloc(sizeof(student*) * 500000);
	student** s2 = (student**)malloc(sizeof(student*) * 500000);
	student** s3 = (student**)malloc(sizeof(student*) * 500000);
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < n;j++) {
			s[j].name = j + 1;
			cin >> s[j].c[i];
			s[j].in = true;
		}
	}
	for (int i = 0;i < n;i++) {
		s1[i] = s2[i] = s3[i] = s + i;
	}
	qsort(s1, n, sizeof(student*), f1);
	qsort(s2, n, sizeof(student*), f2);
	qsort(s3, n, sizeof(student*), f3);
	int k;
	cin >> k;
	while (true) {
		int j;
		for (j = 0;!s1[j]->in;j++);
		s1[j]->in = false;
		if (k == s1[j]->name) {
			cout << 'A';break;
		}
		for (j = 0;!s2[j]->in;j++);
		s2[j]->in = false;
		if (k == s2[j]->name) { cout << 'B';break; }
		for (j = 0;!s3[j]->in;j++);
		s3[j]->in = false;
		if (k == s3[j]->name) { cout << 'C';break; }
	}
	return 0;
}
int f1(const void*s1, const void*s2) {
	return (*((student**)s1))->c[0] - (*((student**)s2))->c[0];
}
int f2(const void*s1, const void*s2) {
	return (*((student**)s1))->c[1] - (*((student**)s2))->c[1];
}
int f3(const void*s1, const void*s2) {
	return (*((student**)s1))->c[2] - (*((student**)s2))->c[2];
}