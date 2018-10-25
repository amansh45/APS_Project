#include <iostream>

using namespace std;

struct graph_node {
	int vertex;
	struct node *parent;
	int weight;
}

int main() {
	int N;
	cin>>N;
	int E;
	cin>>E;
	int adj_mat[N][N];
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			adj_mat[i][j]=-1;
	
	vector<vector<pair<int, int>>> adj_list(N);
	
	for(int i=0;i<E;i++) {
		int v1, v2, w;
		cin>>v1>>v2>>w;
		pair<int, int> f, s;
		f.first=v1;
		f.second=s.second=w;
		s.first=v2;
		adj_list[v1].push_back(s);
		adj_list[v2].push_back(f);
		adj_mat[v1][v2]=w;
	}

	return 0;
}
