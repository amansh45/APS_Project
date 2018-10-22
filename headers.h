#include <iostream>
#include <list>
#include <iterator>
#include <queue>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

struct node {
	int minimum, degree;
	struct node *child, *neighbour;
};

struct avlNode { 
	int key; 
	struct avlNode *left; 
	struct avlNode *right; 
	int height; 
};

enum COLOR { RED, BLACK}; 

class rbNode { 
	public: 
		int val; 
		COLOR color; 
		rbNode *left, *right, *parent; 
		rbNode(int);
		rbNode *uncle();
		bool isOnLeft();
		rbNode *sibling();
		void moveDown(rbNode *);
		bool hasRedChild(); 
};

class RBTree { 
	rbNode *root; 

	void leftRotate(rbNode *);

	void rightRotate(rbNode *);

	void swapColors(rbNode *, rbNode *);

	void swapValues(rbNode *, rbNode *); 

	void fixRedRed(rbNode *);

	rbNode *successor(rbNode *); 

	rbNode *BSTreplace(rbNode *); 

	void deleteNode(rbNode *); 

	void fixDoubleBlack(rbNode *); 

	void levelOrder(rbNode *);

	void inorder(rbNode *);

	public: 
		RBTree(); 

		~RBTree();

		rbNode *getRoot(); 

		rbNode *search(int);

		void insert(int);

		void deleteByVal(int);

		void printInOrder();

		void printLevelOrder();

		void clearNodes(rbNode *);

		void clearRBTree();

		int retrieveMinRB();

		int returnMin(rbNode *);
}; 

list<struct node *>::iterator merge_trees(list<struct node *>::iterator, list<struct node *>::iterator, list<struct node *> &);

void printTree(struct node *);

void printHeap(list<struct node *>);

void modify_heap(list<struct node *> &);

list<struct node *>::iterator retrieve_min(list<struct node *> &);

void insert_to_heap(list<struct node *> &, int);

list<struct node *> union_heap(list<struct node *>, list<struct node *>);

void extract_min(list<struct node *> &);

int height(struct avlNode *);

int max(int, int);

struct avlNode* newNode(int);

struct avlNode *rightRotate(struct avlNode *);

struct avlNode *leftRotate(struct avlNode *);

int getBalance(struct avlNode *);

struct avlNode* insert(struct avlNode*, int);

struct avlNode * minValueNode(struct avlNode*);

struct avlNode* deleteNode(struct avlNode*, int);

void preOrder(struct avlNode *);

void clearAVL(struct avlNode *);

void clearBinomial(list<struct node *> &);

void clearBinomialTree(struct node *);

int retrieveMinAVL(struct avlNode *);

struct node *search_binomial_tree(struct node *, int);

bool search_binomial(list <struct node *> &, int);