#ifndef TREE_H
#define TREE_H

#include <boost/iterator/iterator_facade.hpp>
#include <ostream>
#include <stdexcept>

template <class T>
class Tree
{

private:
	struct Node;

public:
	Tree();
	~Tree();

	void clear();
	bool isEmpty() const { return mSize == 0; }

	bool add(const T& value);
	bool remove(const T& value);
	bool contains(const T& value) const;

	size_t size() const { return mSize; }

	void dumpToDot(std::ostream& out) const;

	// Refer to:
	// http://www.boost.org/doc/libs/1_55_0/libs/iterator/doc/iterator_facade.html
	class iterator : public boost::iterator_facade<
		iterator, T, boost::forward_traversal_tag>
	{
	public:
		iterator() : iterator(nullptr, nullptr) {}
		explicit iterator(Node* n, const Tree* tree);

	private:
		friend class boost::iterator_core_access;

		void increment();
		bool equal(iterator const& other) const;
		T& dereference() const;

		Node* mNode;
		const Tree* mTree;
	};

	iterator begin();
	iterator end();

private:
	Tree(const Tree& t) = default;
	Tree& operator=(const Tree& t) = default;

	struct Node
	{
		enum class Color { RED, BLACK };

		Node(const T& v, Color c = Color::RED);
		~Node();

		// Returns the left-most node of the tree rooted at this node.
		Node* leftMostNode();

		// Returns the left-most ancestor of this node. It is possible that this
		// node is its own left-most ancestor.
		Node* leftMostAncestor();

		void dumpToDot(std::ostream& out) const;

		Node* parent;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
		T value;

		Color color;
	};

	std::shared_ptr<Node> mRoot;
	size_t mSize;
};


// --------------------------------------------------------------------------
// Tree implementation
// --------------------------------------------------------------------------
template <class T>
Tree<T>::Tree()
	: mRoot()
	, mSize(0)
{
}

template <class T>
Tree<T>::~Tree()
{
}

template <class T>
void
Tree<T>::clear()
{
	mRoot.reset();
	mSize = 0;
}

template <class T>
bool
Tree<T>::add(const T& value)
{
	Node* current;
	bool isModified = false;

	if (!mRoot) {
		// The root is black.
		mRoot.reset(new Node(value, Node::Color::BLACK));
		mRoot->parent = nullptr;
		current = mRoot.get();
		isModified = true;
	}
	else {
		Node* current = mRoot.get();
		bool done = false;
		while (!done) {
			if (value == current->value) {
				// Already in the tree.
				done = true;
			}
			else if (value < current->value) {
				if (!current->left) {
					current->left.reset(new Node(value));
					current->left->parent = current;
					isModified = done = true;
				}
				current = current->left.get();
			}
			else {
				if (!current->right) {
					current->right.reset(new Node(value));
					current->right->parent = current;
					isModified = done = true;
				}
				current = current->right.get();
			}
		}
	}

	if (isModified) {
		mSize++;
	}
	return isModified;
}

template <class T>
bool
Tree<T>::remove(const T& value)
{
	// Refer to:
	// http://webdocs.cs.ualberta.ca/~holte/T26/del-from-bst.html

	std::shared_ptr<Node> current = mRoot;
	while (current) {
		if (value == current->value) {
			// Found it! Proceed to remove.
			if (!current->left && !current->right) {
				// No sub-tree. Set parent's left or right child to null.
				if (current->parent) {
					if (current == current->parent->left) {
						current->parent->left.reset();
					}
					else {
						current->parent->right.reset();
					}
				}
				else {
					mRoot.reset();
				}
			}
			else if (!current->left && current->right) {
				// Only right sub-tree present.
				current->right->parent = current->parent;
				if (current->parent) {
					if (current == current->parent->left) {
						current->parent->left = current->right;
					}
					else {
						current->parent->right = current->right;
					}
				}
				else {
					mRoot = current->right;
				}
			}
			else if (current->left && !current->right) {
				// Only left sub-tree present.
				current->left->parent = current->parent;
				if (current->parent) {
					if (current == current->parent->left) {
						current->parent->left = current->left;
					}
					else {
						current->parent->right = current->left;
					}
				}
				else {
					mRoot = current->left;
				}
			}
			else {
				// Both sub-trees present. Replace the current node's value with
				// the smallest value in the right sub-tree, then delete that
				// node containing the smallest value.
				Node* smallest = current->right->leftMostNode();
				current->value = smallest->value;
				if (smallest->right) {
					smallest->right->parent = smallest->parent;
				}
				smallest->parent->right = smallest->right;
			}

			mSize--;
			return true;
		}

		if (value < current->value) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return false;
}

template <class T>
bool
Tree<T>::contains(const T& value) const
{
	Node* current = mRoot.get();
	while (current) {
		if (value == current->value) {
			return true;
		}

		if (value < current->value) {
			current = current->left.get();
		}
		else {
			current = current->right.get();
		}
	}
	return false;
}

template <class T>
void
Tree<T>::dumpToDot(std::ostream& out) const
{
	out << "digraph BST {\n"
		<< "  graph [ordering=\"out\"];\n";
	if (mRoot) {
		mRoot->dumpToDot(out);
	}
	out << "}" << std::endl;
}

template <class T>
typename Tree<T>::iterator
Tree<T>::begin()
{
	Node* n = mRoot ? mRoot->leftMostNode() : nullptr;
	return iterator(n, this);
}

template <class T>
typename Tree<T>::iterator
Tree<T>::end()
{
	return iterator();
}


// --------------------------------------------------------------------------
// Node implementation
// --------------------------------------------------------------------------
template <class T>
Tree<T>::Node::Node(const T& v, Color c)
	: value(v)
	, color(c)
{
}

template <class T>
Tree<T>::Node::~Node()
{
}

template <class T>
typename Tree<T>::Node*
Tree<T>::Node::leftMostNode()
{
	Node* current = this;
	while (current->left) {
		current = current->left.get();
	}
	return current;
}

template <class T>
typename Tree<T>::Node*
Tree<T>::Node::leftMostAncestor()
{
	Node* current = this;
	while (current->parent && current->parent->right.get() == current) {
		current = current->parent;
	}
	return current;
}

template <class T>
void
Tree<T>::Node::dumpToDot(std::ostream& out) const
{
	if (!left && !right) {
		out << "  " << value << ";\n";
		return;
	}

	if (left) {
		out << "  " << value << " -> " << left->value << ";\n";
	}

	if (right) {
		out << "  " << value << " -> " << right->value << ";\n";
	}

	if (left) {
		left->dumpToDot(out);
	}

	if (right) {
		right->dumpToDot(out);
	}
}

// --------------------------------------------------------------------------
// Iterator implementation
// --------------------------------------------------------------------------

template <class T>
Tree<T>::iterator::iterator(Tree<T>::Node* n, const Tree<T>* tree)
	: mNode(n)
	, mTree(tree)
{
}

template <class T>
void
Tree<T>::iterator::increment()
{
	if (!mNode) {
		throw std::logic_error("Bad iterator.");
	}

	if (mNode->right) {
		// If there is a right subtree, go to the lowest value of that subtree.
		mNode = mNode->right->leftMostNode();
	}
	else if (mNode->parent && mNode->parent->left.get() == mNode) {
		// The current node is the left child of its parent, so the next node is
		// just the parent.
		mNode = mNode->parent;
	}
	else {
		// Pop back up to the top of this subtree, then scoot over to the
		// parent.
		mNode = mNode->leftMostAncestor()->parent;
	}
}

template <class T>
bool
Tree<T>::iterator::equal(iterator const& other) const
{
	if (mNode && other.mNode) {
		return mNode->value == other.mNode->value;
	}
	return mNode == other.mNode;
}

template <class T>
T&
Tree<T>::iterator::dereference() const
{
	return mNode->value;
}

#endif // TREE_H