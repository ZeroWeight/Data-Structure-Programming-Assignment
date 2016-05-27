#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
class people {
public:
	people* from;
	people* to;
	int ID;
	people() {}
};
int main() {
	int n, m,arrived;
	register int j;
	people* cursor = new people;
	cursor->from = cursor->to = cursor;
	scanf("%d %d %d", &n, &m, &cursor->ID);
	for (arrived = 1;arrived < n;arrived++) {
		if (!(m%arrived))cursor = cursor->from;
		for (j = 1;j < (m%arrived);j++) {
			cursor = cursor->to;
		}
		people* temp = cursor->to;
		cursor->to = new people;
		cursor->to->from = cursor;
		cursor->to->to = temp;
		temp->from = cursor->to;
		scanf("%d", &cursor->to->ID);
		cursor = cursor->to;
	}
	for (j = 0;j < n;j++) {
		printf("%d ", cursor->ID);
		cursor = cursor->from;
	}
	return 0;
}