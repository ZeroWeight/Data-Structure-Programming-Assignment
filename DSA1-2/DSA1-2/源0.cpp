#define _CRT_SECURE_NO_WARNINGS
//#define Z_DEBUG
#include<stdio.h>
#include<iostream>
class worker {
public:
	int name;
	int code;
	worker* L;
	worker* R;
	inline worker(long name) { this->name = name; }
	inline ~worker() { delete(L);delete(R); }
};
void I(worker*&,int&,int);
void O(worker*&,int&,int);
void C(worker*&,int&);
long Q(worker*&,int);
int main() {
	setvbuf(stdin,)
	int n, m, all = 0;
	int answer = 0;
	scanf("%d %d", &n, &m);
	worker* root = NULL;
	for (;m;m--) {
		switch (getchar()) {
		case 'I': {
			int name;
			scanf("%d", &name);
			I(root,all,name);
#ifdef Z_DEBUG
			printf(">>>%d\n", all);
#endif
			break;
		}
		case 'O': {
			int name;
			scanf("%d", &name);
			O(root,all,name);
#ifdef Z_DEBUG
			printf(">>>%d\n", all);
#endif
			break;
		}
		case'C': {
			C(root,all);
#ifdef Z_DEBUG
			printf(">>>%d\n", all);
#endif
			break;
		}
		case'N': {
#ifdef Z_DEBUG
			printf("++++++++++>>>%d\n", all);
#endif
			answer+=all;
			break;
		}
		case'Q': {
			int name;
			scanf("%d", &name);
#ifdef Z_DEBUG
			printf("---------->>>%d\n", Q(root, name));
#endif
			answer+=Q(root,name);
			break;
		}
		default: m++;
		}
	}
	std::cout << answer;
	return 0;
}
void I(worker*& p, int& a,int name) {
	if (!p) {
		p = new worker(name);
		p->L = NULL;
		p->R = NULL;
		scanf("%d", &p->code);
		a++;
		return;
	}
	else if (p->name == name) {
		if (p->code <= 0) a++;
		scanf("%d", &p->code);
		return;
	}
	else if (p->name < name) {
		I(p->R, a, name);
		return;
	}
	else if (name < p->name) {
		I(p->L, a, name);
		return;
	}
}
void O(worker*& p, int& a, int name) {
	if ((!p)) return;
	if (p->name == name) {
		if(p->code > 0){
		p->code = -1;
		a--;}
		return;
	}
	if (p->name < name) {
		O(p->R, a, name);
		return;
	}
	if (name < p->name) {
		O(p->L, a, name);
		return;
	}
}
long Q(worker*&p, int name) {
	if (!p) return -1;
	if (p->name == name) {
		return p->code;
	}
	if (p->name < name) {
		 return Q(p->R,  name);
	}
	if (name < p->name) {
		return Q(p->L,  name);
	}
}
void C(worker*&p, int&a) {
	if (p) {
		delete(p);
	}
	p = NULL;
	a = 0;
}