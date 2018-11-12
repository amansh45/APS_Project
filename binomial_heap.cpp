#include "headers.h"

list<struct node *>::iterator merge_trees(list<struct node *>::iterator itr1, list<struct node *>::iterator itr2, list<struct node *> &heap) {
	if((*itr1)->minimum > (*itr2)->minimum) {
		(*itr1)->tree_parent = (*itr2);
		(*itr1)->neighbour = (*itr2)->child;
		(*itr2)->child = (*itr1);
		(*itr2)->degree +=1;
		return itr1;
	} else {
		(*itr2)->tree_parent = (*itr1);
		(*itr2)->neighbour = (*itr1)->child;
		(*itr1)->child = (*itr2);
		(*itr1)->degree +=1;
		return itr2;
	}
}

void printTree(struct node *head) { 
    while(head) { 
        cout<<head->minimum<<" "; 
        printTree(head->child); 
        head = head->neighbour; 
    } 
} 
   
void printHeap(list<struct node *> _heap) { 
    list<struct node *>::iterator it; 
    it = _heap.begin(); 
    while (it != _heap.end()) { 
        printTree(*it); 
        cout<<endl;
        it++; 
    }
} 

void clearBinomialTree(struct node *head) {
	while(head) {
		clearBinomialTree(head->child);
		struct node *temp = head;
		head = head->neighbour;
		free(temp);
	}
}

void clearBinomial(list<struct node *> &heap) {
	list<struct node *>::iterator it;
	it = heap.begin();
	while(it != heap.end()) {
		clearBinomialTree(*it);
		it++;
	}	
	heap.clear();
}

void modify_heap(list<struct node *> &heap) {
	list<struct node *>::iterator itr1, itr2;
	itr1=heap.begin();
	itr2=heap.begin();
	advance(itr2, 1);
	while(true) {
		if(itr2==heap.end() || itr1 == heap.end())
			break;
		if((*itr1)->degree == (*itr2)->degree) {
			list<struct node *>::iterator del_itr;
			del_itr = merge_trees(itr1, itr2, heap);
			
			if(del_itr == itr1) {
				if(itr1==heap.begin()) {
					heap.erase(del_itr);
					itr1 = itr2 = heap.begin();
					if(itr2!=heap.end())
						advance(itr2, 1);
				} else {
					list<struct node *>::iterator prev_itr;
					prev_itr = prev(itr1);
					itr1 = itr2 = prev_itr;
					heap.erase(del_itr);
					if(itr1!=heap.end())
						advance(itr1, 1);
					if(itr1!=heap.end())
						advance(itr2, 2);
				}
			} else if(del_itr == itr2) {
				itr2=itr1;
				heap.erase(del_itr);
				if(itr2!=heap.end()) {
					advance(itr2, 1);
				}
			}
		} else {
			advance(itr1,1);
			advance(itr2,1);
		}
	}
}

list<struct node *>::iterator retrieve_min(list<struct node *> &heap) {
	list<struct node *>::iterator min;
	int val;
	if(heap.size() == 0) 
		return heap.end();
	for(list <struct node *>::iterator itr=heap.begin();itr!=heap.end();itr++) {
		if(itr==heap.begin()) 
			min = itr;
		else {
			if((*itr)->minimum < (*min)->minimum)
				min=itr;
		}
	}
	return min;
}

void insert_to_heap(list<struct node *> &heap, int value) {
	struct node *ptr=(struct node *)malloc(sizeof(struct node));
	ptr->minimum=value;
	ptr->degree=0;
	ptr->child=NULL;
	ptr->neighbour=NULL;
	heap.push_front(ptr);
	modify_heap(heap);
}

list<struct node *> union_heap(list<struct node *> heap1, list<struct node *> heap2) {
	list<struct node *> heap;
	list<struct node *>::iterator itr1, itr2;
	itr1 = heap1.begin();
	itr2 = heap2.begin();
	while(itr1!=heap1.end() && itr2!=heap2.end()) {
		if((*itr1)->degree <= (*itr2)->degree) {
			heap.push_back(*itr1);
			itr1++;
		}
		else {
			heap.push_back(*itr2);
			itr2++;
		}
	}
	if(itr1==heap1.end() && itr2!=heap2.end()) {
		while(itr2!=heap2.end()) {
			heap.push_back(*itr2);
			itr2++;
		}
	} else if(itr2==heap2.end() && itr1!=heap1.end()) {
		while(itr1!=heap1.end()) {
			heap.push_back(*itr1);
			itr1++;
		}
	}
	modify_heap(heap);
	return heap;
}

struct node *search_binomial_tree(struct node *h, int val) { 
    if (h == NULL) 
    	return NULL; 

    if (h->minimum == val) 
        return h; 
  
    struct node *res = search_binomial_tree(h->child, val); 
    
    if(res != NULL) 
       return res; 
  
    return search_binomial_tree(h->neighbour, val); 
}

bool search_binomial(list<struct node *> &heap, int val) {
	struct node * sample = NULL;
	for(list<struct node *>::iterator itr = heap.begin();itr!=heap.end();itr++) {
		sample = search_binomial_tree((*itr), val);
		if(sample != NULL)
			break;
	}
	if(sample == NULL)
		return false;
	else 
		return true;

}



struct node *extract_min(list<struct node *> &heap) {
	list<struct node *>::iterator itr = retrieve_min(heap);
	list<struct node *> another_heap;
	struct node *child = (*itr)->child;
	(*itr)->child = NULL;
	struct node *mini = *itr;
	heap.erase(itr);
	
	while(child!=NULL) {
		struct node *temp = child->neighbour;
		child->neighbour = NULL;
		child->tree_parent=NULL;
		another_heap.push_front(child);
		child = temp;
	}

	list<struct node *> new_heap = union_heap(heap, another_heap);
	heap = new_heap;
	return mini;
}

void adjust_tree_on_change(struct node *ptr, vector<struct node *> &pointers) {
	struct node *myparent = ptr->tree_parent; 
   
    while (myparent != NULL && ptr->minimum < myparent->minimum) { 
        int temp = ptr->minimum;
        int tvid = ptr->vid;
        
        ptr->minimum = myparent->minimum;
        ptr->vid = myparent->vid;

        myparent->minimum = temp;
        myparent->vid = tvid;
        
        struct node * swap_parent = ptr->parent;
        ptr->parent = myparent->parent;
        myparent->parent = swap_parent;

        pointers[myparent->vid]=myparent;
        pointers[ptr->vid] = ptr;
        ptr = myparent; 
        myparent = myparent->tree_parent; 
    } 
}