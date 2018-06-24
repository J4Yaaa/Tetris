#include <stdio.h>

int main()
{
    int i = 0;
    int j = 0;
    for(i = 1; i <= 9; ++i)
    {
        printf("\033[3%dm",i%8);
        for(j = 1; j <= i; ++j)
        {
            printf("%d*%d=%-3d",j,i,i*j);
        }
        printf("\033[0m\n");
    }
    return 0;
}
