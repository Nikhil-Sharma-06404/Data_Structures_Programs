#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

 vector<int> kLargest(int arr[], int n, int k)
    {   
        vector<int> ans;
        priority_queue<int, vector<int>, greater<int> > minHeap;
        
        for(int i=0; i<k; i++)
        {
         minHeap.push(arr[i]);    
        }
        
        for(int i=k; i<n; i++)
        {
            if(arr[i] > minHeap.top())
            {
                minHeap.pop();
                minHeap.push(arr[i]);
            }
        }
    for(int i=0; i<k; i++)
    {
        ans.push_back(minHeap.top());
        minHeap.pop();
    }
    return ans;
   } 

int main()
{
int arr[] = {1,23,12,9,30,2,50};
   vector<int> ans = kLargest(arr,7,3);
   for(int i=ans.size() -1 ; i>=0; i--)
     cout<< ans[i] << "\t";
    return 0;
}
