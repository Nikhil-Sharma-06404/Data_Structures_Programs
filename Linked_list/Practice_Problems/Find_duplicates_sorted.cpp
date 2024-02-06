#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,i;
    printf("Enter the number of elements: ");
    cin >> n;
              
    int arr[n];
    cout << "Enter the array elements: ";
    for(i=0; i<n; i++)
    {
        cin >> arr[i];
    }
    
    int last_duplicate = 0;
    for(i=0; i<n; i++)
    {  
        while(arr[i] == arr[i+1] && last_duplicate != arr[i])
        {
            printf("\n Duplicate element is: %d",arr[i]);
            last_duplicate = arr[i];
        }
    } 
    return 0;
}