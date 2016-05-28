#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define RESULT 001234567
#define _8 40320
typedef struct _list {
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
	int const empty();
	int const value();
};
int solve(int);
void BFS();
//zip and upzip
inline int zip(int);
inline int unzip(int);
//rule to
inline int change_1(int);
inline int change_2(int);
inline int change_3(int);
//rule for
inline int R_change_1(int);
inline int R_change_2(int);
inline int R_change_3(int);
//static variables
const int fact[] = { 1,1,2,6,24,120,720,5040,40320 };
int map[_8];
int time_stamp[_8];
int time;
queue result(RESULT);
char read_in[1 << 20];
int main() {
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	int n;
	int i;
	int temp;
	int code;
	scanf("%d", &n);
	/*BFS();*/
	for (;n--;) {
		time++;
		code = 0;
		for (i = 8;i--;) {
			scanf("%d", &temp);
			code <<= 3;
			code += (temp - 1);
		}
		printf("%d %d\n",n,solve(code));
	}
	return 0;
}
//void BFS() {
//	int code;
//	while (!result.empty()) {
//		int code = result.pop();
//		if (!map[zip(R_change_1(code))] && R_change_1(code) != RESULT) {
//			map[zip(R_change_1(code))] = map[zip(code)] + 1;
//			result.push(R_change_1(code));
//		}
//		if (!map[zip(R_change_2(code))] && R_change_2(code) != RESULT) {
//			map[zip(R_change_2(code))] = map[zip(code)] + 1;
//			result.push(R_change_2(code));
//		}
//		if (!map[zip(R_change_3(code))] && R_change_3(code) != RESULT) {
//			map[zip(R_change_3(code))] = map[zip(code)] + 1;
//			result.push(R_change_3(code));
//		}
//	}
//}
int solve(int code) {
	int R[12] = { 100,100,100,100,100,100,100,100,100,100,100,100 };
	int r = 1;
	int r_temp, s_temp;
	if (code == RESULT) return 0;
	if (map[zip(code)] > 0) return map[zip(code)];
	if (result.empty()) return -1;
	queue start(code);
	map[zip(code)] = 0;
	time_stamp[zip(code)] = time;
	while ((!start.empty()) && (!result.empty())&&r) {
		//a try from root
		r_temp = result.value();
		if (map[zip(R_change_1(r_temp))] <= 0 && time_stamp[zip(R_change_1(r_temp))] == time)
		{
			R[0] =  1+map[zip(r_temp)] - map[zip(R_change_1(r_temp))];
			r = 0;
		}
		if (map[zip(R_change_2(r_temp))] <= 0 && time_stamp[zip(R_change_2(r_temp))] == time)
		{
			R[1] =  1+map[zip(r_temp)] - map[zip(R_change_2(r_temp))];
			r = 0;
		}
		if (map[zip(R_change_3(r_temp))] <= 0 && time_stamp[zip(R_change_3(r_temp))] == time)
		{
			R[2] =  1+map[zip(r_temp)] - map[zip(R_change_3(r_temp))];
			r = 0;
		}
		if (map[zip(R_change_1(r_temp))] <= 0 && R_change_1(r_temp) != RESULT) {
				map[zip(R_change_1(r_temp))] = map[zip(r_temp)] + 1;
				result.push(R_change_1(r_temp));
			}
		if (map[zip(R_change_2(r_temp))] <= 0 && R_change_2(r_temp) != RESULT) {
				map[zip(R_change_2(r_temp))] = map[zip(r_temp)] + 1;
				result.push(R_change_2(r_temp));
			}
		if (map[zip(R_change_3(r_temp))] <= 0 && R_change_3(r_temp) != RESULT) {
				map[zip(R_change_3(r_temp))] = map[zip(r_temp)] + 1;
				result.push(R_change_3(r_temp));
			}
		result.pop();
		//a try from start
		s_temp = start.value();
		if (map[zip(change_1(s_temp))] > 0|| change_1(s_temp)==RESULT) {
			R[3] = 1+map[zip(change_1(s_temp))] - map[zip(s_temp)];
			r = 0;
		}
		if (map[zip(change_2(s_temp))] > 0||change_2(s_temp)==RESULT) {
			R[4] = 1+map[zip(change_2(s_temp))] - map[zip(s_temp)];
			r = 0;
		}
		if (map[zip(change_3(s_temp))] > 0||change_2(s_temp)==RESULT) {
			R[5] = 1+map[zip(change_3(s_temp))] - map[zip(s_temp)];
			r = 0;
		}
		if (time_stamp[zip(change_1(s_temp))] == time);
		else {
			time_stamp[zip(change_1(s_temp))] = time;//update time
			start.push(change_1(s_temp));//push
			map[zip(change_1(s_temp))] = map[zip(s_temp)] - 1;//minus 1
		}
		if (time_stamp[zip(change_2(s_temp))] == time);
		else {
			time_stamp[zip(change_2(s_temp))] = time;//update time
			start.push(change_2(s_temp));//push
			map[zip(change_2(s_temp))] = map[zip(s_temp)] - 1;//minus 1
		}
		if (time_stamp[zip(change_3(s_temp))] == time);
		else {
			time_stamp[zip(change_3(s_temp))] = time;//update time
			start.push(change_3(s_temp));//push
			map[zip(change_3(s_temp))] = map[zip(s_temp)] - 1;//minus 1
		}
		start.pop();
	}
	if (!r) {
		r_temp = result.value();
		if (map[zip(R_change_1(r_temp))] <= 0 && time_stamp[zip(R_change_1(r_temp))] == time)
		{
			R[6] = 1 + map[zip(r_temp)] - map[zip(R_change_1(r_temp))];
		}
		if (map[zip(R_change_2(r_temp))] <= 0 && time_stamp[zip(R_change_2(r_temp))] == time)
		{
			R[7] = 1 + map[zip(r_temp)] - map[zip(R_change_2(r_temp))];
		}
		if (map[zip(R_change_3(r_temp))] <= 0 && time_stamp[zip(R_change_3(r_temp))] == time)
		{
			R[8] = 1 + map[zip(r_temp)] - map[zip(R_change_3(r_temp))];
		}
		s_temp = start.value();
		if (map[zip(change_1(s_temp))] > 0 || change_1(s_temp) == RESULT) {
			R[9] = 1 + map[zip(change_1(s_temp))] - map[zip(s_temp)];
		}
		if (map[zip(change_2(s_temp))] > 0 || change_2(s_temp) == RESULT) {
			R[10] = 1 + map[zip(change_2(s_temp))] - map[zip(s_temp)];
		}
		if (map[zip(change_3(s_temp))] > 0 || change_2(s_temp) == RESULT) {
			R[11] = 1 + map[zip(change_3(s_temp))] - map[zip(s_temp)];
		}
		int min = 100;
		for (int i = 12;i--;) {
			if (R[i] < min) min = R[i];
		}
		return min;
	}
	return -1;
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
			if (a[j]<a[i]) t++;
		sum += t*fact[8 - i - 1];
	}
	return sum;
}
inline int unzip(int code) {
	return code;
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
	int lower_1 = (lower & 07000) >> (3 * 3);
	int lower_234 = lower - (lower_1 << (3 * 3));
	lower = (lower_234 << 3) + lower_1;
	int higher_1 = higher & 07;
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
const int queue::empty() {
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
const int queue::value() {
	return this->head->value;
}