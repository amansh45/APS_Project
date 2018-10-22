#include <iostream>

using namespace std;

struct node {
	int vertex;
	struct node *next;
	
}

int main() {
	int N;
	cin>>N;
	int E;
	cin>>E;
	int adj_mat[N][N];
	vector<vector<struct node *>> adj_list(N);
	for(int i=0;i<E;i++) {
		int v1, v2;
		cin>>v1>>v2;
		adj_list[v1].
	}
	return 0;
}
