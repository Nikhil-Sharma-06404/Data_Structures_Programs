#include <stdio.h>
#include <string.h>

int main()
{
    char str[50];
    printf("Enter string: ");
    gets(str);
    
    int start_idx, last_idx,len;
    len = strlen(str);
    last_idx = strlen(str) - 1;
    
    int i=len-1;
    while(i >= 0)
    {
        if(i == 0 || str[i] == ' ')
        {
            if(i==0)
            {
                start_idx = 0;
            }
            else
            {
                start_idx = i+1;
            }
        
        for(int j=start_idx; j<=last_idx; j++)
        {
            printf("%c",str[j]);
        }
        last_idx = i - 1;
        printf(" ");
        }
        i--;
    }

    return 0;
}
