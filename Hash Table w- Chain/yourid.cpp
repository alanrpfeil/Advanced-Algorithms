#include <iostream>
#include <string>

using namespace std;

struct node {

	node* next = NULL;
	int data;
	node* prev = NULL;

};

void insert(int key, int size, node** arr) {

	node* pivot;
	node* insert = new node;
	insert->data = key;

	if (arr[key % size] != NULL) {		//when it's NOT empty
		pivot = arr[key % size];
		insert->next = pivot;
		arr[key % size] = insert;
		pivot->prev = insert;
	}
	else {								//when empty
		insert->prev = NULL;
		arr[key % size] = insert;
	}
}

void search(int key, int size, node** arr) {

	node* temp;
	temp = arr[key % size];
	int LLindex = 0;

	if (arr[key % size] == NULL) {
		cout << key << ":NOT_FOUND;" << endl;
		return;
	}

	while (temp->next != NULL) {
		if (temp->data == key) {
			cout << key << ":FOUND_AT" << key%size << "," << LLindex << ";" << endl;
			return;
		}
		temp = temp->next;
		LLindex++;
	}

	if (temp->data == key) {
		cout << key << ":FOUND_AT" << key%size << "," << LLindex << ";" << endl;
	}
	else {
		cout << key << ":NOT_FOUND;" << endl;
	}

}

void del(int key, int size, node** arr) {

	node* nextNode;
	node* previous;
	node* temp;
	temp = arr[key % size];


	if (temp == NULL) {
		cout << key << ":DELETE_FAILED;" << endl;
		return;
	}

	while (temp->next != NULL) {		//node(s) before and after
		if (temp->data == key) {
			if (temp->prev != NULL) {
				previous = temp->prev;
			}
			nextNode = temp->next;
			temp->next = nextNode->next;
			temp->prev = previous;
			temp->data = nextNode->data;
			cout << key << ":DELETED;" << endl;
			free(nextNode);
			return;
		}
		else {
			temp = temp->next;
		}
	}

	if (temp->data == key) {	//last node or one node here
		temp->prev->next = NULL;
		cout << key << ":DELETED;" << endl;
	}
	else {
		cout << key << ":DELETE_FAILED;" << endl;
	}

}

void const printHash(int size, node** arr) {
	node* temp;

	for (int i = 0; i < size; i++) {
		temp = arr[i];

		cout << i << ":";

		if (arr[i] == NULL) {
			cout << ";" << endl;
			continue;
		}

		while (temp->next != NULL) {		
			cout << temp->data << "->";
			temp = temp->next;
		}
		cout << temp->data << "->" << ";" << endl;	//@ last node
	}
}

int get_num(int tensPlace, int onesPlace) {
	int num = 0;
	int tens;
	int ones;

	tens = tensPlace - '0';	//getting tens place
	ones = onesPlace - '0';	//getting ones place

	for (int i = 0; i < tens; i++) {
		num += 10;
	}
	for (int j = 0; j < ones; j++) {
		num += 1;
	}

	return num;
}

int main(int argc, const char * argv[]) {
	unsigned int size;
	string input;
	int dum;

	cin >> size;

	node** arr;
	arr = (node**)malloc(sizeof(node*) * size);

	for (int i = 0; i < size; i++) {
		arr[i] = NULL;
	}

	while (input != "e") {		//user input section:

		getline(cin, input);


		if (input[2] != 0) {
			dum = get_num(input[1], input[2]);
		}
		else {
			dum = input[1] - '0';
		}


		if (input[0] == 'i') {
			insert(dum, size, arr);
		}

		else if (input[0] == 'd') {
			del(dum, size, arr);
		}

		else if (input[0] == 's') {
			search(dum, size, arr);
		}

		else if (input[0] == 'o') {
			printHash(size, arr);
		}

	}
}