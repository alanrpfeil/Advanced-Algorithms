#include <iostream>

using namespace std;

int counter = 0;

struct Node {
	int data;
	Node* left;
	Node* right;
	
	Node() {
		data = 0;
		left = NULL;
		right = NULL;
	}
	
	~Node(){
		left = NULL;
		right = NULL;
		data = 0;
	}
	
};

Node* insert(Node* root, int value) {
	if (counter == 0) {
		root->data = value;
		root->left = NULL;
		root->right = NULL;
		counter++;
	} else if (root == NULL) {
		root = new Node();
		root->data = value;
		root->left = NULL;
		root->right = NULL;
	} else {
		if (value < root->data) {
			root->left = insert(root->left, value);
		}
		else {
			root->right = insert(root->right, value);
		}
	}
	return root;
}

void del(Node* root, int value) {
	Node* temp = root;
	Node* parent = temp;
	int count = 0;		//special case counter
	int lastMove = 0;	//control var to help keep track of left/right control
	
	while (temp->data != value) {
		//cout << temp->data << endl;
		parent = temp;
		if (value < temp->data && temp->left != NULL) {
			temp = temp->left;
			lastMove = -1;
			count++;
		}
		else if (value > temp->data && temp->right != NULL) {
			temp = temp->right;
			lastMove = 1;
			count++;
		} else {
			//cout << "hello" << endl;
			return;	//should never be here
		}
	}
	
	if (count == 0) {
		//cout << "hello" << endl;
		//removing head node...
		if (temp->right == NULL && temp->left != NULL){			//left child
			parent = temp;
			temp = temp->left;
			parent->data = temp->data;
			parent->left = temp->left;
			parent->right = temp->right;
			delete temp;
		} else if (temp->left == NULL && temp->right != NULL) {	//right child
			parent = temp;
			temp = temp->right;
			parent->left = temp->left;
			parent->data = temp->data;
			parent->right = temp->right;
			delete temp;
		} else if (temp->right != NULL && temp->left != NULL){	//two children
			parent = temp;
			temp = temp->right;
			parent->data = temp->data;
			parent->right = temp->right;
			delete temp;
		} else {	//leaf
			delete temp;
		}
	}
	
	if (temp->left == NULL && temp->right == NULL) {
		//leaf node; simply delete.
		if (lastMove == -1) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
		delete temp;
		//return;
	} else if (temp->right == NULL && temp->left != NULL) {
		//only left child exists
		Node* leftChild = temp->left;
		if (lastMove == -1) {
			parent->left = leftChild;
		}
		else {
			parent->right = leftChild;
		}
		delete temp;
		//return root;
	} else if (temp->right != NULL && temp->left == NULL) {
		//only right child exists
		Node* rightChild = temp->right;
		if (lastMove == -1) {
			parent->left = rightChild;
		}
		else {
			parent->right = rightChild;
		}
		delete temp;
		//return root;
	} else {
		//Has two children
		
		Node* nextSmallest = temp->right;		//initial movement
		while (nextSmallest->left != NULL) {	//getting to smallest of higher branch
			nextSmallest = nextSmallest->left;
		}

		int dum = nextSmallest->data;			//save value here
		del(root, nextSmallest->data);			//recursion
		temp->data = dum;
		
		//return root;
	}	
}

void outputIO(Node* root) {
	if (root != NULL) {
		outputIO(root->left);
		cout << root->data << endl;
		outputIO(root->right);
	}
}

void outputPO(Node* root) {
	if (root != NULL) {
		outputPO(root->left);
		outputPO(root->right);
		cout << root->data << endl;
	}
}

void outputPR(Node* root) {
	if (root != NULL) {
		cout << root->data << endl;
		outputPR(root->left);
		outputPR(root->right);
	}
}

int main(int argc, const char * argv[]) {
	string input;
	int dum;
	Node* root = new Node();
	
	while (input != "e") {		//exit
	int dum = 0;
		getline(cin, input);

		if (input[0] == 'i' || input[0] == 'd') {	//insert or delete
			if (input[0] == 'i') {
				for (int i = 1; i < input.length(); i++) {
				int imm = ((int)input[i] - 48);	//-48 is ASCII offset for real int value
					if ((input.length() - i )== 3) {
						imm = imm*100;
					} else if ((input.length() - i) == 2) {
						imm = imm*10;
					}
					
					dum += imm;
				}
				root = insert(root, dum);
			} else {
				for (int i = 1; i < input.length(); i++) {
				int imm = ((int)input[i] - 48);	//-48 is ASCII offset for real int value
					if ((input.length() - i )== 3) {
						imm = imm*100;
					} else if ((input.length() - i) == 2) {
						imm = imm*10;
					}
					
					dum += imm;
				}
				del(root, dum);
			}
		}

		else if (input == "opre") {
			outputPR(root);	//preorder
		} else if (input == "opost") {
			outputPO(root);	//post order
		} else if (input == "oin") {
			outputIO(root);	//in order
		}
	}
}