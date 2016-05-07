#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#define Check(n) (bitmap[n >> 3] & (0x80 >> (n & 0x07)))// check the bit
#define Reverse(n) (bitmap[n >> 3] ^= (0x80 >> (n & 7)))//reverse the bit
#define Rchild(n) ((n<<1)+1)
#define Lchild(n) (n<<1)
char bitmap[1 << 18];
int sum[1 << 21];
void initial(const int, const int, const int);
inline void pushdown(const int, const int, const int);
void reverse(const int, const int, const int, const int, const int);
int query(const int, const int, const int, const int, const int);
int main() {
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	register char op;
	register int n, m, l, r;
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	scanf("%d%d", &n, &m);
	initial(1, n,1);
	for (;m--;) {
		scanf("\n%c%d%d", &op, &l, &r);
		if (op == 'H') reverse(l, r,1,n,1);
		else printf("%d\n", query(l, r,1,n,1));
	}
	return 0;
}
void initial(const int L, const int R , const int root) {
	sum[root] = R - L + 1;
	if (L == R) return;
	int mid = (L + R) / 2;
	initial(L, mid, root * 2);
	initial(mid + 1, R, root * 2 + 1);
}
inline void pushdown(const int L, const int R, const int root) {
	if (Check(root)) {
		Reverse(Lchild(root));
		Reverse(Rchild(root));
		int mid = ((L + R) >> 1);
		sum[Lchild(root)] = mid - L + 1 - sum[Lchild(root)];
		sum[Rchild(root)] = R - mid - sum[Rchild(root)];
		Reverse(root);
	}
}
void reverse(const int l, const int r, const int L, const int R , const int root) {
	if (l <= L && R <= r) {
		Reverse(root);
		sum[root] = R - L + 1 - sum[root];
		return;
	}
	pushdown(L, R, root);
	int mid = ((L + R) >> 1);
	if (l <= mid) reverse(l, r, L, mid, root * 2);
	if (r > mid) reverse(l, r, mid + 1, R, root * 2 + 1);
	sum[root] = sum[root * 2] + sum[root * 2 + 1];
}
int query(const int l, const int r, const int L, const int R, const int root) {
	if (l <= L && R <= r) return sum[root];
	pushdown(L, R, root);
	int res = 0, mid = (L + R) / 2;
	if (l <= mid) res += query(l, r, L, mid, root * 2);
	if (r > mid) res += query(l, r, mid + 1, R, root * 2 + 1);
	return res;
}

