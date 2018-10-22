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
 	//avl_insert.open ("avl_insert.txt");
 	rb_insert.open ("rb_insert.txt");
 	binomial_insert.open("binomial_insert.txt");

 	//avl_rmin.open ("avl_rmin.txt");
 	rb_rmin.open ("rb_rmin.txt");
 	binomial_rmin.open("binomial_rmin.txt");
 	
 	//avl_xmin.open ("avl_xmin.txt");
 	rb_xmin.open ("rb_xmin.txt");
 	binomial_xmin.open("binomial_xmin.txt");
 	
 	//avl_search.open ("avl_search.txt");
 	rb_search.open ("rb_search.txt");
 	binomial_search.open("binomial_search.txt");

	//for(int i=10000;i<10000000;i+=10000) {
		//int times = i;
		int times = 10000;
		
		// creating binomial heap
		list<struct node *> heap;
		cout<<endl<<"For array of size: "<<times<<endl;
		auto start1 = high_resolution_clock::now();
		for(int j=0;j<times;j++) 
			insert_to_heap(heap, arr[j]);
		auto stop1 = high_resolution_clock::now(); 
		auto duration1 = duration_cast<microseconds>(stop1 - start1); 
		cout << "Time taken by binomial heap to build: "<< duration1.count() << " microseconds" << endl;
		//binomial_insert<<times<<" "<<duration1.count()<<endl;
		
		
		// findinging minimum in binomial heap
		auto start10 = high_resolution_clock::now();
		list<struct node *>::iterator itr = retrieve_min(heap);
		int mymin=(*itr)->minimum;
		auto stop10 = high_resolution_clock::now(); 
		auto duration10 = duration_cast<microseconds>(stop10 - start10); 
		cout << "Time taken by binomial heap to retrieve minimum: "<< duration10.count() << " microseconds" <<" and search results: "<<mymin<< endl;
		binomial_rmin<<times<<" "<<duration1.count()<<endl;
		
		// extracting minimum from binomial heap
		auto start11 = high_resolution_clock::now();
		extract_min(heap);
		auto stop11 = high_resolution_clock::now(); 
		auto duration11 = duration_cast<microseconds>(stop11 - start11); 
		cout << "Time taken by binomial heap to extract minimum: "<< duration11.count() << " microseconds" << endl;
		binomial_xmin<<times<<" "<<duration1.count()<<endl;

		// searching for a random number in binomial heap
		auto start12 = high_resolution_clock::now();
		int ridx = random(0, times-1);
		int sval = arr[ridx];
		bool flag = search_binomial(heap, sval);
		auto stop12 = high_resolution_clock::now(); 
		auto duration12 = duration_cast<microseconds>(stop12 - start12); 
		cout << "Time taken by binomial heap to search element "<<sval<<": "<< duration12.count() << " microseconds "<<" and search results: "<<flag<<endl;
		binomial_search<<times<<" "<<duration1.count()<<endl;


		// clearing the binomial heap
		clearBinomial(heap);

		




		struct avlNode *root = NULL;  
		auto start2 = high_resolution_clock::now();
		for(int j=0;j<times;j++) 
			root = insert(root, arr[j]);
		auto stop2 = high_resolution_clock::now(); 
		auto duration2 = duration_cast<microseconds>(stop2 - start2); 
		cout << "Time taken by AVL tree: "<< duration2.count() << " microseconds" << endl;
		//avl_insert<<times<<" "<<duration2.count()<<endl;
		clearAVL(root);

		
		RBTree tree;  
		auto start3 = high_resolution_clock::now();
		for(int j=0;j<times;j++) 
			tree.insert(arr[j]);
		auto stop3 = high_resolution_clock::now(); 
		auto duration3 = duration_cast<microseconds>(stop3 - start3); 
		cout << "Time taken by RB Tree: "<< duration3.count() << " microseconds" << endl;
		//rb_insert<<times<<" "<<duration3.count()<<endl;
		tree.clearRBTree();
	//}
	//rb_insert.close();
	//avl_insert.close();
	//binomial_insert.close();
}

int main() {
	ifstream numFile;
	numFile.open("random.txt");
    if (!numFile) {
        ofstream myfile;
	  	myfile.open ("random.txt");

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


