#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

template <class X>
void swap(X *a, X *b)
{
	X temp = *a;
	*a = *b;
	*b = temp;
}

template <class T>
void bubble_sort(T arr[], int n)
{
	for (int i = 0; i < n-1; i++){
		for (int j = 0; j < n-i-1; j++){
           if (arr[j] > arr[j+1]){
              swap(&arr[j], &arr[j+1]);
           }
		}
	}
}

int main(int argc, char *argv[])
{
	string s = "abc";
	while(next_permutation(s.begin(), s.end())){
		cout<<s<<endl;
	}
	// bubble_sort(a,3);
	// for(int i=0;i<3;i++){
	// 	cout<<a[i]<<" ";
	// }
	return 0;
}