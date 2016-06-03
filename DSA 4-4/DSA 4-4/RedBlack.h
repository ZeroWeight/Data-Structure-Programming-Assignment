#ifndef _RedBlack_H_
#define _RedBlack_H_
#define T int
class RedBlack {
private:
	void solveDoubleRed(BinNodePosi);
	void solveDoubleBlack(BinNodePosi);
	int updateHight(BinNodePosi);
public:
	BinNodePosi insert(const T&);
	bool remove(const T&);
};
#endif