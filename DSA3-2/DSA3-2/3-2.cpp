#include<stdio.h>
// 1-> 1<<20
//2 3->1<<19
//4 5 6 7->1<<18   
//..
//from 1<<20 n>>= 20-- until n==1
//father   n>>1
//son n<<1,n<<1+1
//total:1<<21 2097152
//in char: 1<<18 262144
//(bitmap[next >> 3] & (0x80 >> (next & 0x07))) check next
//bitmap[i >> 3] |= (0x80 >> (i & 0x07)) write next to 1
//bitmap[i>>3]&=~(0x80 >> (i & 0x07)) write to 0