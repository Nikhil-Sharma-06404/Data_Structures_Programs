#include<iostream>
using namespace std;

int main()
{
    int n,i,last,sum,S;
    printf("Enter the size of an array: ");
    scanf("%d",&n);

    int arr[n];
    cout<<"Enter the natural numbers: ";
    for(i=0; i<n; i++)
      cin >> arr[i];
    
    last = arr[n-1];
    S = (last*(last+1))/2;
     
    for(i=0; i<n; i++)
     sum += arr[i];
    
    cout<<"\nMissing element is: "<<S<<"-"<<sum<<" = "<<S-sum<<" ";

    return 0;
}