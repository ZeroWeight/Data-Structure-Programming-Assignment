#include <stdio.h>
#include <malloc.h>
#include <string.h>
int find(char*);
int main(){
	int m, n;
	scanf("%d%d\n", &m, &n);
	char *s = (char*)malloc(sizeof(char) * n);
	for (int i = 0; i < m; ++i){
		gets(s);
		printf("%d\n", find(s, n));
	}
	return 0;
}
int min_represent(char *s, int n){
	int i = 0, j = 1, k = 0;
	for (; i < n && j < n && k < n; ){
		if (s[(i + k) % n] == s[(j + k) % n]) ++k;
		else{
			if (s[(i + k) % n] > s[(j + k) % n]) i += k + 1;
			else j += k + 1;
			if (i == j) ++j;
			k = 0;
		}
	}
	return i < j ? i : j;
}
int find(char *s, int n){
	int tmp = min_represent(s, n);
	char *s_ = (char*)malloc(sizeof(char) * n);
	for (int i = 0; i < n; ++i) s_[i] = s[(tmp + i) % n];
}
