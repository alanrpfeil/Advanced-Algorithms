#include <iostream>

using namespace std;

	int find_max_crossing_subarray(int* arr, int low, int mid, int high){
		int leftsum = -2147483647;
		int sum = 0;
		for (int i = mid; i >= low; i--) {
			sum = sum + arr[i];
			if (sum > leftsum) {
				leftsum = sum;
			}
		}
		
		int rightsum = -2147483647;
		sum = 0;
		for (int i = mid + 1; i <= high; i++) {
			sum = sum + arr[i];
			if (sum > rightsum) {
				rightsum = sum;
			}
		}
		return (leftsum + rightsum);
	}

	int find_max_subarray(int* arr, int low, int high){
		int mid, leftsum, rightsum, cross_sum;
		if (high == low) {
			return arr[0]; 	//base case; only one element in arr
		}
		else {
			mid = (high + low) / 2;
			
			leftsum = find_max_subarray(arr, low, mid);
			rightsum = find_max_subarray(arr, mid + 1, high);
			cross_sum = find_max_crossing_subarray(arr, low, mid, high);
			
			if (leftsum >= rightsum && leftsum >= cross_sum) {
				return leftsum;
			}
			else if (rightsum >= leftsum && rightsum >= cross_sum) {
				return rightsum;
			}
			else {
				return cross_sum;
			}
		}
	}
	
int main (int argc, const char * argv[]) {
	unsigned int length;
	int maxsubarray;
	cin >> length;
	int* arr = new int[length];
	
	for (int i = 0; i < length; i++) {
		cin >> arr[i];
	}
	
	maxsubarray = find_max_subarray(arr, 0, length - 1);
	cout << maxsubarray;
	
	return -1;
}