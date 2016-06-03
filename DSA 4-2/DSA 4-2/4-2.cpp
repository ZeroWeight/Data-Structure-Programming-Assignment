#undef  _DEBUG_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define M 2015011
#define N 83
typedef struct _list {
	char* string;
	short find;
	struct _list* next;
}list;
typedef list* head;
int find(const char* const, const int);
inline int hash(const char* const, const int);
int min_represent(const char* const, const int);
const short key[] = {
	3,5,7,11,13,
	17,19,23,29,31,
	37,41,43,47,53,
	59,61,67,71,73,
	79,83,89,97,101,103 };
const short value[N] = {
	229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743
};
head table[M];
int count;
char read_in[1 << 20];
int main() {
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	int m, n;
	scanf("%d%d\n", &m, &n);
	char *s = (char*)malloc(sizeof(char) * (n + 1));
	for (; count < m; ++count) {
#ifdef _DEBUG_
		gets_s(s, n + 1);
#else
		fread(s, sizeof(char), n + 1, stdin);
		s[n] = 0;
#endif
		printf("%d\n", find(s, n));
	}
	return 0;
}
int min_represent(const char* const s, const int n) {
	int i = 0, j = 1, k = 0;
	for (; i < n && j < n && k < n; ) {
		if (s[(i + k) % n] == s[(j + k) % n]) ++k;
		else {
			if (s[(i + k) % n] > s[(j + k) % n]) i += k + 1;
			else j += k + 1;
			if (i == j) ++j;
			k = 0;
		}
	}
	return i < j ? i : j;
}
int find(const char* const s, const int n) {
	head H;
	char* temp = (char*)malloc(sizeof(char) * (n + 1));
	int min = min_represent(s, n);
	for (int i = 0;i < n;i++) {
		temp[i] = s[(i + min) % n];
	}
	temp[n] = 0;
	int h = hash(temp, n);
	if (!table[h]) {
		table[h] = (head)malloc(sizeof(list));
		table[h]->string = (char*)malloc(sizeof(char) * (n + 1));
		strcpy(table[h]->string, temp);
		table[h]->next = NULL;
		table[h]->find = count;
		free(temp);
		return count;
	}
	if (!strcmp(table[h]->string, temp)) {
		free(temp);
		return table[h]->find;
	}
	H = table[h];
	while (H->next) {
		if (!strcmp(H->next->string, temp)) {
			free(temp);
			return H->next->find;
		}
	}
	H->next = (head)malloc(sizeof(list));
	H->next->next = NULL;
	H->next->find = count;
	H->next->string = (char*)malloc(sizeof(char) * (n + 1));
	strcpy(H->next->string, temp);
	free(temp);
	return count;
}
inline int hash(const char* const s, const int n) {
	int pi = 1;
	for (int i = n;i--;) {
		pi *= key[s[i] - 'a' + 1] * value[i%N];
	}
	pi %= M;
	pi += M;
	pi %= M;
	return pi;
}