#include<cstdio>  
#include<cstring>  
const int fac[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };///�׳�  

bool vis[10];

///nΪans��С��kΪȫ���еı���  
void invKT(int ans[], int n, int k)
{
	int i, j, t;
	memset(vis, 0, sizeof(vis));
	--k;
	for (i = 0; i < n; ++i)
	{
		t = k / fac[n - i - 1];
		for (j = 1; j <= n; j++)
			if (!vis[j])
			{
				if (t == 0) break;
				--t;
			}
		ans[i] = j, vis[j] = true;
		k %= fac[n - i - 1];///����  
	}
}

int main()
{
	int a[10];
	for (int i = 1;i < 40321;i++) {
		invKT(a, 8, i);
		for (int i = 0; i < 8; ++i)
			printf("%d ", a[i]);///1 4 3 5 2  
		printf("\n");
	}
	
}
