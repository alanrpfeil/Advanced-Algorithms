#include <iostream>

using namespace std;

void print_matrices(int** s, int i, int j) {
	
	if (i == j) {
		cout << "A" << i-1;
	} else {
		cout << "(";
		print_matrices(s, i, s[i-1][j-1]);
		print_matrices(s, s[i-1][j-1] + 1, j);
		cout << ")";
	}
}

void matrix_chain_order(int dims[], int matnum) {
	int n = matnum; 			//n = dims.size() - 1
	int max_int = 2147483647;	//"infinity"
	int j, q;					//q = number of multiplications
	
	int** m = new int*[n];	   //m[1...n,1...n]
	for (int i = 0; i < n; i++) {
		m[i] = new int[n];
	}
	int** s = new int*[n - 1]; //s[1...n-1][2...n]??
	for (int i = 0; i < n; i++) {
		s[i] = new int[n];
	}
	
	for (int i = 0; i < n; i++) {
		m[i][i] = 0;				//m[i][i] always zero
	}
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			j = i + l - 1;
			m[i-1][j-1] = max_int;
			for (int k = i; k <= j - 1; k++) {
				q = (m[i-1][k-1] + m[k][j-1] + (dims[i-1] * dims[k] * dims[j]));
				if (q < m[i-1][j-1]) {
					m[i-1][j-1] = q;
					s[i-1][j-1] = k;
				}
			}
		}
	}
	//testing...
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "[" << s[j][i] << "]";
		}
		cout << endl;
	}
	*/
	//testing end
	cout << m[0][n-1] << endl;
	print_matrices(s, 1, n);	//print parents(s, i, j);
	
	cout << endl;
	
	for (int i = 0; i < matnum; i++) {
		delete[] m[i];
	}
	delete [] m;
}

int main(int argc, const char * argv[]) {

int matnum;							//no of mats
cin >> matnum;						//n matrices
int* dims = new int[matnum + 1];	//n + 1 dimensions
for (int i = 0; i <= matnum; i++) {	//get dimensions
	cin >> dims[i];
}

matrix_chain_order(dims, matnum);

//clean up://
delete [] dims;

return 0;
}