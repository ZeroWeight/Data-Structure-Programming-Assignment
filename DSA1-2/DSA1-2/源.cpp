#include<iostream>
#include<vector>
using namespace std;
class worker {
public:
	long long code;
	worker** ld;
	worker** rd;
	int name;
	worker(int name);
};
void I(worker**);
void O(worker**);
int N(worker**);
void C(worker**);
int Q(worker** );
int main() {
	worker**ALL=new(worker*);
	*ALL = nullptr;
	int n;
	cin >> n;
	int m;
	cin >> m;
	int q = 0;
	for (int i = 0;i < m;i++) {
		char mode;
		cin >> mode;
		switch (mode) {
		case'I': {
			I(ALL);
			break;
		}
		case'O': {
			O(ALL);
			break;
		}
		case'C': {
			C(ALL);
			break;
		}
		case'N':{
			q += N(ALL);
			break;
				 }
		case'Q': {
			q += Q(ALL);
			break;
		}
		}
	}
	cout << q;
	return 0;
}
void I(worker**p) {
	int name;
	long long code;
	cin >> name;
	cin >> code;
	if (!*p) {
		*p = new worker(name);
		(*p)->code = code;
	}
	if ((*p)->name == name)(*p)->code = code;
	if ((*p)->name < name) I((*p)->rd);
	else I((*p)->ld);
}
worker::worker(int name) {
	code = -1;
	ld = new(worker*);
	rd = new(worker*);
	this->name = name;
}
void O(worker**p) {
	int name;
	cin >> name;
	if (!(*p)) return;
	if ((*p)->name == name) (*p)->code = -1;
	if ((*p)->name < name) O((*p)->rd);
	if ((*p)->name >name) O((*p)->ld);
}
void C(worker**p) {
	if (!(*p)) return;
	(*p)->code = -1;
	C((*p)->ld);
	C((*p)->rd);
}
int N(worker**p) {

}
int Q(worker**p) {

}
