#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int left_of(long long ,long long,long long,long long);
int main() {
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);						//������������С
	int n, m;
	register int i;
	scanf("%d %d", &n, &m);
	long long* x_pos = (long long*)malloc(sizeof(long long)*(n));				//���ݣ�x��y����̽������λ��
	long long* y_pos = (long long*)malloc(sizeof(long long)*(n));
	for (i = 0;i < n;i++) {
		scanf("%lld %lld", x_pos + i, y_pos + i);
	}
	for (i = 0;i < m;i++) {
		long long x, y;
		scanf("%lld %lld", &x, &y);
		long long start = -1, end = n;						//��ʼ����start�ǵ����ҵ�ֱ�ߺţ�end�ǵ�������ֱ�ߺ�
		while (start != end-1) {						
			if (left_of(x, y, x_pos[(start + end) >> 1], y_pos[(start + end) >> 1])) {	//��ʼѭ����������ֱ�ߵ���ֻ��1�����м����һ��������ֹͣ
				end = (start + end) >> 1;				//��������м�ֱ�ߵ����棬��end��ֵΪ�м�ֱ��
			}
			else start= (start + end) >> 1;					//��������м�ֱ�ߵ����棬��start��ֵΪ�м�ֱ��
		}
		printf("%lld\n", end);							//���Ϊend��ֵ
	}
	return 0;
}

int left_of(long long x,long long y,long long a,long long b) {
	return(a*y + b*x < a*b);							//������ѧ֪ʶ�����(x,y)�Ƿ����к����ؾ�Ϊa,b��ֱ�����
}

