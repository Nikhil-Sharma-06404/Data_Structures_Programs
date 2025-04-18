#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,i;
    printf("Enter the size of an array: ");
    cin >> n;

    int arr[n];
    for(i=0; i<n; i++)
    {
        cin >> arr[i];
    }

    int hi = INT_MIN;
    int lo = INT_MAX;

    for(i=0; i<n; i++)
    {
    if(arr[i] > hi)
        hi = arr[i];

    if(arr[i] < lo)
        lo = arr[i];

    }
    int Hash[hi+1] = {0};

    for(i=0; i< n; i++)
    {
        Hash[arr[i]]++;
    }
    
    for(i=lo; i<=hi; i++)
    {
        if(Hash[i] == 0)
         printf("\nMissing elemnts is: %d",i);
    }

    return 0;
}