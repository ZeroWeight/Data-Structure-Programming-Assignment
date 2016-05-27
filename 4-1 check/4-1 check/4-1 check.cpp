#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 40321; //由于此题数字1~8，康托展开的所有情况为8!，共40320种
const int fac[8] = { 1, 1, 2, 6, 24, 120, 720, 5040 }; //康托展开中用到的0~7的阶乘
string ans[MAXN]; //存储各状态的变化步骤，预处理完成
struct node {
	int a[8];
	int n;
} u, v;
void A(node &t) //A操作
{
	swap(t.a[0], t.a[7]);
	swap(t.a[1], t.a[6]);
	swap(t.a[2], t.a[5]);
	swap(t.a[3], t.a[4]);
}
void B(node &t) //B操作
{
	swap(t.a[3], t.a[2]);
	swap(t.a[2], t.a[1]);
	swap(t.a[1], t.a[0]);
	swap(t.a[4], t.a[5]);
	swap(t.a[5], t.a[6]);
	swap(t.a[6], t.a[7]);
}
void C(node &t) //C操作
{
	swap(t.a[1], t.a[6]);
	swap(t.a[6], t.a[5]);
	swap(t.a[5], t.a[2]);
}
int contor(node &t) //康托展开
{
	int tmp, num = 0;
	for (int i = 0; i < 8; i++) {
		tmp = 0;
		for (int j = i + 1; j < 8; j++) {
			if (t.a[j] < t.a[i]) {
				tmp++;
			}
		}
		num += tmp * fac[7 - i];
	}
	return num;
}
void Init(void) {
	void(*ptr[3])(node&); //定义函数指针
	ptr[0] = A;
	ptr[1] = B;
	ptr[2] = C; //指向对应函数方便处理

	int mark[MAXN] = { 0 }; //设置标记
	mark[0] = 1;

	for (int i = 0; i < 8; i++) //由初始状态12345678开始
	{
		u.a[i] = i + 1;
	}
	u.n = contor(u);

	queue<node> que;
	que.push(u);
	while (!que.empty()) {
		u = que.front();
		que.pop();
		for (int i = 0; i < 3; i++) //三种变换
		{
			v = u;
			(*ptr[i])(v);
			v.n = contor(v); //对副本执行操作并康托展开
			if (mark[v.n] == 0) //重复
			{
				char ch = 'A' + i;
				ans[v.n] = ans[u.n] + ch; //记录步骤

				mark[v.n] = 1; //标记
				que.push(v);
			}
		}
	}
}
int main() {
	Init();
	char a[10] = { 0 }, b[10] = "12345678";
	while (gets_s(a)) {
		int n[10];
		for (int i = 0; i < 8; i++) //把初态置换成12345678
		{
			n[a[i] - '0'] = i + 1;
		}

		for (int i = 0; i < 8; i++) //把目标状态相对于初态置换
		{
			u.a[i] = n[b[i] - '0'];
		}

		cout << ans[contor(u)].length() << endl; //输出由12345678到目标态的步骤
	}
	return 0;
}
