#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define RESULT 001234567
#define _8 40320
typedef struct _list{
	int value;
	struct _list* next;
}list;
class queue {
private:
	list* head;
	list* end;
	short num;
public:
	queue(int);
	void push(int);
	int pop();
	int empty();
};
//BFS search
void BFS();
//zip and upzip
inline int zip(int);
//rule for
inline int R_change_1(int);
inline int R_change_2(int);
inline int R_change_3(int);
//static variables
const int fact[] = { 1,1,2,6,24,120,720,5040,40320 };
int map[_8];
char read_in[1 << 20];
int main() {
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	int n;
	scanf("%d", &n);
	int i;
	int temp;
	int code;
	BFS();
	for (;n--;) {
		code = 0;
		for (i = 8;i--;) {
			scanf("%d", &temp);
			code <<= 3;
			code += (temp - 1);
		}
		if (code == RESULT) puts("0");
		else if (map[zip(code)] > 0) printf("%d", map[zip(code)]);
		else puts("-1");
	}
	return 0;
}
//BFS search
void BFS() {
	queue root(RESULT);
	int code;
	while (!root.empty()) {
		code=root.pop();
		if (!map[zip(R_change_1(code))] && R_change_1(code) != RESULT) {
			map[zip(R_change_1(code))] = map[zip(code)] + 1;
			root.push(R_change_1(code));
		}
		if (!map[zip(R_change_2(code))] && R_change_2(code) != RESULT) {
			map[zip(R_change_2(code))] = map[zip(code)] + 1;
			root.push(R_change_2(code));
		}
		if (!map[zip(R_change_3(code))] && R_change_3(code) != RESULT) {
			map[zip(R_change_3(code))] = map[zip(code)] + 1;
			root.push(R_change_3(code));
		}
	}
}
//zip and unzip
inline int zip(int code) {
	int a[8], i, j, t, sum = 0;
	for (i = 8;i--;) {
		a[i] = code & 07;
		code >>= 3;
	}
	for (i = 0;i < 8;++i) {
		t = 0;
		for (j = i + 1;j < 8;++j)
			if(a[j]<a[i]) t++;
		sum += t*fact[8 - i - 1];
	}
	return sum;
}
//rules: from
inline int R_change_1(int code) {
	int temp = 0;
	for (int i = 8;i--;) {
		temp <<= 3;
		temp += (code & 07);
		code >>= 3;
	}
	return temp;
}
inline int R_change_2(int code) {
	int lower = code & 07777;//the lower state;
	int higher = code >> (3 * 4);
	int higher_1 = (higher & 07000) >> (3 * 3);
	int higher_234 = higher - (higher_1 << (3 * 3));
	higher = (higher_234 << 3) + higher_1;
	int lower_1 = lower & 07;
	int lower_234 = lower >> 3;
	lower = (lower_1 << (3 * 3)) + lower_234;
	return ((higher << (3 * 4)) + lower);
}
inline int R_change_3(int code) {
	int a[8];
	for (int i = 8;i--;) {
		a[i] = code & 07;
		code >>= 3;
	}
	int temp = a[1];
	a[1] = a[2];
	a[2] = a[5];
	a[5] = a[6];
	a[6] = temp;
	temp = 0;
	for (int i = 0;i < 8;++i) {
		temp <<= 3;
		temp += a[i];
	}
	return temp;
}
//the function of a queue
int queue::empty() {
	return num == 0;
}
queue::queue(int code) {
	this->head = this->end = (list*)malloc(sizeof(list));
	this->head->value = code;
	this->head->next = NULL;
	this->num = 1;
}
int queue::pop() {
	int temp = this->head->value;
	this->head = this->head->next;
	this->num--;
	return temp;
}
void queue::push(int code) {
	if (num) {
		this->end->next = (list*)malloc(sizeof(list));
		this->end = this->end->next;
		this->end->value = code;
		this->end->next = NULL;
		this->num++;
	}
	else {
		this->head = this->end = (list*)malloc(sizeof(list));
		this->head->value = code;
		this->head->next = NULL;
		this->num = 1;
	}
}