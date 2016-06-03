#include<stdio.h>
#include<stdlib.h>
#define InHeap(n,i) (((-1)<(i))&&((i)<(n))
#define Parent(i) ((i-1)>>1)
#define LastLinternal(n) Parent(n-1)
#define LChild(i) (1+((i)<<1))
#define RChild(i) ((1+(i))<<1)
#define ParentValid(i) (i<0)
#define LChildVaild(n,i) InHeap(n,LChild(i))
#define RChildVaild(n,i) InHeap(n,RChild(i))
#define Bigger(PQ,i,j) ((PQ[i]<PQ[j])?j:i)
#define ProperParent(PQ,n,i) \
		(RChildVaild(n,i)?Bigger(PQ,Bigger(i,LChild(i)),RChild(i)): \
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
	Rank percolateDown(Rank, Rank);
	Rank percolateUp(Rank);
	void heapify(Rank);
public:
	PQ_ComplHeap(int);
	void insert(T);
	inline T const getMax();
	T delmax();
};
inline T const PQ_ComplHeap::getMax() {
	return data[0];
}
void PQ_ComplHeap::insert(T e) {
	data[0] = e;
	percolateDown(0, size);
}
Rank PQ_ComplHeap::percolateUp(Rank i) {
	while (ParentValid(i)) {
		Rank j = Parent(i);
		if (data[i] < data[j]) break;
		swap(data[i], data[j]);i = j;
	}
	return i;
}