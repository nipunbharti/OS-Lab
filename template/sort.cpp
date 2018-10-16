#include <iostream>
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
	char a[3] = {'a','c','b'};
	bubble_sort(a,3);
	for(int i=0;i<3;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}