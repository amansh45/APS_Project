#include "headers.h"
int arr[10000000];

vector<vector<pair<int, int>>> adj_list;
vector<bool> bitmap;

int random(int srange, int erange) {
	random_device rd;
	mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(srange,erange);
	return dist(mt);
}

void compare_RB_AVL_BINOMIAL() {
	ofstream avl_insert, rb_insert, binomial_insert, avl_rmin, rb_rmin, binomial_rmin, avl_xmin, rb_xmin, binomial_xmin, avl_search, rb_search, binomial_search;
 	avl_insert.open ("avl_insert.txt");
 	rb_insert.open ("rb_insert.txt");
 	binomial_insert.open("binomial_insert.txt");

 	avl_rmin.open ("avl_rmin.txt");
 	rb_rmin.open ("rb_rmin.txt");
 	binomial_rmin.open("binomial_rmin.txt");
 	
 	avl_xmin.open ("avl_xmin.txt");
 	rb_xmin.open ("rb_xmin.txt");
 	binomial_xmin.open("binomial_xmin.txt");
 	
 	avl_search.open ("avl_search.txt");
 	rb_search.open ("rb_search.txt");
 	binomial_search.open("binomial_search.txt");

	for(int i=10000;i<10000000;i+=10000) {
		int times = i;
		

		/*------------------BINOMIAL HEAP----------------*/

		// creating binomial heap
		list<struct node *> heap;
		cout<<times<<endl;
		//cout<<endl<<"For array of size: "<<times<<endl;
		auto start1 = high_resolution_clock::now();
		for(int j=0;j<times;j++) 
			insert_to_heap(heap, arr[j]);
		auto stop1 = high_resolution_clock::now(); 
		auto duration1 = duration_cast<microseconds>(stop1 - start1); 
		//cout << "Time taken by binomial heap to build: "<< duration1.count() << " microseconds" << endl;
		binomial_insert<<times<<" "<<duration1.count()<<endl;
		
		
		// findinging minimum in binomial heap
		auto start10 = high_resolution_clock::now();
		list<struct node *>::iterator itr = retrieve_min(heap);
		int mymin=(*itr)->minimum;
		auto stop10 = high_resolution_clock::now(); 
		auto duration10 = duration_cast<microseconds>(stop10 - start10); 
		//cout << "Time taken by binomial heap to retrieve minimum: "<< duration10.count() << " microseconds" <<" and search results: "<<mymin<< endl;
		binomial_rmin<<times<<" "<<duration10.count()<<endl;
		

		// extracting minimum from binomial heap
		auto start11 = high_resolution_clock::now();
		struct node * min_node=extract_min(heap);
		auto stop11 = high_resolution_clock::now(); 
		auto duration11 = duration_cast<microseconds>(stop11 - start11); 
		//cout << "Time taken by binomial heap to extract minimum: "<< duration11.count() << " microseconds" << endl;
		binomial_xmin<<times<<" "<<duration11.count()<<endl;

		// searching for a random number in binomial heap
		auto start12 = high_resolution_clock::now();
		int ridx = random(0, times-1);
		int sval = arr[ridx];
		bool flag = search_binomial(heap, sval);
		auto stop12 = high_resolution_clock::now(); 
		auto duration12 = duration_cast<microseconds>(stop12 - start12); 
		//cout << "Time taken by binomial heap to search element "<<sval<<": "<< duration12.count() << " microseconds "<<" and search results: "<<flag<<endl;
		binomial_search<<times<<" "<<duration12.count()<<endl;


		// clearing the binomial heap
		clearBinomial(heap);

		



		/*------------------AVL TREE----------------*/

		// creating AVL tree
		struct avlNode *root = NULL;  
		auto start2 = high_resolution_clock::now();
		for(int j=0;j<times;j++) 
			root = insert(root, -1, arr[j]);
		auto stop2 = high_resolution_clock::now(); 
		auto duration2 = duration_cast<microseconds>(stop2 - start2); 
		//cout << "Time taken by AVL tree: "<< duration2.count() << " microseconds" << endl;
		avl_insert<<times<<" "<<duration2.count()<<endl;
		


		// finding minimum in AVL tree
		auto start20 = high_resolution_clock::now();
		struct avlNode *min_avl=retrieveMinAVL(root);
		auto stop20 = high_resolution_clock::now(); 
		auto duration20 = duration_cast<microseconds>(stop20 - start20); 
		//cout << "Time taken by AVL tree to retrieve minimum: "<< duration20.count() << " microseconds" <<" and search results: "<<mymin<< endl;
		avl_rmin<<times<<" "<<duration20.count()<<endl;		

		
		
		// extracting minimum in AVL tree
		auto start21 = high_resolution_clock::now();
		min_avl=retrieveMinAVL(root);
		root = deleteNode(root, min_avl->key);
		auto stop21 = high_resolution_clock::now(); 
		auto duration21 = duration_cast<microseconds>(stop21 - start21); 
		//cout << "Time taken by AVL tree to extract minimum: "<< duration21.count() << " microseconds"<< endl;
		avl_xmin<<times<<" "<<duration21.count()<<endl;		


		// searching for a random number in AVL tree
		auto start22 = high_resolution_clock::now();
		ridx = random(0, times-1);
		sval = arr[ridx];
		struct avlNode *ptr = search_avl(root, sval);
		auto stop22 = high_resolution_clock::now(); 
		auto duration22 = duration_cast<microseconds>(stop22 - start22); 
		//cout << "Time taken by binomial heap to search element "<<sval<<": "<< duration22.count() << " microseconds "<<" and search results: "<<flag<<endl;
		avl_search<<times<<" "<<duration22.count()<<endl;

		// clearing the AVL tree
		clearAVL(root);

		


		/*------------------RB TREE-----------------*/


		// creating RB tree
		RBTree tree;  
		auto start3 = high_resolution_clock::now();
		for(int j=0;j<times;j++) 
			tree.insert(arr[j], -1, NULL);
		auto stop3 = high_resolution_clock::now(); 
		auto duration3 = duration_cast<microseconds>(stop3 - start3); 
		//cout << "Time taken by RB Tree: "<< duration3.count() << " microseconds" << endl;
		rb_insert<<times<<" "<<duration3.count()<<endl;
		

		// finding minimum in RB tree
		auto start30 = high_resolution_clock::now();
		rbNode *min_rb = tree.retrieveMinRB();
		auto stop30 = high_resolution_clock::now(); 
		auto duration30 = duration_cast<microseconds>(stop30 - start30); 
		//cout << "Time taken by AVL tree to retrieve minimum: "<< duration30.count() << " microseconds" <<" and search results: "<<mymin<< endl;
		rb_rmin<<times<<" "<<duration30.count()<<endl;


		// extracting minimum in RB tree
		auto start31 = high_resolution_clock::now();
		min_rb = tree.retrieveMinRB();
		tree.deleteByVal(min_rb->val);
		auto stop31 = high_resolution_clock::now(); 
		auto duration31 = duration_cast<microseconds>(stop31 - start31); 
		//cout << "Time taken by AVL tree to extract minimum: "<< duration31.count() << " microseconds"<< endl;
		rb_xmin<<times<<" "<<duration31.count()<<endl;		


		// searching for a random number in RB tree
		auto start32 = high_resolution_clock::now();
		ridx = random(0, times-1);
		sval = arr[ridx];
		rbNode *obj = tree.search(sval);
		auto stop32 = high_resolution_clock::now(); 
		auto duration32 = duration_cast<microseconds>(stop32 - start32); 
		//cout << "Time taken by binomial heap to search element "<<sval<<": "<< duration32.count() << " microseconds "<<" and search results: "<<flag<<endl;
		rb_search<<times<<" "<<duration32.count()<<endl;


		// clearing the RB tree
		tree.clearRBTree();
	}
	rb_insert.close();
	avl_insert.close();
	binomial_insert.close();
	avl_rmin.close();
 	rb_rmin.close();
 	binomial_rmin.close();
 	avl_xmin.close();
 	rb_xmin.close();
 	binomial_xmin.close();
 	
 	avl_search.close();
 	rb_search.close();
 	binomial_search.close();

}

void prims_using_binomial_heap(int start_node, int N) {
	list<struct node *> heap;
	vector<struct node *> mst(N);
	vector<struct node *> pointer_to_heap(N);
	for(int i=0;i<N;i++) {
		bitmap[i]=false;
		struct node *ptr=(struct node *)malloc(sizeof(struct node));
		if(i!=start_node)
			ptr->minimum=INT_MAX;
		else
			ptr->minimum=0;
		ptr->degree=0;
		ptr->vid=i;
		ptr->child=NULL;
		ptr->neighbour=NULL;
		ptr->parent = NULL;
		ptr->tree_parent=NULL;
		heap.push_front(ptr);
		modify_heap(heap);
		pointer_to_heap[i]=ptr;
	}	

	while(!heap.empty()) {
		struct node * min_vertex=extract_min(heap);
		int vertex = min_vertex->vid;
		bitmap[vertex]=true;
		mst[vertex]=min_vertex;
		for(vector<pair<int, int>>::iterator itr=adj_list[vertex].begin(); itr!=adj_list[vertex].end(); itr++) {
			if(!bitmap[(*itr).first] && (*itr).second < pointer_to_heap[(*itr).first]->minimum) {
				pointer_to_heap[(*itr).first]->minimum = (*itr).second;
				pointer_to_heap[(*itr).first]->parent = min_vertex;
				adjust_tree_on_change(pointer_to_heap[(*itr).first], pointer_to_heap);
			}
		}
	}
	int cost=0;
	for(int i=0;i<N;i++) {
		cost+=mst[i]->minimum;
	}
	cout<<cost<<endl;
}

struct avlNode* custom_insert(struct avlNode* node, int vid, int key, struct avlNode* parent) { 
	
	if (node == NULL) {
		struct avlNode* custom_new_node = (struct avlNode*) malloc(sizeof(struct avlNode)); 
		custom_new_node->key = key; 
		custom_new_node->vid = vid;
		custom_new_node->left = NULL; 
		custom_new_node->right = NULL; 
		custom_new_node->height = 1;
		custom_new_node->parent = parent;
		return custom_new_node;
	} 

	if (key < node->key) 
		node->left = custom_insert(node->left, vid, key, parent); 
	else if (key > node->key) 
		node->right = custom_insert(node->right, vid, key, parent); 
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

struct avlNode *preOrderSearch(struct avlNode *root, int vertex) {
	if(root == NULL)
		return NULL;
	if(root->vid == vertex)
		return root;
	else {
		struct avlNode *t1 = preOrderSearch(root->left, vertex);
		if(t1!=NULL)
			return t1;
		else {
			return preOrderSearch(root->right, vertex);
		}
	}
}

void prims_using_avl(int start_node, int N) {
	struct avlNode *root = NULL;  
	vector<struct avlNode *> mst(N);
	for(int i=0;i<N;i++) {
		bitmap[i]=false;
		if(i==start_node)
			root = custom_insert(root, i, 0, NULL);
		else
			root = custom_insert(root, i, (1254*N)-i, NULL);
	}

	while(root!=NULL) {
		struct avlNode *min_vertex = (struct avlNode *) malloc(sizeof(struct avlNode));
		struct avlNode *mymin = retrieveMinAVL(root);
		min_vertex->vid = mymin->vid;
		min_vertex->parent = mymin->parent;
		min_vertex->key = mymin->key;
		min_vertex->left = NULL;
		min_vertex->right = NULL;
		
		root = deleteNode(root, mymin->key);
		int vertex = min_vertex->vid;
		bitmap[vertex]=true;
		mst[vertex]=min_vertex;
		for(vector<pair<int, int>>::iterator itr=adj_list[vertex].begin(); itr!=adj_list[vertex].end(); itr++) {
			if(!bitmap[(*itr).first]) { 
			 	struct avlNode *pointer = preOrderSearch(root, (*itr).first);
			 	int relaxing_id = pointer->vid;
			 	if((*itr).second < pointer->key) {
					root = deleteNode(root, pointer->key);
					root = custom_insert(root, relaxing_id, (*itr).second, min_vertex);
				}
			}
		}
	}
	int cost=0;
	for(int i=0;i<N;i++) {
		cost+=mst[i]->key;
	}
	cout<<cost<<endl;
}

void prims_using_rb(int start_node, int N) {
	RBTree tree; 	
	vector<rbNode *> mst(N);
	for(int i=0;i<N;i++) {
		bitmap[i]=false;
		if(i==start_node)
			tree.insert(0,i,NULL);
		else
			tree.insert((1254*N)-i,i,NULL);
	}

	cout<<"Outside while"<<endl;
	while(tree.getRoot()!=NULL) {
		
		cout<<"Before"<<endl;
		rbNode *mymin = tree.retrieveMinRB();
		cout<<"Minimum is: "<<mymin->val<<endl;
		rbNode test_obj(mymin->val, mymin->vid, mymin->mst_parent);
		rbNode *min_vertex = &test_obj;
		cout<<"Extracting: "<<mymin->val<<endl;
		tree.deleteByVal(mymin->val);
		cout<<"After extraction: "<<endl;
		tree.printInOrder();
		int vertex = min_vertex->vid;
		bitmap[vertex]=true;
		mst[vertex]=min_vertex;
		for(vector<pair<int, int>>::iterator itr=adj_list[vertex].begin(); itr!=adj_list[vertex].end(); itr++) {
			if(!bitmap[(*itr).first]) { 
			 	rbNode *pointer = tree.AVLpreOrderSearch((*itr).first);
			 	int relaxing_id = pointer->vid;
			 	if((*itr).second < pointer->val) {
			 		cout<<"Relaxing: "<<relaxing_id<<" old_weight: "<<pointer->val<<" new_weight: "<<(*itr).second<<endl;
			 		cout<<"Before deletion traversal: "<<endl;
			 		tree.printInOrder();
					tree.deleteByVal(pointer->val);
					cout<<"After deletion traversal: "<<endl;
					tree.printInOrder();
					tree.insert((*itr).second, relaxing_id, min_vertex);
					cout<<"After insertion traversal: "<<endl;
					tree.printInOrder();
				}
			}
		}
	}
	int cost=0;
	for(int i=0;i<N;i++) {
		cost+=mst[i]->val;
	}
	cout<<cost<<endl;
}

int main() {

	/*
	ifstream numFile;
	numFile.open("random.txt");
    if (!numFile) {
        ofstream myfile;
	  	myfile.open("random.txt");
	  	cout<<"Creating file"<<endl;
		for(int i=0;i<10000000;i++) {
			if(i%1000000==0)
				cout<<i<<endl;
			arr[i]=random(1,10000000);
			myfile<<arr[i]<<endl;
		}
		myfile.close();
		cout<<"Randomly created array!"<<endl; 
    } else {
    	int x, i=0;
    	while (numFile >> x) {
	        arr[i++] = x;
	    }
    }
	
    compare_RB_AVL_BINOMIAL();
	
	*/
	int N;
	cin>>N;
	int E;
	cin>>E;
	adj_list.resize(N);
	bitmap.resize(N);
	for(int i=0;i<E;i++) {
		int v1, v2, w;
		cin>>v1>>v2>>w;
		v1--;
		v2--;
		pair<int, int> f, s;
		f.first=v1;
		f.second=w;
		s.first=v2;
		s.second=w;
		adj_list[v1].push_back(s);
		adj_list[v2].push_back(f);
	}

	int start_node;
	cin>>start_node;
	start_node--;

	//prims_using_binomial_heap(start_node, N);
	
	//prims_using_avl(start_node, N);

	prims_using_rb(start_node, N);
	
	return 0;
}


