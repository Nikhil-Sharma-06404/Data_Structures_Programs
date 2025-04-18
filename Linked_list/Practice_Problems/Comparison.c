#include<stdio.h>
#include<string.h>
int main()
{
    char S1[20],S2[20];
    scanf("%s %s",S1,S2);

    int i=0;
    while(S1[i] == S2[i])
    {
      if(S1[i] == '\0' && S2[i] == '\0')
      {
        break;
      }
        i++;
    }
    if(S1[i] == '\0' && S2[i] == '\0')
    {
        printf("Strings are equal.");
    }
    else
    {
        printf("Strings are not equal.");
    }
    return 0;
}