#include<iostream>
using namespace std;

int main()
{
  int arr[][3] = {{1,2},{3,4,5},{5}};
  printf("%d %d %d",sizeof(arr),arr[0][2],arr[1][2]);
  return 0;
}