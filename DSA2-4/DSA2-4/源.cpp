#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
class Stack
{
public:
	Stack(int);
	bool empty();
	void push(int);
	int pop();
	int top();
private:
	int cursor;
	int* container;						//底层用数组实现
};
Stack::Stack(int n)
{
	cursor = 0;
	container = (int*)malloc(sizeof(int)*n);				//按程序要求初始化
}
bool Stack::empty()
{
	return cursor == 0;
}
void Stack::push(int value)
{
	container[cursor] = value;
	cursor++;
}
int Stack::pop()
{
	cursor--;
	return container[cursor];
}
int Stack::top()
{
	return container[cursor - 1];
}
class Queap
{
public:
	Queap(int n);
	void enqueap(int);
	int dequeap();
	int min();
private:
	Stack* main_stack;						//主要栈，用于入队
	Stack* buffer_stack;						//缓冲栈，用于逆向出队
	Stack* temp;						//临时栈，用于临时需要
	int min_in_main;						//主要栈的最小元素，当主要栈非空时均生效
	int min_in_all;						//整个队列中的最小元素，当时间戳为1时生效
	int time_stamp;						//时间戳，记录上个变量是否有效
};
Queap::Queap(int n)							//初始化
{
	main_stack = new Stack(n);
	buffer_stack = new Stack(n);
	temp = new Stack(n);
	time_stamp = 0;
}
void Queap::enqueap(int value)
{
	if (main_stack->empty()) min_in_main = value;			//如果之前栈为空，赋值给min_in_main
	if (min_in_main > value) min_in_main = value;			//如果入栈的比之前的小，改变min_in_main
	main_stack->push(value);					//进入主要栈
}		
int Queap::dequeap()
{
	if (buffer_stack->empty()) {					//如果缓冲栈已空，将主要栈的元素导倒入缓冲栈中
		while (!main_stack->empty()) {
			buffer_stack->push(main_stack->pop());
		}
		time_stamp = 1;					//此时时间戳为1
		min_in_all = min_in_main;				//总体的最小元素就是之前主要栈的最小元素
	}
	if (min_in_all == buffer_stack->top()) time_stamp = 0;			//如果最小元素值被弹出，时间戳为0
	return buffer_stack->pop();					//弹出缓冲栈顶
}
int Queap::min()
{
	if (time_stamp) {						//如果时间戳有效
		if ((!main_stack->empty())&&(min_in_all > min_in_main)) min_in_all = min_in_main;
		return min_in_all;					//最小值必为min_in_all和后入栈的最小值min_in_main中的较小者，并同时更新min_in_all
	}
	if (!main_stack->empty()) min_in_all = min_in_main;			//如果主要栈非空，即min_in_main有效，暂时将min_in_all定为min_in_main
	else min_in_all = buffer_stack->top();				//否则定为缓冲栈栈顶元素
	while (!buffer_stack->empty()) {					//遍历缓冲栈，通过倒入临时栈遍历各个元素，寻找最小的
		if (min_in_all > buffer_stack->top()) min_in_all = buffer_stack->top();
		temp->push(buffer_stack->pop());
	}
	while (!temp->empty()) {					//临时栈倒回缓冲栈
		buffer_stack->push(temp->pop());
	}
	time_stamp = 1;						//已经更新完，时间戳生效
	return min_in_all;						//返回更新的min_in_all
}

int main()
{
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);				//调整缓冲区大小
	int n;
	register char c;
	scanf("%d", &n);
	Queap main_structure(n);					//声明Queap
	for (int i = 0;i < n;i++) {
		c = getchar();
		switch (c) {
		case 'E':
			int input;
			scanf("%d", &input);
			main_structure.enqueap(input);			//入队
			break;
		case 'D':
			printf("%d\n", main_structure.dequeap());		//出队
			break;
		case 'M':
			printf("%d\n", main_structure.min());		//最小值
			break;
		default:
			i--;					//如果指令失效，循环节回退，清除影响
			break;
		}
	}
	return 0;
}