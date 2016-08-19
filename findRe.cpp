#include <iostream>

using namespace std;

bool findRe(int a[], int n, int f){

	if(n == 0)
		return false;
	if(a[0] == f)
		return true;
	else
		return findRe(a + 1, n - 1, f);	
}

int main(){

	int a[5] = {1, 4, 6, 7, 0};
	cout << findRe(a, 5, 4) << endl;

	return 0;
}
