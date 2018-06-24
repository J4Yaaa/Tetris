#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

static int flag = 0;

//前景色和背景色
#define FRONTCOLOR 5
#define BACKCOLOR 0

//边框的大小
#define HIGH  20
#define WIDTH 10

//边框是一个 WIDTH*HIGH 的二维数组
int BackGround[HIGH][WIDTH];

//每一个图形都有一个 5*5 的二维数组
typedef struct shape
{
    int s[5][5];
}shape;

//表示图形对于当前 5*5 格子的位置
typedef struct graph
{
    int x;
    int y;
}graph;

//绘制 7 种图案的起始状态
static shape shape_arr[7] = {
    { 0,0,0,0,0, 0,0,1,0,0, 0,1,1,1,0, 0,0,0,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,2,0,0, 0,0,2,0,0, 0,0,2,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,3,0,0, 0,0,3,0,0, 0,0,3,3,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,4,0,0, 0,0,4,0,0, 0,4,4,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,5,5,0,0, 0,5,5,0,0, 0,0,0,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,6,6,0,0, 0,0,6,6,0, 0,0,0,0,0, 0,0,0,0,0 },
    { 0,0,0,0,0, 0,0,7,7,0, 0,7,7,0,0, 0,0,0,0,0, 0,0,0,0,0 } 
};


static graph t = {3,3};//图形的起始位置是整个屏幕的 3,0
static shape p ;//用 shape_arr[0] 进行测试

void clear_line();
void PrintArr();
