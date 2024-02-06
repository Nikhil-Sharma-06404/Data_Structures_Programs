#include<iostream>
using namespace std;

int main()

{
    int i,n;
    cout << "Enter the size of an array: ";
    cin >> n;
   
    int arr[n];
    cout << "Enter the array elements:";
    for(i-0;i<n; i++)
    {
        cin >> arr[i];
    }

    int lo=arr[0];
    int hi=arr[n-1],diff=lo-0;

    for(i=0; i<n; i++)
    {
        if(arr[i] - i != diff)
        {
            while(diff < arr[i] - i)
            {
                cout << "Missing element is: "<<i+diff<<"\n";
                diff++;
            }
        }
    }
    return 0;
}