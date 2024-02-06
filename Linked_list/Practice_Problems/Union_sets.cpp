#include<iostream>
using namespace std;

int main()
{
    int i,j,k=0;
    int A[] = {3,5,10,4,6};
    int B[] = {12,4,7,2,5};
    int C[10];
    
    i=0,j=0;
    while(i<5 && j<5)
    {
            if(A[i] < B[j])
            {
                i++;
            }
            else if(A[i] > B[j])
           {
                j++;
           }
            else if(A[i] == B[j])
            {
             C[k++] = A[i++];
             j++;
            }
    }

     for(i=0; i<k; i++)
     {
        cout << C[k]<<" ";
     }

    return 0;
}