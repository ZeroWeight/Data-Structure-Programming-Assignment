#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#define Check(n) (bitmap[n >> 3] & (0x80 >> (n & 0x07)))// check the bit
#define Reverse(n) (bitmap[n >> 3] ^= (0x80 >> (n & 7)))//reverse the bit
#define Father(n) (n>>1)
#define Lchild(n) (n<<1)
#define Rchild(n) ((n<<1)+1)
char bitmap[1 << 18];
char ever_reach[1 << 18];
inline int find_start(int n);//find the start of bit(include)
inline int find_end(int n);//find the end of the bit(include)
inline int count(int n);
void reverse(int, int,int root=1);
int query(int, int, int root = 1);
int main() {
	int n, m;
	int l, r;
	register char op;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; ++i) {
		scanf("\n%c%d%d", &op, &l, &r);
		if (op == 'H') reverse(l, r);
		else printf("%d\n", query(l, r));
	}
	return 0;
}
inline int find_start(int n) {
	int temp = n;
	int volume = 20;
	for (;n>>1;) {
		--volume;
		n >>= 1;
	}
	return 1 + (1 << volume)*(temp - (1 << (20 - volume)));
}
inline int find_end(int n) {
	int temp = n;
	int volume = 20;
	for (;n >> 1;) {
		--volume;
		n >>= 1;
	}
	return (1 << volume)*(1+temp - (1 << (20 - volume)));
}
inline int count(int n) {
	int volume = 20;
	for (;n >> 1;) {
		--volume;
		n >>= 1;
	}
	return 1 << volume;
}
void reverse(int l, int r, int root) {
	if (l > find_end(root) || r < find_start(root)) return;
	if (l == find_start(root) && r == find_end(root)) {
		Reverse(root);
		return;
	}
	int temp = find_end(Lchild(root));
	reverse(l, temp, Lchild(root));
	reverse(temp + 1, r, Rchild(root));
}
int query(int l, int r, int root) {
	if (l > find_end(root) || r < find_start(root)) return 0;//ill
	if (find_end(root) == find_start(root)) return (Check(root)==0);//leaf
	int temp = find_end(Lchild(root));
	int tmp = query(l, temp, Lchild(root)) + query(temp + 1, r, Rchild(root));
	if (Check(root)) tmp = count(root) - tmp;
	return tmp;
}