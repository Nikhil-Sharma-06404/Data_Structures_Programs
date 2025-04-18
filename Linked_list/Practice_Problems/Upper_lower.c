#include<stdio.h>
#include<string.h>
int main()
{
    char S1[20];
    printf("Enter the string: ");
    scanf("%s",S1);

    for(int i=0; S1[i] != '\0'; i++)
    {
     if(S1[i] >= 65 && S1[i] <= 90)
     {
        S1[i] = S1[i] + 32;
     }      
    }

    printf("LOWER CASE STRING IS: %s",S1);
    return 0;
}