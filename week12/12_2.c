#include<iostream>
#include<conio.h>
using namespace std;
int *findMax(int arr[],int n);
int main(){   
   int n,i,*p;    
  cout<<"Nhap so du lieu: ";    
  cin>>n;    
  int arr[n];        
  for(i=0;i<n;i++)     {      
    cout<<"Nhap gia tri thu "<<i+1<<" la :";      
   cin>>arr[i];            
}          
  p=findMax(arr,n);    
  cout<<"Gia tri lon nhat la: "<<*p;    
  getch();    
  return 0;
}   
int *findMax(int data[],int n){    
  int *max=data;    
  int i;   
 for(i=1;i<n;i++){           
   if(*max<*(max+i)) *max=*(max+i);                              
  }    
  return max;
    
}