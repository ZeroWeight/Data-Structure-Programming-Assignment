#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int left_of(long long ,long long,long long,long long);
int main() {
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);						//调整缓冲区大小
	int n, m;
	register int i;
	scanf("%d %d", &n, &m);
	long long* x_pos = (long long*)malloc(sizeof(long long)*(n));				//数据：x和y轴上探测器的位置
	long long* y_pos = (long long*)malloc(sizeof(long long)*(n));
	for (i = 0;i < n;i++) {
		scanf("%lld %lld", x_pos + i, y_pos + i);
	}
	for (i = 0;i < m;i++) {
		long long x, y;
		scanf("%lld %lld", &x, &y);
		long long start = -1, end = n;						//初始化：start是点在右的直线号，end是点在左侧的直线号
		while (start != end-1) {						
			if (left_of(x, y, x_pos[(start + end) >> 1], y_pos[(start + end) >> 1])) {	//开始循环，当两条直线的秩只差1，即中间仅有一个区域是停止
				end = (start + end) >> 1;				//如果点在中间直线的左面，将end赋值为中间直线
			}
			else start= (start + end) >> 1;					//如果点在中间直线的右面，将start赋值为中间直线
		}
		printf("%lld\n", end);							//输出为end的值
	}
	return 0;
}

int left_of(long long x,long long y,long long a,long long b) {
	return(a*y + b*x < a*b);							//利用数学知识计算点(x,y)是否在有横竖截距为a,b的直线左侧
}

