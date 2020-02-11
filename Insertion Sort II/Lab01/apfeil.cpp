

#include <iostream>
using namespace std;

void insertionSort(int num[], int length) {
	int cnt = 0;

	for (int i = 0; i < length; i++) {
		int j = i;
		while (j > 0 && num[j - 1] > num[j]) {

			int temp = num[j - 1];
			num[j - 1] = num[j];
			num[j] = temp;

			j = j - 1;
		}
		cnt++;
		if (cnt != 1) {
			for (int k = 0; k < cnt; k++) {
				cout << num[k] << ";";
			}
			cout << endl;
		}
	}
}

int main(int argc, char **argv) {

	int size = 0;
	cin >> size;

	int* num = new int[size];

	for (int i = 0; i < size; i++) {
		cin >> num[i];
	}

	insertionSort(num, size);

	delete num;
}

