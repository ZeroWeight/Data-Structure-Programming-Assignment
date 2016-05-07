#include<stdio.h>
#include<iostream>
#define check(n) (bitmap[n >> 3] & (0x80 >> (n & 0x07)))
#define reverse(n) (bitmap[n >> 3] ^= (0x80 >> (n & 7)))
char bitmap[1 << 18];
int main() {
	reverse(100);
	reverse(101);
	std::cout << check(100) << std::endl;
	std::cout << check(101) << std::endl;
	std::cout << check(102) << std::endl;
	reverse(100);
	std::cout << check(100) << std::endl;
}