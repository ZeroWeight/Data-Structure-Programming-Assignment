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
	int* container;						//�ײ�������ʵ��
};
Stack::Stack(int n)
{
	cursor = 0;
	container = (int*)malloc(sizeof(int)*n);				//������Ҫ���ʼ��
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
	Stack* main_stack;						//��Ҫջ���������
	Stack* buffer_stack;						//����ջ�������������
	Stack* temp;						//��ʱջ��������ʱ��Ҫ
	int min_in_main;						//��Ҫջ����СԪ�أ�����Ҫջ�ǿ�ʱ����Ч
	int min_in_all;						//���������е���СԪ�أ���ʱ���Ϊ1ʱ��Ч
	int time_stamp;						//ʱ�������¼�ϸ������Ƿ���Ч
};
Queap::Queap(int n)							//��ʼ��
{
	main_stack = new Stack(n);
	buffer_stack = new Stack(n);
	temp = new Stack(n);
	time_stamp = 0;
}
void Queap::enqueap(int value)
{
	if (main_stack->empty()) min_in_main = value;			//���֮ǰջΪ�գ���ֵ��min_in_main
	if (min_in_main > value) min_in_main = value;			//�����ջ�ı�֮ǰ��С���ı�min_in_main
	main_stack->push(value);					//������Ҫջ
}		
int Queap::dequeap()
{
	if (buffer_stack->empty()) {					//�������ջ�ѿգ�����Ҫջ��Ԫ�ص����뻺��ջ��
		while (!main_stack->empty()) {
			buffer_stack->push(main_stack->pop());
		}
		time_stamp = 1;					//��ʱʱ���Ϊ1
		min_in_all = min_in_main;				//�������СԪ�ؾ���֮ǰ��Ҫջ����СԪ��
	}
	if (min_in_all == buffer_stack->top()) time_stamp = 0;			//�����СԪ��ֵ��������ʱ���Ϊ0
	return buffer_stack->pop();					//��������ջ��
}
int Queap::min()
{
	if (time_stamp) {						//���ʱ�����Ч
		if ((!main_stack->empty())&&(min_in_all > min_in_main)) min_in_all = min_in_main;
		return min_in_all;					//��Сֵ��Ϊmin_in_all�ͺ���ջ����Сֵmin_in_main�еĽ�С�ߣ���ͬʱ����min_in_all
	}
	if (!main_stack->empty()) min_in_all = min_in_main;			//�����Ҫջ�ǿգ���min_in_main��Ч����ʱ��min_in_all��Ϊmin_in_main
	else min_in_all = buffer_stack->top();				//����Ϊ����ջջ��Ԫ��
	while (!buffer_stack->empty()) {					//��������ջ��ͨ��������ʱջ��������Ԫ�أ�Ѱ����С��
		if (min_in_all > buffer_stack->top()) min_in_all = buffer_stack->top();
		temp->push(buffer_stack->pop());
	}
	while (!temp->empty()) {					//��ʱջ���ػ���ջ
		buffer_stack->push(temp->pop());
	}
	time_stamp = 1;						//�Ѿ������꣬ʱ�����Ч
	return min_in_all;						//���ظ��µ�min_in_all
}

int main()
{
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);				//������������С
	int n;
	register char c;
	scanf("%d", &n);
	Queap main_structure(n);					//����Queap
	for (int i = 0;i < n;i++) {
		c = getchar();
		switch (c) {
		case 'E':
			int input;
			scanf("%d", &input);
			main_structure.enqueap(input);			//���
			break;
		case 'D':
			printf("%d\n", main_structure.dequeap());		//����
			break;
		case 'M':
			printf("%d\n", main_structure.min());		//��Сֵ
			break;
		default:
			i--;					//���ָ��ʧЧ��ѭ���ڻ��ˣ����Ӱ��
			break;
		}
	}
	return 0;
}