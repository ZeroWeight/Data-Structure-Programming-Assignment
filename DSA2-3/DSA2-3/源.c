#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct _tree {					//�������ṹ
	int value;
	struct _tree* lchild;
	struct _tree* rchlid;
}tree;
int reconstruct(tree* root, int* pre, int*mid,int amount);		//���ع���������һ���������������������λͼ�ı���������������amountλ��������Ϊroot��ʧ�ܷ���1
void post(tree*root);					//�������
int main() {
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);		//����������
	int n, *pre, *mid;
	scanf("%d", &n);
	pre = (int*)malloc(sizeof(int)*n);
	mid = (int*)malloc(sizeof(int)*n);
	register int i;
	int temp;
	for (i = 0;i < n;i++) {
		scanf("%d", pre + i);			//�������鰴˳���¼Ԫ�س���
	}
	for (i = 0;i < n;i++) {
		scanf("%d", &temp);
		mid[temp] = i;			//���������¼��Ԫ�س��ֵ�˳����������ֻ�������������л�ȡ�ĺϷ�ֵΪ�ȷ���
	}
	tree root;
	if (!reconstruct(&root, pre, mid, n)) {		//������ع��ɹ������������
		post(&root);
	}
	else {
		printf("-1");			//�������-1
	}
	return 0;
}
int reconstruct(tree * root, int * pre, int * mid, int amount)
{
		if (amount == 1) {						//��ͼ��ݹ��������һ��Ԫ��ֱ�Ӹ��������������سɹ�
			root->value = pre[0];
			root->rchlid = root->lchild = NULL;
			return 0;
		}
		root->value = pre[0];						//����Ԫ�ظ�������
		register int i;
		int I;
		for (i = 1;i < amount;i++) {
			if (mid[pre[i]]>mid[pre[0]]) break;			//���������������׸�����������֮���Ԫ��
		}
		I = i;
		if (I == amount) {						//���û�����Ԫ�أ�˵��ȫ����������
			root->rchlid = NULL;					//����������Ϊ����
			root->lchild = (tree*)malloc(sizeof(tree));			//�������ռ�׼��
			return reconstruct(root->lchild, pre + 1, mid, amount - 1);	//��������һλΪ�������������򹹽����������ɹ��������ֱ�����
		}
		for (i = I;i < amount;i++) {					//����������������û���������г��ֱȸ�ǰ��Ԫ�أ�Ӧ������������
			if (mid[pre[i]] < mid[pre[0]]) return 1;			//���У�����ʧ��
		}
		if (I == 1) {						//�������������������������ڽ���������
			root->lchild = NULL;
			root->rchlid = (tree*)malloc(sizeof(tree));
			return reconstruct(root->rchlid, pre + 1, mid, amount - 1);
		}
		root->lchild = (tree*)malloc(sizeof(tree));				//��������������������У��������������ռ�
		root->rchlid = (tree*)malloc(sizeof(tree));
		if (reconstruct(root->lchild, pre + 1, mid, I - 1)) return 1;		//����������֮ǰ������Ԫ���ع�����������ʧ��ֱ�ӷ���ʧ��
		else return reconstruct(root->rchlid, pre + I, mid, amount - I);		//���ɹ��������������ع������������سɹ���
}
void post(tree*root) {
	if (root->lchild) post(root->lchild);					//�������������
	if (root->rchlid) post(root->rchlid);					//�������������
	printf("%d ", root->value);						//�����ֵ
}