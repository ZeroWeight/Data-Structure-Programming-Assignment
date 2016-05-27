#include<iostream>
#include<stdlib.h>
class student {
public:
	student** rank[3];
	int name;
	void shut();
};
int main() {
	student** ABC[3];
	int n;
	std::cin >> n;
	ABC[0] = (student**)malloc(sizeof(student*) * n);
	ABC[1] = (student**)malloc(sizeof(student*) * n);
	ABC[2] = (student**)malloc(sizeof(student*) * n);
	student** L= (student**)malloc(sizeof(student*) * n);
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < n;j++) {
			int r;
			if (!i) L[j] = new student;
			L[j]->name = j+1;
			std::cin >> r;
			L[j]->rank[i] = ABC[i] + r-1;
			*(L[j]->rank[i]) = L[j];
		}
	}
	int k;
	std::cin >> k;
	for (int i = 0;;i++) {
		int j;
		for (j = 0;!ABC[i%3][j];j++);
		if (ABC[i % 3][j]->name == k) { std::cout << char('A' + i % 3) << std::endl;break; }
		ABC[i % 3][j]->shut();
	}
	return 0;
}
void student::shut() {
	*(rank[0]) = *(rank[1]) = *(rank[2]) = NULL;
}