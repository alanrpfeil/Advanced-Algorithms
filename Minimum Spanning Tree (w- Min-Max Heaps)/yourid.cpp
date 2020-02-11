//#I collaborated with Peter Watanabe on this lab, lab 12
#include <list>
#include <vector>
#include <iostream>
using namespace std;

#define INFINITY 2147483647

class WeightedEdge {
public:
	int source;
	int dest;
	int weight;
};

 
class Graph {
public:
	int vertNum;

    Graph(int vertices) {
		this->vertNum = vertices;
	}
	
	void addEdge(int u, int v, int weight, int** weights) {
		weights[u][v] = weight;
		weights[v][u] = weight;
	}
	
};


int smallestKey(int vertices, int* keys, bool* valid) {
	int minAt;
	int min = INFINITY;	//starting at infinity to ensure any initial case is min
	
	for (int i = 0; i < vertices; i++) {
		if (valid[i] == true && keys[i] < min) {
			min = keys[i];
			minAt = i;
		}
	}
	
	return minAt;     //returning index of min
}

void primsMinSpanTree(int vertices, int** weights) {
	int parents[vertices];	//parent array
	int keys[vertices];		//key array
	bool valid[vertices];	//control array
	
	for (int i = 0; i < vertices; i++) {	//initiating to base condition
		keys[i] = INFINITY;
		valid[i] = true;
	}
	
	keys[0] = 0;	//root will always have these conditions:
	parents[0] = 0;	//^^^
	
	for (int j = 0; j < vertices - 1; j++) {
		int u = smallestKey(vertices, keys, valid);
		valid[u] = false;
			
		//cout << "hello" << endl; //debugging...
			
		for (int k = 0; k < vertices; k++) {
		//cout << j << " " << k << " " << endl; //debugging...
			if (weights[u][k] != 0 && weights[u][k] < keys[k] && valid[k] == true) {
				parents[k] = u;
				keys[k] = weights[u][k];
			}
		}
	}     
	     
	for (int i = 1; i < vertices; i++) {	//starting at 1 because itself isn't a parent
		cout << parents[i] << endl;
	}
}
 
int main(int argc, const char * argv[]) {
	int vertNum;	//# vertices
	int edgeNum;	//# edges
	
	cin >> vertNum >> edgeNum;
	            
	WeightedEdge* edges = new WeightedEdge[edgeNum];
	int** weights = new int*[vertNum];   //holds weight of connection of vertices: [u][v]
	
	for (int i = 0; i < vertNum; i++) {
		weights[i] = new int[vertNum];
	}
	
	Graph myGraph(vertNum);
	
	for (int i = 0; i < edgeNum; i++) {	//constructing graph w/ weighted edges
		cin >> edges[i].source;	//u
		cin >> edges[i].dest;	//v
		cin >> edges[i].weight;	//w
		myGraph.addEdge(edges[i].source, edges[i].dest, edges[i].weight, weights);
	}
     
	primsMinSpanTree(vertNum, weights);
          
	return 1;
}