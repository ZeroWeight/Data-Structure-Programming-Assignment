#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define alpha(n) ((n)-'a'+1)
#define beta(n) ((n)+'a'-1)
#define NUM 32
long long code[10000];
int number[10000];
char read_in[1 << 20];
int rank;
long long zip(char*);
void unzip(char*, long long);
int main() {
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	int n;
	register int i;
	long long temp;
	scanf("%d", &n);
	char name[9];
	for (;n--;) {
		scanf("%s", name);
		temp = zip(name);
		for (i = rank;i--;) {//sort necessary?
			if (code[i] == temp) break;
		}
		if (i == -1) {
			code[rank] = temp;
			number[rank] = 1;
			rank++;
		}
		else {
			number[i]++;
		}
	}
	n = rank - 1;
	for (i = rank;i--;) {
		if (number[n] < number[i]) n = i;
	}
	unzip(name, code[n]);
	printf("%s\t%d\t%d\n", name, number[n],n);
	return 0;
}
long long zip(char*s) {
	long long result = 0;
	for (int i = 0;s[i];i++) {
		result += alpha(s[i]);
		result <<= 5;
	}
	return result >>= 5;
}
void unzip(char*s, long long n) {
	char buffer[9];
	int count = 0;
	int i;
	for (;n;n >>= 5) {
		buffer[count] = n&0x1F;
		++count;
	}
	for (i=0;count--;i++) {
		s[i] = beta(buffer[count]);
	}
	s[i] = 0;
}