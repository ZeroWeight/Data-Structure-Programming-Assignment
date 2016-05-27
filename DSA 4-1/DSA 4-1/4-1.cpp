#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define RESULT 001234567
typedef struct _list{
	int value;
	struct _list* next;
}list;
class queue {
private:
	list* head;
	list* end;
	int num;
public:
	queue(int);
	void push(int);
	int pop();
	int empty();
};
int solve(int);
//rule to
inline int change_1(int);
inline int change_2(int);
inline int change_3(int);
//rule for
inline int R_change_1(int);
inline int R_change_2(int);
inline int R_change_3(int);
int map[077777777];
//int main() {
//	int n;
//	int i;
//	int temp;
//	int code;
//	scanf("%d", &n);
//	for (;n--;) {
//		code = 0;
//		for (i = 8;i--;) {
//			scanf("%d", &temp);
//			code <<= 3;
//			code += (temp - 1);
//		}
//		printf("%d\n",solve(code));
//	}
//	return 0;
//}
int main() {
	int temp = RESULT;
	printf("%o\n", temp = change_1(temp));
	printf("%o\n", temp = change_2(temp));
	printf("%o\n", temp = change_3(temp));
	printf("%o\n", temp = R_change_3(temp));
	printf("%o\n", temp = R_change_2(temp));
	printf("%o\n", temp = R_change_1(temp));
}
int solve(int code) {
	if (code == RESULT) return 0;
	//find the code,if not
	//A while loop
	//BFS the result root tree a loop
	//BFS the begin root tree a loop
	//check whether they have a cir.
	//if cannot goon return -1;
	return -1;
}
//rules: to
inline int change_1(int code) {
	int temp = 0;
	for (int i = 8;i--;) {
		temp <<= 3;
		temp += (code & 07);
		code >>= 3;
	}
	return temp;
}
inline int change_2(int code) {
	int lower = code & 07777;//the lower state;
	int higher = code >> (3 * 4);
	int lower_1 = (lower & 07000)>>(3*3);//the [8]
	int lower_234 = lower - (lower_1<<(3*3));
	lower = (lower_234 << 3) + lower_1;
	int higher_1 = higher & 07;//the [8]
	int higher_234 = higher >> 3;
	higher = (higher_1 << (3 * 3)) + higher_234;
	return ((higher << (3 * 4)) + lower);
}
inline int change_3(int code) {
	int a[8];
	for (int i = 8;i--;) {
		a[i] = code & 07;
		code >>= 3;
	}
	int temp = a[1];
	a[1] = a[6];
	a[6] = a[5];
	a[5] = a[2];
	a[2] = temp;
	temp = 0;
	for (int i = 0;i < 8;++i) {
		temp <<= 3;
		temp += a[i];
	}
	return temp;
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
	int higher_1 = (higher & 07000) >> (3 * 3);//the [8]
	int higher_234 = higher - (higher_1 << (3 * 3));
	higher = (higher_234 << 3) + higher_1;
	int lower_1 = lower & 07;//the [8]
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
	list* temp = this->head;
	this->head = this->head->next;
	this->num--;
	int tmp = temp->value;
	free(temp);
	return tmp;
}
void queue::push(int code) {
	this->end->next = (list*)malloc(sizeof(list));
	this->end = this->end->next;
	this->end->value = code;
	this->end->next = NULL;
	this->num++;
}