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
//static variables
int map[077777777];
int time_stamp[077777777];
int time;
queue result(RESULT);
int main() {
	int n;
	int i;
	int temp;
	int code;
	scanf("%d", &n);
	for (;n--;) {
		time++;
		code = 0;
		for (i = 8;i--;) {
			scanf("%d", &temp);
			code <<= 3;
			code += (temp - 1);
		}
		printf("%d\n",solve(code));
	}
	return 0;
}
int solve(int code) {
	int r_temp, s_temp;
	if (code == RESULT) return 0;
	if (map[code] > 0) return map[code];
	if (result.empty()) return -1;
	queue start(code);
	map[code] = 0;
	while ((!start.empty()) && (!result.empty())) {
		//a try from root
		r_temp = result.pop();
		if (map[R_change_1(r_temp)] < 0 && time_stamp[R_change_1(r_temp)] == time)
			return 1 + map[r_temp] - map[R_change_1(r_temp)];
		if (map[R_change_2(r_temp)] < 0 && time_stamp[R_change_2(r_temp)] == time)
			return 1 + map[r_temp] - map[R_change_2(r_temp)];
		if (map[R_change_3(r_temp)] < 0 && time_stamp[R_change_3(r_temp)] == time)
			return 1 + map[r_temp] - map[R_change_3(r_temp)];
		if (map[R_change_1(r_temp)] <= 0) {
			map[R_change_1(r_temp)] = map[r_temp] + 1;
			result.push(R_change_1(r_temp));
		}
		if (map[R_change_2(r_temp)] <= 0) {
			map[R_change_2(r_temp)] = map[r_temp] + 1;
			result.push(R_change_2(r_temp));
		}
		if (map[R_change_3(r_temp)] <= 0) {
			map[R_change_3(r_temp)] = map[r_temp] + 1;
			result.push(R_change_3(r_temp));
		}
		//a try from start
		s_temp = start.pop();
		if (map[change_1(s_temp)] > 0) return 1 + map[change_1(s_temp)] - map[s_temp];
		if (map[change_2(s_temp)] > 0) return 1 + map[change_2(s_temp)] - map[s_temp];
		if (map[change_3(s_temp)] > 0) return 1 + map[change_3(s_temp)] - map[s_temp];
		if (time_stamp[change_1(s_temp)] == time&&map[change_1(s_temp)] < 0);
		else {
			time_stamp[change_1(s_temp)] = time;//update time
			start.push(change_1(s_temp));//push
			map[change_1(s_temp)] = map[s_temp] - 1;//minus 1
		}
		if (time_stamp[change_2(s_temp)] == time&&map[change_2(s_temp)] < 0);
		else {
			time_stamp[change_2(s_temp)] = time;//update time
			start.push(change_2(s_temp));//push
			map[change_2(s_temp)] = map[s_temp] - 1;//minus 1
		}
		if (time_stamp[change_3(s_temp)] == time&&map[change_3(s_temp)] < 0);
		else {
			time_stamp[change_3(s_temp)] = time;//update time
			start.push(change_3(s_temp));//push
			map[change_3(s_temp)] = map[s_temp] - 1;//minus 1
		}
	}
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