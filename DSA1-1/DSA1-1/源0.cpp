#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
class student {
public:
	student** ptr[3];
	inline void shut() {
		*(ptr[0]) = NULL; *(ptr[1]) = NULL;*(ptr[2]) = NULL;
	}
};
int main() {
	unsigned int n;
	register unsigned int j;
	unsigned int r;
	scanf("%d", &n);
	student** coach = (student**)malloc(3 * n * sizeof(student*));
	unsigned int a = 0, b = 0, c = 0;
	student* Student = (student*)malloc(sizeof(student)*n);
	for (j = 0;j < n;j++) {
		scanf("%d", &r);
			coach[j] = Student+r-1;
			(Student + r-1)->ptr[0] = coach + j;
		}
	for (j = 0;j < n;j++) {
		scanf("%d", &r);
		coach[n + j] = Student + r - 1;
		(Student + r - 1)->ptr[1] = coach + n + j;
	}
	for (j = 0;j < n;j++) {
		scanf("%d", &r);
		coach[2*n + j] = Student + r - 1;
		(Student + r - 1)->ptr[2] = coach + 2*n + j;
	}
	scanf("%d", &r);
	while(true){
		for (;!coach[a];a++);
		if (r == (coach[a] - Student + 1))
			{
				putchar('A');
				break;
			}
		coach[a]->shut();
		for (;!coach[n+b];b++);
		if (r == (coach[n+b] - Student + 1))
		{
			putchar('B');
			break;
		}
		coach[n+b]->shut();
		for (;!coach[2*n+c];c++);
		if (r == (coach[2*n+c] - Student + 1))
		{
			putchar('C');
			break;
		}
		coach[2*n+c]->shut();
	}
	
}