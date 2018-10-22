#include "headers.h"

int height(struct avlNode *N) { 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

int max(int a, int b) { 
	return (a > b)? a : b; 
} 

struct avlNode* newNode(int key) { 
	struct avlNode* node = (struct avlNode*) malloc(sizeof(struct avlNode)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1;
	return(node); 
} 

struct avlNode *rightRotate(struct avlNode *y) { 
	struct avlNode *x = y->left; 
	struct avlNode *T2 = x->right; 

	x->right = y; 
	y->left = T2; 

	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	return x; 
} 

struct avlNode *leftRotate(struct avlNode *x) { 
	struct avlNode *y = x->right; 
	struct avlNode *T2 = y->left; 

	y->left = x; 
	x->right = T2; 

	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	return y; 
} 

int getBalance(struct avlNode *N) { 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

struct avlNode* insert(struct avlNode* node, int key) { 
	
	if (node == NULL) 
		return(newNode(key)); 

	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	else
		return node; 

	node->height = 1 + max(height(node->left), height(node->right)); 

	int balance = getBalance(node); 

	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	if (balance > 1 && key > node->left->key) { 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	if (balance < -1 && key < node->right->key) { 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	return node; 
} 

struct avlNode * minValueNode(struct avlNode* node) { 
	struct avlNode* current = node; 

	while (current->left != NULL) 
		current = current->left; 

	return current; 
} 

struct avlNode* deleteNode(struct avlNode* root, int key) { 

	if (root == NULL) 
		return root; 

	if ( key < root->key ) 
		root->left = deleteNode(root->left, key); 
	else if( key > root->key ) 
		root->right = deleteNode(root->right, key); 
	else { 
		if( (root->left == NULL) || (root->right == NULL) ) { 
			struct avlNode *temp = root->left ? root->left : root->right; 
			if (temp == NULL) { 
				temp = root; 
				root = NULL; 
			} 
			else 
				*root = *temp;
			free(temp); 
		} 
		else { 
			struct avlNode* temp = minValueNode(root->right); 

			root->key = temp->key; 

			root->right = deleteNode(root->right, temp->key); 
		} 
	} 

	if (root == NULL) 
		return root; 

	root->height = 1 + max(height(root->left), height(root->right)); 

	int balance = getBalance(root); 

	if (balance > 1 && getBalance(root->left) >= 0) 
		return rightRotate(root); 

	if (balance > 1 && getBalance(root->left) < 0) { 
		root->left = leftRotate(root->left); 
		return rightRotate(root); 
	} 

	if (balance < -1 && getBalance(root->right) <= 0) 
		return leftRotate(root); 

	if (balance < -1 && getBalance(root->right) > 0) { 
		root->right = rightRotate(root->right); 
		return leftRotate(root); 
	} 

	return root; 
} 

void preOrder(struct avlNode *root) { 
	if(root != NULL) { 
		cout<<root->key<<" "; 
		preOrder(root->left); 
		preOrder(root->right); 
	} 
}

int retrieveMinAVL(struct avlNode *root) {
	if(root->left == NULL)
		return root->key;
	else
		retrieveMinAVL(root->left);
}

void clearAVL(struct avlNode *root) {
	if(root != NULL) {
		clearAVL(root->left);
		clearAVL(root->right);
		free(root);
	}
}