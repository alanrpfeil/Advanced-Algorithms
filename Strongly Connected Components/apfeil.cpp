#include <iostream>
#include <deque>
#include <vector>

using namespace std;

vector<int> sccIDs;

class Graph {

	int vNum;
	vector<int>* edges;
	
public:
	
	Graph(int verts) {
		vNum = verts;
		edges = new vector<int>[vNum];
	}

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
	
	void addEdge(int u, int v) {
		edges[v].push_back(u);	//adds node u to v's node to create an 'edge' of sorts
	}
	
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

	void print(int vertNum) {
		int* arr = new int[vertNum];		//vertex array for final print; SCC ID should be in each element for a vertex
		
		deque<int> stack;					//deque is a stack as long as I push/pop from front.
		bool* seen = new bool[vNum];
		
		for (int i = 0; i < vNum; i++) {
			seen[i] = false;				//set all initially to "unseen"
		}
		
		for (int j = 0; j < vNum; j++) {
			if (seen[j] == false) {			//push all into stack to start DFS
				pushStack(j, stack, seen);
			}
		}
		//now transpose to get SCC's
		Graph transposedGraph = transpose();
		
		for (int i = 0; i < vNum; i++) {
			seen[i] = false;				//set all to "unseen" again
		}
		
		while (stack.empty() == false) {	//as long as stack has something in it...
			int v1 = stack.front();
			stack.pop_front();
			
			if(seen[v1] == false) {
				transposedGraph.recursiveDFS(seen, v1, arr, v1, v1);
				//cout << endl;
			}
		
		}
		
		for (int i = 0; i < vertNum; i++) {	//final print
			cout << arr[i] << endl;
		}
		
	}
	
};

int main(int argc, const char * argv[]) {
	unsigned int edgeNum, vertNum, v1, v2;

	cin >> vertNum >> edgeNum;

	Graph map(vertNum);
	
	for (int i = 0; i < edgeNum; i++) {
		cin >> v1 >> v2;
		map.addEdge(v1, v2);	//adding v1 and v2 as "adjacent" in graph; drawing edge
	}

	map.print(vertNum);
	
	return 1;
}