#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main() {
	int* p, n, in=0;
	int answer=0;
	register int i;
	scanf("%d", &n);
	p = new int[n];
	for (i = 0;i < n;i++) {
		p[i] = -1;
	}
	int m;
	scanf("%d", &m);
	for (;m;m--) {
		getchar();
		switch (getchar()) {
		case 'I': {
			int name;
			scanf("%d", &name);
			int code;
			scanf("%d", &code);
			if (p[name] < 0) in++;
			p[name] = code;
			break;
		}
		case 'O': {
			int name;
			scanf("%d", &name);
			if (p[name] > 0) in--;
			p[name] = -1;
			break;
		}
		case'C': {
			in = 0;
			for (i = 0;i < n;i++) {
				p[i] = -1;
		}
			break;
		}
		case'N': {
			answer += in;
			break;
		}
		case'Q': {
			int name;
			scanf("%d", &name);
			answer += p[name];
			break;
		}
		}
	}
	printf("%d", answer);
	return 0;
}