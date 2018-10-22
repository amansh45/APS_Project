#include "headers.h"

rbNode::rbNode(int x) {
	val=x; 
	parent = left = right = NULL; 
	color = RED;
}

rbNode * rbNode::uncle() { 
	if (parent == NULL or parent->parent == NULL) 
		return NULL; 

	if (parent->isOnLeft()) 
		return parent->parent->right; 
	else
		return parent->parent->left; 
}

bool rbNode::isOnLeft() { return this == parent->left; }

rbNode * rbNode::sibling() { 
	if (parent == NULL) 
		return NULL; 

	if (isOnLeft()) 
		return parent->right; 

	return parent->left; 
} 
 
void rbNode::moveDown(rbNode *nParent) { 
	if (parent != NULL) { 
	if (isOnLeft()) { 
		parent->left = nParent; 
	} else { 
		parent->right = nParent; 
	} 
	} 
	nParent->parent = parent; 
	parent = nParent; 
} 

bool rbNode::hasRedChild() { 
	return (left != NULL and left->color == RED) or 
		(right != NULL and right->color == RED); 
}

void RBTree::leftRotate(rbNode *x) { 
	rbNode *nParent = x->right; 
	if (x == root) 
	root = nParent; 
	x->moveDown(nParent); 
	x->right = nParent->left; 
	if (nParent->left != NULL) 
	nParent->left->parent = x; 
	nParent->left = x; 
}

void RBTree::rightRotate(rbNode *x) { 
	rbNode *nParent = x->left; 
	if (x == root) 
	root = nParent; 
	x->moveDown(nParent); 
	x->left = nParent->right; 
	if (nParent->right != NULL) 
	nParent->right->parent = x; 
	nParent->right = x; 
}

void RBTree::swapColors(rbNode *x1, rbNode *x2) { 
	COLOR temp; 
	temp = x1->color; 
	x1->color = x2->color; 
	x2->color = temp; 
}

void RBTree::swapValues(rbNode *u, rbNode *v) { 
	int temp; 
	temp = u->val; 
	u->val = v->val; 
	v->val = temp; 
} 

void RBTree::fixRedRed(rbNode *x) { 
	if (x == root) { 
		x->color = BLACK; 
		return; 
	} 
	rbNode *parent = x->parent, *grandparent = parent->parent, 
		*uncle = x->uncle(); 

	if (parent->color != BLACK) { 
		if (uncle != NULL && uncle->color == RED) { 
			parent->color = BLACK; 
			uncle->color = BLACK; 
			grandparent->color = RED; 
			fixRedRed(grandparent); 
		} else { 
			if (parent->isOnLeft()) { 
			if (x->isOnLeft()) { 
				swapColors(parent, grandparent); 
			} else { 
				leftRotate(parent); 
				swapColors(x, grandparent); 
			} 
			rightRotate(grandparent); 
			} else { 
			if (x->isOnLeft()) { 
				rightRotate(parent); 
				swapColors(x, grandparent); 
			} else { 
				swapColors(parent, grandparent); 
			} 

			leftRotate(grandparent); 
			} 
		} 
	} 
}

rbNode * RBTree::successor(rbNode *x) { 
	rbNode *temp = x; 
	while (temp->left != NULL) 
		temp = temp->left; 

	return temp; 
}

rbNode * RBTree::BSTreplace(rbNode *x) { 
	if (x->left != NULL and x->right != NULL) 
		return successor(x->right); 

	if (x->left == NULL and x->right == NULL) 
		return NULL; 
	
	if (x->left != NULL) 
		return x->left; 
	else
		return x->right; 
}

void RBTree::deleteNode(rbNode *v) { 
	rbNode *u = BSTreplace(v); 
	bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK)); 
	rbNode *parent = v->parent; 

	if (u == NULL) { 
		if (v == root) { 
			root = NULL; 
		} else { 
			if (uvBlack) { 
				fixDoubleBlack(v); 
			} else { 
			if (v->sibling() != NULL) 
				v->sibling()->color = RED; 
			} 
			if (v->isOnLeft()) { 
				parent->left = NULL; 
			} else { 
				parent->right = NULL; 
			} 
		} 
		delete v; 
		return; 
	} 

	if (v->left == NULL or v->right == NULL) { 
		if (v == root) { 
			v->val = u->val; 
			v->left = v->right = NULL; 
			delete u; 
		} else { 
			if (v->isOnLeft()) { 
				parent->left = u; 
			} else { 
				parent->right = u; 
			} 
			delete v; 
			u->parent = parent; 
			if (uvBlack) { 
				fixDoubleBlack(u); 
			} else { 
				u->color = BLACK; 
			} 
		} 
		return; 
	} 

	swapValues(u, v); 
	deleteNode(u); 
}

void RBTree::fixDoubleBlack(rbNode *x) { 
	if (x == root) 
		return; 

	rbNode *sibling = x->sibling(), *parent = x->parent; 
	if (sibling == NULL) { 
		fixDoubleBlack(parent); 
	} else { 
		if (sibling->color == RED) { 
			parent->color = RED; 
			sibling->color = BLACK; 
			if (sibling->isOnLeft()) { 
				rightRotate(parent); 
			} else { 
				leftRotate(parent); 
			} 
			fixDoubleBlack(x); 
		} else { 
			if (sibling->hasRedChild()) { 
				if (sibling->left != NULL and sibling->left->color == RED) { 
					if (sibling->isOnLeft()) { 
						sibling->left->color = sibling->color; 
						sibling->color = parent->color; 
						rightRotate(parent); 
					} else { 
						sibling->left->color = parent->color; 
						rightRotate(sibling); 
						leftRotate(parent); 
					} 
				} else { 
					if (sibling->isOnLeft()) { 
						sibling->right->color = parent->color; 
						leftRotate(sibling); 
						rightRotate(parent); 
					} else { 
						sibling->right->color = sibling->color; 
						sibling->color = parent->color; 
						leftRotate(parent); 
					} 
				} 
				parent->color = BLACK; 
			} else { 
				sibling->color = RED; 
				if (parent->color == BLACK) 
					fixDoubleBlack(parent); 
				else
					parent->color = BLACK; 
			} 
		} 
	} 
}

void RBTree::levelOrder(rbNode *x) { 
	if (x == NULL) 
		return; 
	queue<rbNode *> q; 
	rbNode *curr; 
	q.push(x); 

	while (!q.empty()) { 
		curr = q.front(); 
		q.pop(); 
		cout << curr->val << " "; 
		if (curr->left != NULL) 
			q.push(curr->left); 
		if (curr->right != NULL) 
			q.push(curr->right); 
	} 
}

void RBTree::inorder(rbNode *x) { 
	if (x == NULL) 
		return; 
	inorder(x->left); 
	cout << x->val << " "; 
	inorder(x->right); 
}

RBTree::RBTree() { root = NULL; }

RBTree::~RBTree() {}

rbNode * RBTree::getRoot() { return root; }

rbNode * RBTree::search(int n) { 
	rbNode *temp = root; 
	while (temp != NULL) { 
		if (n < temp->val) { 
			if (temp->left == NULL) 
			break; 
			else
			temp = temp->left; 
		} else if (n == temp->val) { 
			break; 
		} else { 
			if (temp->right == NULL) 
			break; 
			else
			temp = temp->right; 
		} 
	} 
	return temp; 
}

void RBTree::insert(int n) { 
	rbNode *newNode = new rbNode(n); 
	if (root == NULL) { 
		newNode->color = BLACK; 
		root = newNode; 
	} else { 
		rbNode *temp = search(n); 
		if (temp->val == n) { 
			return; 
		} 
		newNode->parent = temp; 
		if (n < temp->val) 
			temp->left = newNode; 
		else
			temp->right = newNode; 

		fixRedRed(newNode); 
	} 
} 

void RBTree::deleteByVal(int n) { 
	if (root == NULL) 
		return; 

	rbNode *v = search(n), *u; 

	if (v->val != n) { 
		cout << "No node found to delete with value:" << n << endl; 
		return; 
	} 

	deleteNode(v); 
}

void RBTree::printInOrder() { 
	cout << "Inorder: " << endl; 
	if (root == NULL) 
		cout << "Tree is empty" << endl; 
	else
		inorder(root); 
	cout << endl; 
}

void RBTree::clearNodes(rbNode *x) {
	if(x==NULL)
		return;
	clearNodes(x->left);
	clearNodes(x->right);
	delete x;
}

void RBTree::clearRBTree() {
	if(root == NULL)
		cout<<"Tree is empty"<<endl;
	else
		clearNodes(root);
}

int RBTree::returnMin(rbNode *x) {
	if(x->left==NULL)
		return x->val;
	else
		returnMin(x->left);
}

int RBTree::retrieveMinRB() {
	if(root == NULL)
		return -1;
	else
		return returnMin(root);	
}

void RBTree::printLevelOrder() { 
	cout << "Level order: " << endl; 
	if (root == NULL) 
		cout << "Tree is empty" << endl; 
	else
		levelOrder(root); 
	cout << endl; 
}
