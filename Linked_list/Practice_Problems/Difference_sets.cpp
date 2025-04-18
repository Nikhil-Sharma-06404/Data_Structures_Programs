#include <iostream>

using namespace std;

int main()
{
    int i,j,k=0;
   int A[] = {3,5,10,4,6};
   int B[] = {12,4,7,2,5};
   int C[10];
   
   // Difference operation in unsorted array
   for(i=0;i<5; i++)
   {
       int count = 0;
       for(j=0; j<5; j++)
       {
          if(A[i] == B[j])
          {
              count = 1;
          }
       }
       if(count == 0)
       {
           C[k] = A[i];
           k++;
       }
   }
   
   for(i=0; i<k; i++)
   {
       cout << C[i]<<"\t";
   }

    return 0;
}
