#include<stdio.h>
#include<string.h>
int main()
{
    int i,j;
    char S1[20], S2[20]; 
    printf("Enter the two strings for concatenation: ");
    scanf("%s %s",S1,S2);
    int len = strlen(S1);

    i=len,j=0;
    while(S2[j] != '\0')
    {
        S1[i] = S2[j];
        i++;
        j++;
    }

    S1[i] = '\0';
    printf("Concatenated string is: ");
    printf("%s",S1);
    return 0;

}