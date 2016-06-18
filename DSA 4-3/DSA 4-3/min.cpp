#include <stdio.h>
#include <malloc.h>
#define l(i) (((i) << 1) + 1)
#define r(i) (((i) << 1) + 2)
void adjust(int*, int, int);
int extract(int*, int);
int main(){
	int n, k;
	fread(&n, sizeof(int), 1, stdin);
	fread(&k, sizeof(int), 1, stdin);
	int *data = (int*)malloc(sizeof(int) * k);
	fread(data, sizeof(int), k, stdin);
	for (int i = k - 2 >> 1; ~i; --i) adjust(data, i, k);
	int tmp;
	for (int i = n - k; i; --i){
		fread(&tmp, sizeof(int), 1, stdin);
		if (tmp < *data){
			*data = tmp;
			adjust(data, 0, k);
		}
	}
	for (; k--;) printf("%d\n", extract(data, k));
	return 0;
}
void swap(int *data, int i, int j){
	int tmp;
	tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}
void adjust(int *data, int i, int size){
	int tmp = i;
	if (i <= size >> 1){
		if (l(i) < size && data[l(i)] > data[tmp]) tmp = l(i);
		if (r(i) < size && data[r(i)] > data[tmp]) tmp = r(i);
		if (tmp != i){
			swap(data, tmp, i);
			adjust(data, tmp, size);
		}
	}
}
int extract(int *data, int size){
	int tmp = *data;
	swap(data, 0, size);
	adjust(data, 0, size);
	return tmp;
}
