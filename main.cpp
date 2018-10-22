#include "headers.h"
int arr[10000000];

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
		extract_min(heap);
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
			root = insert(root, arr[j]);
		auto stop2 = high_resolution_clock::now(); 
		auto duration2 = duration_cast<microseconds>(stop2 - start2); 
		//cout << "Time taken by AVL tree: "<< duration2.count() << " microseconds" << endl;
		avl_insert<<times<<" "<<duration2.count()<<endl;
		


		// finding minimum in AVL tree
		auto start20 = high_resolution_clock::now();
		mymin=retrieveMinAVL(root);
		auto stop20 = high_resolution_clock::now(); 
		auto duration20 = duration_cast<microseconds>(stop20 - start20); 
		//cout << "Time taken by AVL tree to retrieve minimum: "<< duration20.count() << " microseconds" <<" and search results: "<<mymin<< endl;
		avl_rmin<<times<<" "<<duration20.count()<<endl;		

		
		
		// extracting minimum in AVL tree
		auto start21 = high_resolution_clock::now();
		mymin=retrieveMinAVL(root);
		root = deleteNode(root, mymin);
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
			tree.insert(arr[j]);
		auto stop3 = high_resolution_clock::now(); 
		auto duration3 = duration_cast<microseconds>(stop3 - start3); 
		//cout << "Time taken by RB Tree: "<< duration3.count() << " microseconds" << endl;
		rb_insert<<times<<" "<<duration3.count()<<endl;
		

		// finding minimum in RB tree
		auto start30 = high_resolution_clock::now();
		mymin = tree.retrieveMinRB();
		auto stop30 = high_resolution_clock::now(); 
		auto duration30 = duration_cast<microseconds>(stop30 - start30); 
		//cout << "Time taken by AVL tree to retrieve minimum: "<< duration30.count() << " microseconds" <<" and search results: "<<mymin<< endl;
		rb_rmin<<times<<" "<<duration30.count()<<endl;


		// extracting minimum in RB tree
		auto start31 = high_resolution_clock::now();
		mymin = tree.retrieveMinRB();
		tree.deleteByVal(mymin);
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

int main() {
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

	
	return 0;
}


