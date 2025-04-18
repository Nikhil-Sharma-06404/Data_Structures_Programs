#include<stdio.h>

int main()
{
    int n,target,flag=0;
    printf("Enter the size of array: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the array elements: ");
    for(int i=0; i<n; i++)
     scanf("%d",&arr[i]);

    printf("Enter the element you want to search: ");
    scanf("%d",&target);