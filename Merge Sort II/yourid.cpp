#include <iostream>

using namespace std;

void merge(int list[], int start, int mid, int end) {
	int i = start;
	int j = mid + 1;

	while (j <= end && i <= mid) {
		if (list[i] < list[j]) {
			i++;
		}
		else {
			int temp = list[j];
			for (int k = j; k > i; k--) {
				list[k] = list[k - 1];
			}
			list[i] = temp;

			mid++;
			i++;
			j++;
		}
	}
}


void sort(int list[], int start, int end) {
	if (start < end) {
		long mid = (start + end) / 2;

		sort(list, start, mid);
		sort(list, mid + 1, end);

		merge(list, start, mid, end);
	}
}

int main(int argc, const char * argv[]) {
	unsigned int length;
	cin >> length;
	int* arr = new int[length];
	
	for (int i = 0; i < length; i++) {
		cin >> arr[i];
	}

	sort(arr, 0, length);
	
	for (int i = 0; i < length; i++) {
		cout << arr[i] << ";";
	}
	
}