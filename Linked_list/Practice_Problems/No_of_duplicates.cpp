#include<iostream>
using namespace std;

int main()
{
    int n,i,j;
    cout << "Enter the number of elements in an array: ";
    cin >> n;

    int arr[n];
    cout << "Enter tha array elmeents: ";
    for(i=0; i<n; i++)
    {
        cin >> arr[i];
    }

    for(i=0; i<n-1; i++)
    {
        if(arr[i] == arr[i+1])
        {
            j= i+1;
            while(arr[i] == arr[j])
             j++;

            printf("%d is appearing %d times\n",arr[i],j-i);
            i = j-1;
        }
    }
    return 0;
}