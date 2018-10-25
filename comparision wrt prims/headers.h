#include <iostream>
#include <list>
#include <iterator>
#include <queue>
#include <random>
#include <chrono>
#include <fstream>
#include <climits>

using namespace std;
using namespace std::chrono;

struct node {
	int minimum, degree, vid;
	struct node *child, *neighbour, *parent, *tree_parent;
};

struct avlNode { 
	int key, vid; 
	struct avlNode *left; 
	struct avlNode *right;
	struct avlNode *parent; 
	int height; 
};

enum COLOR { RED, BLACK}; 

class rbNode { 
	public: 
		int val, vid; 
		COLOR color; 
		rbNode *left, *right, *parent, *mst_parent; 
		rbNode(int, int, rbNode*);
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

		void insert(int, int, rbNode *);

		void deleteByVal(int);

		void printInOrder();

		void printLevelOrder();

		void clearNodes(rbNode *);

		void clearRBTree();

		rbNode *retrieveMinRB();

		rbNode *returnMin(rbNode *);

		rbNode *AVLpreOrderSearch(int);

		rbNode *search_helper(rbNode *, int);
}; 

list<struct node *>::iterator merge_trees(list<struct node *>::iterator, list<struct node *>::iterator, list<struct node *> &);

void printTree(struct node *);

void printHeap(list<struct node *>);

void modify_heap(list<struct node *> &);

list<struct node *>::iterator retrieve_min(list<struct node *> &);

void insert_to_heap(list<struct node *> &, int);

list<struct node *> union_heap(list<struct node *>, list<struct node *>);

struct node *extract_min(list<struct node *> &);

int height(struct avlNode *);

int max(int, int);

struct avlNode* newNode(int, int);

struct avlNode *rightRotate(struct avlNode *);

struct avlNode *leftRotate(struct avlNode *);

int getBalance(struct avlNode *);

struct avlNode* insert(struct avlNode*, int, int);

struct avlNode * minValueNode(struct avlNode*);

struct avlNode* deleteNode(struct avlNode*, int);

void preOrder(struct avlNode *);

void clearAVL(struct avlNode *);

void clearBinomial(list<struct node *> &);

void clearBinomialTree(struct node *);

struct avlNode * retrieveMinAVL(struct avlNode *);

struct node *search_binomial_tree(struct node *, int);

bool search_binomial(list <struct node *> &, int);

struct avlNode * search_avl(struct avlNode *, int);

void adjust_tree_on_change(struct node *, vector<struct node *> &);