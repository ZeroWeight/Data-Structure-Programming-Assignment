#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//#include<iostream>
#include<stdlib.h>
#define Check(n) (bitmap[n >> 3] & (0x80 >> (n & 0x07)))// check the bit
#define Reverse(n) (bitmap[n >> 3] ^= (0x80 >> (n & 7)))//reverse the bit
#define Set(n) (ever_reach[n >> 3] |= (0x80 >> (n & 0x07)))// set the bit to 1
#define Ever(n) (ever_reach[n >> 3] & (0x80 >> (n & 0x07)))
#define Father(n) (n>>1)
#define Lchild(n) (n<<1)
#define Rchild(n) ((n<<1)+1)
char bitmap[1 << 18];
char ever_reach[1 << 18];
int find_start[1 << 21];
int find_end[1 << 21];
void initial(int,int,int a=1);
void reverse(int, int,int root=1);
int query(int, int, int root = 1);
int main() {
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	int n, m;
	int l, r;
	register char op;
	scanf("%d%d", &n, &m);
	initial(1, n);
	for (int i = 0; i < m; ++i) {
		scanf("\n%c%d%d", &op, &l, &r);
		if (op == 'H') reverse(l, r);
		else printf("%d\n", query(l, r));
	}
	return 0;
}
void initial(int l, int r, int root) {
	if (l == r) find_end[root] = find_start[root] = l;
	else {
		int mid = ((l + r) >> 1);
		initial(l, mid, Lchild(root));
		initial(mid + 1, r, Rchild(root));
		find_start[root] = l;
		find_end[root] = r;
	}
}
void reverse(int l, int r, int root) {
	if (l > find_end[root] || r < find_start[root]) return;
	if (l == find_start[root] && r == find_end[root]) {
		Reverse(root);
		return;
	}
	int temp = find_end[Lchild(root)];
	if (Check(root)) Reverse(Rchild(root)), Reverse(Lchild(root)),Reverse(root);
	if (temp >= r) reverse(l, r, Lchild(root));
	else if (temp < l) reverse(l, r, Rchild(root));
	else {
		reverse(l, temp, Lchild(root));
		reverse(temp + 1, r, Rchild(root));
	}
}
int query(int l, int r, int root) {
	if (l > find_end[root] || r < find_start[root]) return 0;//ill
	if (find_end[root] == find_start[root]) return (Check(root)==0);//leaf
	if (l == find_start[root] && r == find_end[root]) {
		if (Check(root))
		{
			return 0;
		}
		else return find_end[root] - find_start[root] + 1;
	}
	if (Check(root)) Reverse(Rchild(root)), Reverse(Lchild(root)), Reverse(root);
	int temp = find_end[Lchild(root)];
	int tmp;
	if (temp >= r) tmp = query(l, r, Lchild(root));
	else if (temp < l) tmp = query(l, r, Rchild(root));
	else {
		tmp = query(l, temp, Lchild(root)) + query(temp + 1, r, Rchild(root));
	}
	if (Check(root)) tmp = r-l+1 - tmp;
	return tmp;
}