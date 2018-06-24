#include "tetris.h"

void PrintArr()
{
    int i = 0;
    int j = 0;
    for(i = 0; i < HIGH; ++i)
    {
        char arr[128] ={0};
        for(j = 0; j < WIDTH; ++j)
        {
            arr[j] = BackGround[i][j] + '0';
        }
        if(i == 0)
            printf("\033[5;30H %s",arr);
        if(i == 1)
            printf("\033[6;30H %s",arr);
        if(i == 2)
            printf("\033[7;30H %s",arr);
        if(i == 3)
            printf("\033[8;30H %s",arr);
        if(i == 4)
            printf("\033[9;30H %s",arr);
        if(i == 5)
            printf("\033[10;30H %s",arr);
        if(i == 6)
            printf("\033[11;30H %s",arr);
        if(i == 7)
            printf("\033[12;30H %s",arr);
        if(i == 8)
            printf("\033[13;30H %s",arr);
        if(i == 9)
            printf("\033[14;30H %s",arr);
        if(i == 10)
            printf("\033[15;30H %s",arr);
        if(i == 11)
            printf("\033[16;30H %s",arr);
        if(i == 12)
            printf("\033[17;30H %s",arr);
        if(i == 13)
            printf("\033[18;30H %s",arr);
        if(i == 14)
            printf("\033[19;30H %s",arr);
        if(i == 15)
            printf("\033[20;30H %s",arr);
        if(i == 16)
            printf("\033[21;30H %s",arr);
        if(i == 17)
            printf("\033[22;30H %s",arr);
        if(i == 18)
            printf("\033[23;30H %s",arr);
        if(i == 19)
            printf("\033[24;30H %s",arr);
    }
}

