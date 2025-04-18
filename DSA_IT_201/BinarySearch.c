#include<stdio.h>

int main()
{
    int n,target,flag=0;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the array elements in sorted order: ");
    for(int i=0; i<n; i++)
     scanf("%d",&arr[i]);

    printf("Enter the element you want to search: ");
    scanf("%d",&target);
    
    int s=0,e=n-1;
    int mid = (s + (e-s)/2);
    while(s <= e)
    {
      if(arr[mid] == target)
      {
        printf("Element %d is found at index %d",target,mid);
        flag=1;
        break;
      }
      else if(arr[mid] < target)
        s = mid+1;
      else
        e = mid-1;
    
    mid = (s+(e-s)/2); // updating mid again
    }
    
    if(flag == 0)
     printf("Element is not found !");
    return 0;
}