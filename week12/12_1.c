#include <iostream>
using namespace std;
#define MAX 1000
void nhapMang(int arr[], int &n);
void xuatMang(int arr[], int n);

int main()
{
	int myArray[MAX]; 
	int nSize; 
	nhapMang(myArray, nSize);
	xuatMang(myArray, nSize);

	return 0;
}

void nhapMang(int arr[], int &n)
{
	cout << "Nhap so luong phan tu n : ";
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
}

void xuatMang(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] % 2 == 0)
{
			cout << "arr[" << i << "] = " << arr[i] << endl;
}
	}
}