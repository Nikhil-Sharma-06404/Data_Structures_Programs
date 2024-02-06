#include<iostream>
using namespace std;

int main()
{
  int n,i,diff;
  cout << "Enter the number of elemnts : " ;
  cin >> n;
  int arr[n];
  
  cout<<"Enter elements in sequential manner: ";
  for(i=0; i<n; i++)
  {
    cin >> arr[i];
  }

  int lo=arr[0],hi=arr[n-1];
  diff = lo;
  for(i=0; i<n; i++)
  {
    if(arr[i] - i != diff)
    {
      cout <<" Missing element is: "<<i+diff<<" ";
      break;
    }
  }
  return 0;
}