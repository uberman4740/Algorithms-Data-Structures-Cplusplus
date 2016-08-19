#include <iostream>

using namespace std;

int findIRe(int a[], int n, int f){

	if(n == 0)
		return -1;
	if(a[0] == f)
		return 0;
	else{
		int temp = findIRe(a + 1, n - 1, f);
		if(temp == -1)
			return -1;
		else
			return temp + 1;
	}	
}

int main(){

	int a[5] = {1, 4, 6, 7, 0};
	cout << findIRe(a, 5, -10) << endl;

	return 0;
}
