//#I collaborated with Peter Watanabe on this lab
#include <vector>
#include <iostream>

using namespace std;

#define MAX_INTEGER_VALUE 2147483647

class WeightedEdge {
	int u, v, weight;

public:

	void pushWeight(int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->weight = w;
	}

	void setSource(int src) {
		this->u = src;
	}

	void setDest(int dest) {	
		this->v = dest;
	}

	void setWeight(int weight) {
		this->weight = weight;
	}

	int getSource() {
		return this->u;
	}

	int getDest() {	
		return this->v;
	}

	int getWeight() {
		return this->weight;
	}

};

class Graph {

	int vertNum;
	int edgeNum;
	WeightedEdge* edges;
	
public:
	
	Graph(int verts, int numEdges, WeightedEdge* wEdges) {
		vertNum = verts;
		edgeNum = numEdges;
		edges = wEdges;
	}

	/*
	void recursiveDFS(bool seen[], int numVerts, int* arr, int orig, int minID){
		seen[numVerts] = true; 	  	//vertex now seen
		//cout << "ORIG:" << orig << endl;	//debugging
		//cout << "NUMVERTS:" << numVerts << endl;	//debugging
		vector<int>::iterator i; 	//using iterator to navigate container
		
		if (edges[numVerts].empty()) {
			arr[orig] = numVerts;	//if vertex by itself...
		}
		for (i = edges[numVerts].begin(); i != edges[numVerts].end(); i++) {
			//cout << "*i:" << *i << endl;	//debugging
			if (seen[*i] == false) {
				arr[*i] = orig;
				recursiveDFS(seen, *i, arr, orig, minID);
			}
		}
			arr[orig] = orig;

	}
	*/
	/*
	void pushStack(int vertices, deque<int> &stack, bool seen[]) {
		seen[vertices] = true; 
  
		vector<int>::iterator i; 	//using iterator to navigate container
		for(i = edges[vertices].begin(); i != edges[vertices].end(); i++) {
			if(seen[*i] == false) {
				pushStack(*i, stack, seen); 
			}
		}
		stack.push_front(vertices); 
	}
	*/
	/*
	void addEdge(int u, int v, int w) {
		
	}
	*/
	/*
	Graph transpose() {
	
		Graph tGraph(vNum);	//graph w/ same # verts
	
		for (int i = 0; i < vNum; i++) {
			vector<int>::iterator j; 	//using iterator to navigate object container
			for(j = edges[i].begin(); j != edges[i].end(); j++) { 
				tGraph.edges[*j].push_back(i); 	//push back edges in other order
			} 
		} 
    return tGraph; 
	}
	*/
	
	void ShortestDistBF(int sourceNode) {

		int distances[this->vertNum];	//storing distances from sourceNode to node N here

		for (int i = 0; i < this->vertNum; i++) {
			distances[i] = MAX_INTEGER_VALUE;	//in other words, start at infinity (will draw infinity later)
		}

		distances[sourceNode] = 0;	//always zero for itself

		for (int i = 1; i <= this->vertNum - 1; i++) {
			for (int j = 0; j < this->edgeNum; j++) {
				//getting connection instance...
				int u = edges[j].getSource();
				int v = edges[j].getDest();
				int w = edges[j].getWeight();

				if (distances[u] != MAX_INTEGER_VALUE && distances[u] + w < distances[v]) {
					distances[v] = distances[u] + w;
				}
			}
		}

		for (int i = 0; i < this->edgeNum; i++) {
			//getting connection instance to test for negative-weight cycles...
			int u = edges[i].getSource();
			int v = edges[i].getDest();
			int w = edges[i].getWeight();
			if (distances[u] != MAX_INTEGER_VALUE && distances[u] + w < distances[v]) {
            	printFalse();
            	return;
       		}
		}
		printDist(distances, vertNum);
	}

	void printFalse(){
		cout << "FALSE" << endl;
	}

	void printDist(int* distances, int n) {	//n = length of distances array
		cout << "TRUE" << endl;
		for (int i = 0; i < n; i++) {
			if (distances[i] == MAX_INTEGER_VALUE) {
				cout << "INFINITY" << endl;
				continue;
			}
			cout << distances[i] << endl;
		}
	}

};


int main(int argc, const char * argv[]) {
	int numVerts, numEdges, v, u, w;

	cin >> numVerts >> numEdges;

	WeightedEdge edges[numEdges];

	for (int i = 0; i < numEdges; i++) {
		cin >> u >> v >> w;

		edges[i].setSource(u);
		edges[i].setDest(v);
		edges[i].setWeight(w);
	}
	
	Graph myGraph = Graph(numVerts, numEdges, edges);

	myGraph.ShortestDistBF(edges[0].getSource());

	//delete myGraph;
		
}