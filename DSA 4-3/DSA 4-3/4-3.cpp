#include<stdio.h>
#include<stdlib.h>
#define InHeap(n,i) (((-1)<(i))&&((i)<(n)))
#define Parent(i) ((i-1)>>1)
#define LastLinternal(n) Parent(n-1)
#define LChild(i) (1+((i)<<1))
#define RChild(i) ((1+(i))<<1)
#define ParentValid(i) (i<0)
#define LChildVaild(n,i) InHeap(n,LChild(i))
#define RChildVaild(n,i) InHeap(n,RChild(i))
#define Bigger(PQ,i,j) ((PQ[i]<PQ[j])?j:i)
#define ProperParent(PQ,n,i) \
		(RChildVaild(n,i)?Bigger(PQ,Bigger(PQ,i,LChild(i)),RChild(i)): \
		(LChildVaild(n,i)?Bigger(PQ,i,LChild(i)): i \
		) \
		)
#define T int
#define Rank int
inline void swap(T& a, T& b) { T temp = a;a = b;b = temp; }
class PQ_ComplHeap {
private:
	T* data;
	Rank size;
	inline Rank percolateDown(Rank, Rank);
	void heapify(Rank);
public:
	PQ_ComplHeap(int);
	void insert(T);
	inline T const getMax();
	T delmax();
};
int main() {
	int n, k;
	fread(&n, sizeof(int), 1, stdin);
	fread(&k, sizeof(int), 1, stdin);
	PQ_ComplHeap H(k);
	for (int i = n - k;i--;) {
		fread(&n, sizeof(int), 1, stdin);
		if (n < H.getMax()) H.insert(n);
	}
	for (int i = k;i--;) {
		printf("%d\n", H.delmax());
	}
}
inline T const PQ_ComplHeap::getMax() {
	return data[0];
}
void PQ_ComplHeap::insert(T e) {
	data[0] = e;
	percolateDown(size, 0);
}
T PQ_ComplHeap::delmax() {
	T maxelem = data[0];
	data[0] = data[--size];
	percolateDown(size, 0);
	return maxelem;
}
Rank PQ_ComplHeap::percolateDown(Rank n, Rank i) {
	Rank j = i;
	T max;
	T temp = data[i];
	if (RChildVaild(n, i)) {
		if (data[j] < data[LChild(i)]) j = LChild(i);
		if (data[j] < data[RChild(i)]) j = RChild(i);
	}
	else if (LChildVaild(n, i)) {
		if (data[j] < data[LChild(i)]) j = LChild(i);
	}
	while (i != j) {
		data[i] = data[j];
		i = j;
		if (RChildVaild(n, i)) {
			max = (data[LChild(i)]>data[RChild(i)]) ? i : j;
			if (temp < data[max]) j = max;
		}
		else if (LChildVaild(n, i)) {
			if (temp < data[LChild(i)]) j = LChild(i);
		}
	}
	data[j] = temp;
	return i;
}
PQ_ComplHeap::PQ_ComplHeap(int k) {
	data = (T*)malloc(sizeof(T)*k);
	size = k;
	fread(data, sizeof(T), k, stdin);
	heapify(k);
}
void PQ_ComplHeap::heapify(Rank n) {
	for (int i = LastLinternal(n);InHeap(n, i);--i) {
		percolateDown(n, i);
	}
}