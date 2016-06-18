#include <stdio.h>
#include <utility>
using std::pair;
using std::make_pair;
typedef long long ll;
class SBTElmt{
	public:
		SBTElmt *lson, *rson;
		unsigned size, data;
		SBTElmt(){
			lson = rson = NULL;
			size = 1;
			data = 0;
		}
		SBTElmt(unsigned val){
			lson = rson = NULL;
			size = 1;
			data = val;
		}
};
class SBT{
	private:
		SBTElmt *root;
		void ins_(SBTElmt*&, const unsigned);
		unsigned del_(SBTElmt*&, const unsigned);
		unsigned rank_(const SBTElmt*, const unsigned);
		void left_rotate(SBTElmt*&);
		void right_rotate(SBTElmt*&);
		void maintain(SBTElmt*&, bool);
	public:
		SBT();
		void ins(const unsigned);
		unsigned del(const unsigned);
		unsigned rank(const unsigned);
		unsigned size();
};
void SBT::ins_(SBTElmt *&root, const unsigned val){
	++root -> size;
	if (val < root -> data){
	   if (root -> lson == NULL) root -> lson = new SBTElmt(val);
	   else ins_(root -> lson, val);
	}
	else{
		if (root -> rson == NULL) root -> rson = new SBTElmt(val);
		else ins_(root -> rson, val);
	}
	maintain(root, val >= root -> data);
};
unsigned SBT::del_(SBTElmt *&root, const unsigned rank){
	--root -> size;
	if (root -> lson == NULL){
		if (rank == 0){
			SBTElmt *tmp = root;
			unsigned val = root -> data;
			if (root -> rson == NULL) root = NULL;
			else root = root -> rson;
			delete(tmp);
			return val;
		}
		else return del_(root -> rson, rank - 1);
	}
	else{
		if (rank == root -> lson -> size){
			unsigned val = root -> data;
			root -> data = del_(root -> lson, rank - 1);
			return val;
		}
		else{
			if (rank < root -> lson -> size) return del_(root -> lson, rank);
			else return del_(root -> rson, rank - root -> lson -> size - 1);
		}
	}
};
unsigned SBT::rank_(const SBTElmt *root, const unsigned n){
	if (root -> lson == NULL) return n ? rank_(root -> rson, n - 1) : root -> data;
	if (n == root -> lson -> size) return root -> data;
	if (n < root -> lson -> size) return rank_(root -> lson, n);
	else return rank_(root -> rson, n - root -> lson -> size - 1);
};
void SBT::left_rotate(SBTElmt *&root){
	if (root -> rson == NULL) return;
	SBTElmt *tmp = root -> rson;
	root -> rson = tmp -> lson;
	tmp -> lson = root;
	tmp -> size = root -> size;
	root -> size = 1;
	if (root -> lson) root -> size += root -> lson -> size;
	if (root -> rson) root -> size += root -> rson -> size;
	root = tmp;
};
void SBT::right_rotate(SBTElmt *&root){
	if (root -> lson == NULL) return;
	SBTElmt *tmp = root -> lson;
	root -> lson = tmp -> rson;
	tmp -> rson = root;
	tmp -> size = root -> size;
	root -> size = 1;
	if (root -> lson) root -> size += root -> lson -> size;
	if (root -> rson) root -> size += root -> rson -> size;
	root = tmp;
};
void SBT::maintain(SBTElmt *&root, bool flag){
	if (!flag){
		if (root -> lson == NULL) return;
		if (root -> lson -> lson && (root -> rson == NULL || root -> lson -> lson -> size > root -> rson -> size)) right_rotate(root);
		else if (root -> lson -> rson && (root -> rson == NULL || root -> lson -> rson -> size > root -> rson -> size)){
			left_rotate(root -> lson);
			right_rotate(root);
		}
		else return;
	}
	else{
		if (root -> rson == NULL) return;
		if (root -> rson -> rson && (root -> lson == NULL || root -> rson -> rson -> size > root -> lson -> size)) left_rotate(root);
		else if (root -> rson -> lson && (root -> lson == NULL || root -> rson -> lson -> size > root -> lson -> size)){
			right_rotate(root -> rson);
			left_rotate(root);
		}
		else return;
	}
	maintain(root -> lson, false);
	maintain(root -> rson, true);
	maintain(root, false);
	maintain(root, true);
};
SBT::SBT(){
	root = new SBTElmt(1 << 31);
}
void SBT::ins(const unsigned val){
	ins_(root, val);
}
unsigned SBT::del(const unsigned rank){
	return del_(root, rank);
}
unsigned SBT::rank(const unsigned n){
	return rank_(root, n);
}
unsigned SBT::size(){
	return root -> size;
}
ll operator *(const pair<ll, ll> &lhs, const pair<ll, ll> &rhs){
	return lhs.first * rhs.second - lhs.second * rhs.first;
}
int main(){
	int n;
	scanf("%d", &n);
	SBT *A = new SBT();
	SBT *B = new SBT();
	int op, a, b;
	int l, mid, r;
	while (n--){
		scanf("%d%d%d", &op, &a, &b);
		switch (op){
			case 0:
				A -> ins(a);
				B -> ins(b);
				break;
			case 1:
				l = 0, r = A -> size();
				while (l < r){
					mid = l + r >> 1;
					ll x = (ll)A -> rank(mid), y = (ll)B -> rank(mid);
					if (make_pair(-x, y) * make_pair(a - x, b) < 0) l = mid + 1;
					else r = mid;
				}
				printf("%d\n", l);
				break;
			case 2:
				A -> del(a);
				B -> del(b);
		}
	}
	return 0;
}
