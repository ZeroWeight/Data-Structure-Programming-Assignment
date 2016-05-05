#include<stdio.h>
#include<stdlib.h>
typedef struct _Node {
	int count;
	int collect;
	int * next_list;
	int * next_price;
	//for the tree
	struct _Node* from;
	struct _Node* to;
}Node;
typedef struct list {
	int n;
	struct list* next;
	struct list* before;
} Queue;
int pop(Queue * h, Queue * t);
void push(Queue * h, int key, Queue * t);
int empty(Queue h, Queue t);
int main() {
	/*char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);
	register int n, m;
	scanf("%d %d", &n, &m);
	const int N = n;
	Node* map = (Node*)malloc(sizeof(Node)*N);*/
	Queue qh, qt;
	qh.n = qt.n = -1;
	qh.before = qt.next = NULL;
	qt.before = &qh;
	qh.next = &qt;
	push(&qh, 1, &qt);
	push(&qh, 2, &qt);
	push(&qh, 3, &qt);
	printf("%d\n", pop(&qh, &qt));
	printf("%d\n", pop(&qh, &qt));
	push(&qh, 4, &qt);
	printf("%d\n", pop(&qh, &qt));
	printf("++%d\n", empty(qh, qt));
	printf("%d\n", pop(&qh, &qt));
	printf("++%d\n", empty(qh, qt));
	/*int num = 0;
	int * count = (int*)malloc(sizeof(int)*N);
	int ** route = (int**)malloc(sizeof(int*)*N);
	for (--n;~n;--n){
		map[n].count = 0;
		map[n].collect = 0;
		map[n].next_list = (int*)malloc(sizeof(int)*N);
		map[n].next_price = (int*)malloc(sizeof(int)*N);
		map[n].from = map[n].to = NULL;
		route[n] = (int*)malloc(sizeof(int)*N);
		count[n] = 0;
	}
	for (--m;~m;--m) {
		int i, j, k;
		scanf("%d %d %d", &i, &j, &k);
		map[i].next_list[map[i].count] = j;
		map[i].next_price[map[i].count] = k;
		++map[i].count;
		++map[j].collect;
	}
	n = N;
	for (--n;~n;--n) {
		if (!map[n].collect) {
			route[num][count[num]] = n;
			++count[num];
			++num;
		}
	}
	int i = num;
	for (--i;~i;--i) {
		
	}*/
}
int pop(Queue * h,Queue * t) {
	if (empty(*h, *t)) return -1;
	int result = t->before->n;
	Queue * temp = t->before;
	//Queue * tmp = t->before->next;
	t->before = t->before->before;
	t->before->next = t;
	free(temp);
	return result;
}
void push(Queue * h, int key, Queue * t) {
	Queue * temp = h->next;
	//Queue * tmp = h->next->before;
	h->next = (Queue*)malloc(sizeof(Queue));
	h->next->n = key;
	h->next->before = h;
	h->next->next = temp;
	h->next->next->before = h->next;
}
int empty(Queue h, Queue t) {
	if (!h.next->next) return 1;
	else return 0;
}