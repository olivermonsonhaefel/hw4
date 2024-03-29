#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"
#include "print_bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void rotateRight(AVLNode<Key, Value>* n);
		void rotateLeft(AVLNode<Key, Value>* n);
		void insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
		void removeFix(AVLNode<Key, Value>* n, int diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
//check if parent is null before setting child. If it is, update root of the tree
//don't worry about changing balances here, do it in the insert-fix function
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* n) {
	AVLNode<Key, Value>* m = n->getLeft();
	AVLNode<Key, Value>* temp = m->getRight();
	AVLNode<Key, Value>* parent = n->getParent();

	m->setRight(n);
	n->setParent(m);

	m->setParent(parent);
	if(parent != NULL) {
		if(parent->getLeft() == n) parent->setLeft(m);
		else parent->setRight(m);
	}
	else {
		this->root_ = m;
	}
	n->setLeft(temp);
	if(temp != nullptr) {
		temp->setParent(n);
	}
	
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* n) {
	AVLNode<Key, Value>* m = n->getRight();
	AVLNode<Key, Value>* temp = m->getLeft();
	AVLNode<Key, Value>* parent = n->getParent();

	m->setLeft(n);
	n->setParent(m);

	m->setParent(parent);
	if(parent != NULL) {
		if(parent->getRight() == n) parent->setRight(m);
		else parent->setLeft(m);
	}
	else {
		this->root_ = m;
	}
	n->setRight(temp);
	
	if(temp != nullptr) {
		temp->setParent(n);
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n) {
	if (p == nullptr) {
		return;
	}
	
	AVLNode<Key, Value>* g = p->getParent();
	if(g == nullptr) return;

	if(g->getLeft() == p) {
		g->updateBalance(-1);

		if(g->getBalance() == 0) return;
		else if(g->getBalance() == -1) insertFix(g, p);
		else {
			if(p->getLeft() == n) {
				rotateRight(g);
				g->setBalance(0);
				p->setBalance(0);
			}
			else {
				rotateLeft(p);
				rotateRight(g);
				if(n->getBalance() == -1) {
					p->setBalance(0);
					g->setBalance(1);
					n->setBalance(0);
				}
				else if(n->getBalance() == 0) {
					p->setBalance(0);
					g->setBalance(0);
					n->setBalance(0);
				}
				else if (n->getBalance() == 1) {
					p->setBalance(-1);
					g->setBalance(0);
					n->setBalance(0);
				}
			}
		}
	}
	else {
		g->updateBalance(1);
		if(g->getBalance() == 0) return;
		else if(g->getBalance() == 1) insertFix(g, p);
		else {
			if(p->getRight() == n) {
				rotateLeft(g);
				g->setBalance(0);
				p->setBalance(0);
			}
			else {
				rotateRight(p);
				rotateLeft(g);
				if(n->getBalance() == 1) {
					p->setBalance(0);
					g->setBalance(-1);
					n->setBalance(0);
				}
				else if(n->getBalance() == 0) {
					p->setBalance(0);
					g->setBalance(0);
					n->setBalance(0);
				}
				else if (n->getBalance() == -1) {
					p->setBalance(1);
					g->setBalance(0);
					n->setBalance(0);
				}
			}
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
		if(this->root_ == NULL) {
			this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
			return;
		}
		AVLNode<Key, Value> * tempN = static_cast<AVLNode<Key, Value>*>(this->root_);
		AVLNode<Key, Value> * newNode;
		while(true) {
			if(new_item.first == tempN->getKey()) {
				tempN->setValue(new_item.second);
				break;
			}
			else if(new_item.first < tempN->getKey()) {
				if(tempN->getLeft() == NULL) {
					newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, tempN);
					tempN->setLeft(newNode);
					break;
				}
				else {
					tempN = tempN->getLeft();
				}
			}
			else {
				if(tempN->getRight() == NULL) {
					newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, tempN);
					tempN->setRight(newNode);
					break;
				}
				else {
					tempN = tempN->getRight();
				}
			}
		}
		if(tempN->getBalance() == -1 || tempN->getBalance() == 1) {
			tempN->setBalance(0);
		}
		else {
			if (newNode == tempN->getLeft()) {
				tempN->setBalance(-1);
			} else {
				tempN->setBalance(1);
			}
			insertFix(tempN, newNode);
		}
		//this->printRoot(this->root_);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff) {
	if(n == NULL) return;
	AVLNode<Key, Value>* p = n->getParent();
	int nDiff = 0;
	if(p != NULL) {
		if(p->getLeft() == n) {
			nDiff = 1;
		}
		else {
			nDiff = -1;
		}
	}
	if(diff == -1) {
		if(n->getBalance() + diff == -2) {
			AVLNode<Key, Value>* c = n->getLeft();
			if(c->getBalance() == -1) {
				rotateRight(n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, nDiff);
			}
			else if(c->getBalance() == 0) {
				rotateRight(n);
				n->setBalance(-1);
				c->setBalance(1);
			}
			else {
				AVLNode<Key, Value>* g = c->getRight();
				rotateLeft(c);
				rotateRight(n);
				if(g->getBalance() == 1) {
					n->setBalance(0);
					c->setBalance(-1);
					g->setBalance(0);
				}
				else if(g->getBalance() == 0) {
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else {
					n->setBalance(1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, nDiff);
			}
		}

		else if(n->getBalance()+diff == -1) {
			n->setBalance(-1);
		}
		else {
			n->setBalance(0);
			removeFix(p, nDiff);
		}
	}


	else {
		if(n->getBalance() + diff == 2) {
			AVLNode<Key, Value>* c = n->getRight();
			if(c->getBalance() == 1) {
				rotateLeft(n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, nDiff);
			}
			else if(c->getBalance() == 0) {
				rotateLeft(n);
				n->setBalance(1);
				c->setBalance(-1);
			}
			else {
				AVLNode<Key, Value>* g = c->getLeft();
				rotateRight(c);
				rotateLeft(n);
				if(g->getBalance() == -1) {
					n->setBalance(0);
					c->setBalance(1);
					g->setBalance(0);
				}
				else if(g->getBalance() == 0) {
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else {
					n->setBalance(-1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, nDiff);
			}
		}

		else if(n->getBalance()+diff == 1) {
			n->setBalance(1);
		}
		else {
			n->setBalance(0);
			removeFix(p, nDiff);
		}
	}
}


template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
		int diff = 0;
		if(this->root_ == NULL) return;
		AVLNode<Key, Value>* tempN = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));

    if (tempN == NULL) {
        return; // Node not found
    }
		//both children
		if(tempN->getLeft() != nullptr && tempN->getRight() != nullptr) {
			AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(tempN));
      nodeSwap(tempN, pred);
		}
		AVLNode<Key, Value>* p = tempN->getParent();
		if(p != NULL) {
			if(p->getLeft() == tempN) {
				diff = 1;
			}
			else {
				diff = -1;
			}
		}

		//no children
		if (tempN->getLeft() == nullptr && tempN->getRight() == nullptr) {
        if (tempN == this->root_) {
            this->root_ = nullptr;
        } else {
            AVLNode<Key, Value>* parent = tempN->getParent();
            if (parent->getLeft() == tempN) parent->setLeft(NULL);
            else parent->setRight(NULL);
        }
    }
    // Node with only one child
    else {
        AVLNode<Key, Value>* child = tempN->getLeft() ? tempN->getLeft() : tempN->getRight();
        if (tempN == this->root_) {
            this->root_ = child;
						child->setParent(nullptr);
        } else {
            if (p->getLeft() == tempN) p->setLeft(child);
            else p->setRight(child);
            child->setParent(p);
        }
    }

		delete tempN;
		removeFix(p, diff);

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
