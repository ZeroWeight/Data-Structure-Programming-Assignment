#include<stdio.h>
#include<iostream>
#define check(n) (bitmap[n >> 3] & (0x80 >> (n & 0x07)))// check the bit
#define reverse(n) (bitmap[n >> 3] ^= (0x80 >> (n & 7)))//reverse the bit
#define father(n) (n>>1)
#define Lchild(n) (n<<1)
#define Rchild(n) ((n<<1)+1)
char bitmap[1 << 18];
inline int find_start(int n);//find the start of bit(include)
inline int find_end(int n);//find the end of the bit(include)
int main() {
	
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