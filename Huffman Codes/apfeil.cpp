//#I collaborated with Peter Watanabe
#include <iostream>
#include <string.h>
#include <array>

using namespace std;

int A[6], B[6], C[6], D[6], E[6], F[6];	//dynamic bit compression code stored in these arrays
int ctr;	//control global var to aid in print function

int bitLen[6];	//ended up needing to get bit length for each compression char; more simple

//Using min heap (max heap with different conditions); need Node object for max/min heaps
struct Node{
	
	char chr;
	unsigned int freq;	//how many times character appears in text sample
	struct Node* right;
	struct Node* left;
	
	Node() {
		//default constructor - null node
		this->chr = ' ';
		this->freq = 0;
		this->right = NULL;
		this->left = NULL;
	}
	
	Node(char chr, int freq) {
		//constructor
		this->chr = chr;
		this->freq = freq;
		this->right = NULL;
		this->left = NULL;
	}
};

	
//helper function; different from std::swap which just swaps values
void swap(struct Node** n1, Node** n2){
	struct Node* temp = *n1;
	*n1 = *n2;
	*n2 = temp;	//swapped
}

//min heap struct using Node
struct min_heap{

	int size;
	int capacity;
	struct Node** arr;
	
	min_heap(int cap){
	//constructor; ZERO min_heap + capacity arg
		this->size = 0;
		this->capacity = cap;
		this->arr = (struct Node**)malloc(cap * sizeof(struct Node*)); 
	}
	
	min_heap(int cap, int size){
	//constructor; ZERO min_heap + capacity arg + size arg
		this->size = size;
		this->capacity = cap;
		this->arr = (struct Node**)malloc(cap * sizeof(struct Node*)); 
	}
	
	struct Node* get_min(){
		struct Node* temp = this->arr[0];	//get pointer node to head to grab min node
		this->arr[0] = this->arr[this->size - 1];	//head node freq = last leaf node freq (min)
		this->size = this->size - 1; //popped minimum node
		min_heapify(0);	 //make min heap again
		
		return temp;
	}
	
	void min_heapify(int node_id){
		int less = node_id;	//to get left child since lesser freq is left child
		int left = 2*node_id+1;	//left child is 2 * i + 1 in arr
		int right = 2*node_id+2;//left child is 2 * i + 2 in arr
		if (left < this->size && this->arr[left]->freq < this->arr[less]->freq) {
			less = left;
		}
		if (right < this->size && this->arr[right]->freq < this->arr[less]->freq){
			less = right;
		}
		if (less != node_id) {
			swap(&this->arr[less], &this->arr[node_id]);
			min_heapify(less);
		}
	}
	
	void build_min_heap() {
		int i;
		for (i = ((this->size - 2) / 2); i >= 0; i--) {
			this->min_heapify(i);	//recursion like max heap
		}
	}

};

void insertMinHeap(struct min_heap* minHeap, struct Node* node) {	//kept outside min_heap object
	minHeap->size += 1;
	int n = minHeap->size-1;
	while (node->freq < minHeap->arr[(n-1)/2]->freq && n) {	//while this freq less than parent's freq... continue to left/right child...
	minHeap->arr[n] = minHeap->arr[(n-1)/2];	//transition to parent
	n = ((n-1)/2);
	}
	minHeap->arr[n] = node;	//new node placed in correct index
}

struct min_heap* new_min_heap(char* chr, int* freq, int size) {	//goes to method
		struct min_heap* minHeap = new min_heap(size);
		
		for (int i = 0; i < size; i++) {
			minHeap->arr[i] = new Node(chr[i], freq[i]);
		}
		minHeap->size = size;
		minHeap->build_min_heap();	//method
		return minHeap;
}

//condition check helper function
int isLeaf(struct Node* head) {
	return !(head->left) && !(head->right);
}

struct Node* makeCompTree(char* chr, int* freq, int size) {
	struct Node* left;
	struct Node* right;
	struct Node* top;
	struct min_heap* minHeap = new_min_heap(chr, freq, size);
	while (!(minHeap->size == 1)) {
		left = minHeap->get_min();
		right = minHeap->get_min();
		top = new Node('$', left->freq + right->freq);	//args = char chr, int freq in constructor
		top->left = left;
		top->right = right;
		
		insertMinHeap(minHeap, top);
	}
	return minHeap->get_min();
}

void printOutput(){
	//Printing dynamic bit compression codes; char corresponds to chr Node
	
	//A:XXXXX
	cout << "A:";
	for (int i = 0; i < bitLen[0]; i++) {	//bitLen[0->5] corresponds to A->F
		//if(A[i] != 0 && A[i] != 1) {
		//	break;
		//}
	cout << A[i];
	}
	cout << endl;
	
	//B:XXXXX
	cout << "B:";
	for (int i = 0; i < bitLen[1]; i++) {cout << B[i];}	//bitLen[0->5] corresponds to A->F
	cout << endl;
	
	//C:XXXXX
	cout << "C:";
	for (int i = 0; i < bitLen[2]; i++) {cout << C[i];}	//bitLen[0->5] corresponds to A->F
	cout << endl;
	
	//D:XXXXX
	cout << "D:";
	for (int i = 0; i < bitLen[3]; i++) {cout << D[i];}	//bitLen[0->5] corresponds to A->F
	cout << endl;
	
	//E:XXXXX
	cout << "E:";
	for (int i = 0; i < bitLen[4]; i++) {cout << E[i];}	//bitLen[0->5] corresponds to A->F
	cout << endl;
	
	//F:XXXXX
	cout << "F:";
	for (int i = 0; i < (bitLen[5]); i++) {cout << F[i];}	//bitLen[0->5] corresponds to A->F
	cout << endl;
}

void print(struct Node* head, int* arr, int top) {
	if (head->left) {
		arr[top] = 0;
		print(head->left, arr, top + 1);	//recursive call to print for left children
	}
	if (head->right) {
		arr[top] = 1;
		print(head->right, arr, top + 1);	//recursive call to print for right children
	}

	if (isLeaf(head)) {	//if at bottom of tree
		if (head->chr == 'A') {		//if A, print A's bit compression code
			memcpy(A, arr, sizeof(A));
			ctr++;
			bitLen[0] = top;
		}
		else if (head->chr == 'B') {	//if B, print B's bit compression code
			memcpy(B, arr, sizeof(B));
			ctr++;
			bitLen[1] = top;
		}
		else if (head->chr == 'C') {	//if C, print C's bit compression code
			memcpy(C, arr, sizeof(C));
			ctr++;
			bitLen[2] = top;
		}
		else if (head->chr == 'D') {	//if D, print D's bit compression code
			memcpy(D, arr, sizeof(D));
			ctr++;
			bitLen[3] = top;
		}
		else if (head->chr == 'E') {	//if E, print E's bit compression code
			memcpy(E, arr, sizeof(E));
			ctr++;
			bitLen[4] = top;
		}
		else if (head->chr == 'F') {	//if F, print F's bit compression code
			memcpy(F, arr, sizeof(F));
			ctr++;
			bitLen[5] = top;
		}
		//we've printed all of the character's bit compression codes
		if (ctr == 6) {	printOutput();}
	}
}

void huffman(char* chr, int* freq, int size) {	//function that starts/inits huffman code to make compression tree
	struct Node* head = makeCompTree(chr, freq, size);
	int arr[6];
	int top = 0;
	print(head, arr, top);
}

int main(int argc, const char * argv[]) {
	char arr[] = {'A','B','C','D','E','F'};
	int freq[6];	//get 6 frequencies for the 6 chars above; always A->F in this lab/case
	for (int i = 0; i < (sizeof(freq)/sizeof(int)); i++) {
		cin >> freq[i];
	}
	huffman(arr, freq, 6);	//create min_heap using first head node to make compresssion tree
		//cout << "testing..." << endl;
	//print();
	//printOutput();
	return 1;
}

