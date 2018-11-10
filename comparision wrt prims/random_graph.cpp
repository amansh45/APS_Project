#include<bits/stdc++.h> 
using namespace std; 
#define RUN 1 
#define MAX_VERTICES 10

vector<vector<pair<int, int>>> adj_list;
vector<bool> bitmap;

int random(int srange, int erange) {
	random_device rd;
	mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(srange,erange);
	return dist(mt);
}

int main() { 

	int V = random(7, MAX_VERTICES);
	int max_edges = (V*(V-1))/2;
	int E = random(V, max_edges);
	vector <int> vertices(V);
	vector<int> isConnected;

	cout<<"Number of vertices is: "<<V<<endl;
	cout<<"Number of edges is: "<<E<<endl;

	for(int i=0;i<V;i++)
		vertices[i] = i;

	for(int i=0;i<V;i++)
		isConnected.push_back(i);

	int svertex_index = random(0, V-1);
	int start_vertex = isConnected[svertex_index];
	isConnected.erase(isConnected.begin()+svertex_index);

	vector <pair<int, int>> edges; 

	int q=0;
	while(q<V-1) {
		int next_vertex = random(0,isConnected.size()-1);
		pair<int, int> p;
		p.first = start_vertex;
		p.second = isConnected[next_vertex];

		bool check_flag = true;
		int edges_filled = edges.size();
		for(int i=0;i<edges_filled;i++) {
			if(edges[i].first == p.first && edges[i].second == p.second) {
				check_flag = false;
				break;
			}
		}
		if(check_flag) {
			edges.push_back(p);
			start_vertex = isConnected[next_vertex];
			isConnected.erase(isConnected.begin()+next_vertex);
			q++;
		}
	}

	int remaining_edges = E-(V-1);

	for(int i=0;i<remaining_edges;i++) {
		int a = random(0, vertices.size()-1);
		int b = random(0, vertices.size()-1);
		while(b==a) {
			b = random(0, vertices.size()-1);
		}
		pair<int, int> x;
		x.first = a;
		x.second = b;
		edges.push_back(x);
	}

	cout<<"Graph created successfully"<<endl;

	cout<<"Adding weights randomly"<<endl;

	int max_weight = 3*E;
	set<int> weights;
	adj_list.resize(V);
	bitmap.resize(V);
	for(int i=0;i<E;i++) {
		int rand_weight = random(1,max_weight);
		while(weights.find(rand_weight) != weights.end())
			rand_weight = random(1, max_weight);
		pair<int, int> f, s;
		f.first = edges[i].first;
		f.second = rand_weight;
		s.first = edges[i].second;
		s.second = rand_weight;
		adj_list[edges[i].first].push_back(s);
		adj_list[edges[i].second].push_back(f);
	}

	for(int i=0;i<V;i++) {
		cout<<i<<"==> ";
		for(auto itr = adj_list[i].begin(); itr!=adj_list[i].end();itr++) {
			cout<<"("<<(*itr).first<<", "<<(*itr).second<<")";
		}
		cout<<endl;
	}

	int start_node = random(0,V-1);
	return 0;
} 
