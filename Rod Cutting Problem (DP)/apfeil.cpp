#include <iostream>

using namespace std;

int Max(int a, int b) { return (a > b) ? a : b;}

int EXT_cutrod(int prices[], unsigned int size, int lengths[], int revenue[]) {
	if (size <= 0) {
		return 0;
	}
	revenue[0] = 0;

	for (int j = 1; j <= size; j++) {
		int max = -2147483647;	//INT_MIN
		for (int i = 0; i < j; i++) {
			if (max < (prices[i] + revenue[j - i - 1])) {
				max = (prices[i] + revenue[j - i - 1]);
				lengths[j] = i + 1;
			}
		}
		revenue[j] = max;	//max revenue in table
	}

	int max = -2147483647;	//getting max revenue...
	for (int i = 1; i < size; i++) {
		if (max < revenue[i]) {
			max = revenue[i];
		}
	}

	return revenue[size];	//max revenue returned
}

void print(int prices[], unsigned int size, int lengths[], int revenue[]) {
	int rodlen;
	int max_rev = EXT_cutrod(prices, size, lengths, revenue);
	int maxRevenue = max_rev;
	
	cout << max_rev << endl;
	
	/*
	for (int i = 0; i <= size; i++) {
		cout << revenue[i] << " ";
	}
	cout << endl;
	for (int i = 0; i <= size; i++) {
		cout << lengths[i] << " ";
	}
	cout << endl;
	*/

	rodlen = size;

	for (int i = 0; i <= size; i++) {	//printing lengths used
		if (max_rev == revenue[i]) {
			while (rodlen > 0) {
				cout << lengths[i] << " ";
				rodlen -= lengths[i];
				i = rodlen;
			}
		}
	}
	
	cout << "-1" << endl;	//end
}

int main(int argc, const char * argv[]) {

	unsigned int size;
	cin >> size;
	int* prices = new int[size];
	int* lengths = new int[size];
	int* revenue = new int[size + 1];

	for (int i = 0; i < size; i++) {
		cin >> prices[i];
	}

	print(prices, size, lengths, revenue);

	delete[] prices, lengths;

	return 0;
}