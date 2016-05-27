#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
const int N = 1 << 14;
char name[N][9];
char read_in[1 << 20];
int tot, count[N], head[N], next[N];
int zip(char *s);
int create(char *s);
int find(char *s);
int main(){
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	int n, max = 0;
	scanf("%d", &n);
	register char s[9];
	char* max_name;
	for (;n--;) {
		scanf("\n%s", s);
		int hash_value = find(s);
		if (!hash_value) hash_value = create(s);
		if (++count[hash_value] > max){
			max = count[hash_value];
			max_name = name[hash_value];
		}
	}
	printf("%s %d\n", max_name, max);
	return 0;
}
int zip(char *s) {
	int key = 0;
	for (int i = 0; s[i]; ++i) {
		key += (s[i] - 'a' + 1) & 7;
		key <<= 3;
	}
	key >>= 3;
	key &= (0x3FFF);
	return (int)key;
}
int create(char *s) {//if never found a hash code create it with a single list
	int key = zip(s);
	memcpy(name[++tot], s, sizeof s);
	next[tot] = head[key];//add the following list
	head[key] = tot;//create the node
	return tot;
}
int find(char *s) {//check whether the hash code has a string
	int key = zip(s);
	for (int i = head[key]; i; i = next[i])
		if (!strcmp(s, name[i])) return i;
	return 0;//if fail return 0
}