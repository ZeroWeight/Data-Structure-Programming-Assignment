#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
int main() {
	int*p;
	int n, m, all = 0, answer = 0;
	scanf("%d ", &n);
	scanf("%d", &m);
	p = (int*)malloc(sizeof(int)*n);
	for (int i = 0;i < n;i++) {
		p[i] = -1;
	}
	for (;m;m--) {
		getchar();
		switch (getchar()) {
		case 'I': {
			int name;
			scanf("%d", &name);
			if (p[name - 1] < 0) all++;
			scanf("%d", p - 1 + name);
#ifdef Z_DEBUG
			printf(">>>%d\n", all);
#endif
			break;
		}
		case 'O': {
			int name;
			scanf("%d", &name);
			if (p[name - 1] > 0) all--;
			p[name - 1] = -1;
#ifdef Z_DEBUG
			printf(">>>%d\n", all);
#endif
			break;
		}
		case'C': {
			all = 0;
			for (int i = 0;i < n;i++) {
				p[i] = -1;
		}
#ifdef Z_DEBUG
			printf(">>>%d\n", all);
#endif
			break;
		}
		case'N': {
#ifdef Z_DEBUG
			printf(">>>%d\n", all);
#endif
			answer += all;
			break;
		}
		case'Q': {
			int name;
			scanf("%d", &name);
#ifdef Z_DEBUG
			printf("----------------->>>%d\n", p[name - 1]);
#endif
			answer += p[name - 1];
			break;
		}
		}
	}
	printf("%d", answer);
	return 0;
}