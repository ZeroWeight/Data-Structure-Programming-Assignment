#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct _tree {					//声明树结构
	int value;
	struct _tree* lchild;
	struct _tree* rchlid;
}tree;
int reconstruct(tree* root, int* pre, int*mid,int amount);		//树重构函数，用一个先序的数组和中序的类似位图的变量构造先序数组amount位的树，跟为root，失败返回1
void post(tree*root);					//后序遍历
int main() {
	char* read_in = (char*)malloc(sizeof(char)*(1 << 20));
	setvbuf(stdin, read_in, _IOFBF, 1 << 20);		//调整缓冲区
	int n, *pre, *mid;
	scanf("%d", &n);
	pre = (int*)malloc(sizeof(int)*n);
	mid = (int*)malloc(sizeof(int)*n);
	register int i;
	int temp;
	for (i = 0;i < n;i++) {
		scanf("%d", pre + i);			//先序数组按顺序记录元素出现
	}
	for (i = 0;i < n;i++) {
		scanf("%d", &temp);
		mid[temp] = i;			//中序数组记录个元素出现的顺序，中序数组只能以先序数组中获取的合法值为秩访问
	}
	tree root;
	if (!reconstruct(&root, pre, mid, n)) {		//如果树重构成功，后序遍历树
		post(&root);
	}
	else {
		printf("-1");			//否则，输出-1
	}
	return 0;
}
int reconstruct(tree * root, int * pre, int * mid, int amount)
{
		if (amount == 1) {						//最低级递归基，若仅一个元素直接赋给树根，并返回成功
			root->value = pre[0];
			root->rchlid = root->lchild = NULL;
			return 0;
		}
		root->value = pre[0];						//将首元素赋给树根
		register int i;
		int I;
		for (i = 1;i < amount;i++) {
			if (mid[pre[i]]>mid[pre[0]]) break;			//检查在中序遍历中首个出现在树根之后的元素
		}
		I = i;
		if (I == amount) {						//如果没有这个元素，说明全部是左子树
			root->rchlid = NULL;					//右子树定义为空树
			root->lchild = (tree*)malloc(sizeof(tree));			//左子树空间准备
			return reconstruct(root->lchild, pre + 1, mid, amount - 1);	//以先序下一位为基础，参照中序构建左子树，成功与否与其直接相关
		}
		for (i = I;i < amount;i++) {					//查找右子树集中有没有在中序中出现比根前的元素（应属于左子树）
			if (mid[pre[i]] < mid[pre[0]]) return 1;			//若有，返回失败
		}
		if (I == 1) {						//若仅有右子树，处理方法类似于仅有左子树
			root->lchild = NULL;
			root->rchlid = (tree*)malloc(sizeof(tree));
			return reconstruct(root->rchlid, pre + 1, mid, amount - 1);
		}
		root->lchild = (tree*)malloc(sizeof(tree));				//正常情况：左右子树都有，声明左右子树空间
		root->rchlid = (tree*)malloc(sizeof(tree));
		if (reconstruct(root->lchild, pre + 1, mid, I - 1)) return 1;		//将右子树根之前的所有元素重构左子树，若失败直接返回失败
		else return reconstruct(root->rchlid, pre + I, mid, amount - I);		//若成功，以右子树根重构右子树，返回成功性
}
void post(tree*root) {
	if (root->lchild) post(root->lchild);					//后序遍历左子树
	if (root->rchlid) post(root->rchlid);					//后序遍历右子树
	printf("%d ", root->value);						//输出根值
}