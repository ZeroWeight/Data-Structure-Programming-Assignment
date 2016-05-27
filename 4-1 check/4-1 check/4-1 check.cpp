#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN = 40321; //���ڴ�������1~8������չ�����������Ϊ8!����40320��
const int fac[8] = { 1, 1, 2, 6, 24, 120, 720, 5040 }; //����չ�����õ���0~7�Ľ׳�
string ans[MAXN]; //�洢��״̬�ı仯���裬Ԥ�������
struct node {
	int a[8];
	int n;
} u, v;
void A(node &t) //A����
{
	swap(t.a[0], t.a[7]);
	swap(t.a[1], t.a[6]);
	swap(t.a[2], t.a[5]);
	swap(t.a[3], t.a[4]);
}
void B(node &t) //B����
{
	swap(t.a[3], t.a[2]);
	swap(t.a[2], t.a[1]);
	swap(t.a[1], t.a[0]);
	swap(t.a[4], t.a[5]);
	swap(t.a[5], t.a[6]);
	swap(t.a[6], t.a[7]);
}
void C(node &t) //C����
{
	swap(t.a[1], t.a[6]);
	swap(t.a[6], t.a[5]);
	swap(t.a[5], t.a[2]);
}
int contor(node &t) //����չ��
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
	void(*ptr[3])(node&); //���庯��ָ��
	ptr[0] = A;
	ptr[1] = B;
	ptr[2] = C; //ָ���Ӧ�������㴦��

	int mark[MAXN] = { 0 }; //���ñ��
	mark[0] = 1;

	for (int i = 0; i < 8; i++) //�ɳ�ʼ״̬12345678��ʼ
	{
		u.a[i] = i + 1;
	}
	u.n = contor(u);

	queue<node> que;
	que.push(u);
	while (!que.empty()) {
		u = que.front();
		que.pop();
		for (int i = 0; i < 3; i++) //���ֱ任
		{
			v = u;
			(*ptr[i])(v);
			v.n = contor(v); //�Ը���ִ�в���������չ��
			if (mark[v.n] == 0) //�ظ�
			{
				char ch = 'A' + i;
				ans[v.n] = ans[u.n] + ch; //��¼����

				mark[v.n] = 1; //���
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
		for (int i = 0; i < 8; i++) //�ѳ�̬�û���12345678
		{
			n[a[i] - '0'] = i + 1;
		}

		for (int i = 0; i < 8; i++) //��Ŀ��״̬����ڳ�̬�û�
		{
			u.a[i] = n[b[i] - '0'];
		}

		cout << ans[contor(u)].length() << endl; //�����12345678��Ŀ��̬�Ĳ���
	}
	return 0;
}
