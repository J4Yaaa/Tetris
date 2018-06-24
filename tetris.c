#include "tetris.h"
#include "./keyboard.h"

//1.绘制小方块
void draw_grid(int x, int y, int c)
{
    x *= 2;
    x++;
    y++;
    printf("\033[%d;%dH", y, x);
    printf("\033[3%dm\033[4%dm", 7-c, 7-c);
    printf("[]");
    printf("\033[?25l");
    printf("\033[0m");
    fflush(stdout);
}

//2.背景数组里值为 1 设置为前景色，值为 0 设置为背景色
void draw_back()
{
    int i = 0;
    int j = 0;
    for(i = 0; i < HIGH; ++i)
    {
        for(j = 0; j < WIDTH; ++j)
        {
            if(BackGround[i][j] == 0)
            {
                draw_grid(j,i,BACKCOLOR);
            }
            else
            {
                draw_grid(j,i,BackGround[i][j]);
            }
        }
    }
}

//3.根据当前传进来的图形和位置，将对应位置置为 1
void add_shape(graph *t,shape *p)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            if(p->s[i][j] != 0)
            {
                BackGround[t->y+i][t->x+j] = p->s[2][2];
            }
        }
    }
}

//4.为向上下左右走移动，将原先位置置为0,和步骤四对应
void clear_shape(graph* t,shape* p)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            if(p->s[i][j] != 0)
            {
                BackGround[t->y+i][t->x+j] = 0;
            }
        }
    }
}

// 绘制背景色或者绘制前景色
void draw_shape(graph* t,shape* p,int C)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            if(p->s[i][j] != 0)
            {
                draw_grid(j+t->x,i+t->y,C);
            }
        }
    }
}

//5.判断下一个位置是否合法
int can_move(int x,int y,const shape* p)
{
    int i = 0;
    int j = 0;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            if(p->s[i][j] == 0)
            {//如果现在 5*5 的格子值为0， 就不管这个格子，不影响
                continue;
            }
            if(y+i >= HIGH)
            {//判断如果下一步超过最下方，就不可以移动
                draw_back();
                return 0;
            }
            if(x+j < 0 || x+j >= WIDTH)
            {//如果左边超过最小值0，或者右边超过最大值width，就不可以移动
                return 0;
            }
            if(BackGround[y+i][x+j] != 0)
            {//如果这个位置已经被走过，就不可以移动
                return 0;
            }
        }
    }
    printf("\033[3;30H x = %d,y = %d\n",y+i,x+j);
    return 1;
}

//判断有没有到顶
void over()
{
    int i = 0;
    for (i=0; i<WIDTH; i++){
        if ( BackGround[1][i] != 0  ) {
            printf("\033[?25h你输了!!!\n");
            recover_keyboard();
            exit(0);
        }
    }
}

//6.保证图形在一定时间内向下走
void graph_down(graph* t,shape* p)
{
    draw_shape(t,p,BACKCOLOR);
    clear_shape(t,p);
    if(can_move(t->x,t->y+1,p))
    {
        t->y += 1;
        add_shape(t,p);
        draw_shape(t,p,p->s[2][2]);
    }
    else
    {
        add_shape(t,p);
        draw_shape(t,p,p->s[2][2]);
        clear_line();
        over();
        draw_back();
        t->y = 0;
        t->x = 3;
        flag = 1;
    }
}

shape trun_90_right(shape t)
{
    shape tmp;
    int i = 0;
    int j = 0;
    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 5; ++j)
        {
            tmp.s[i][j] = t.s[4-j][i];
        }
    }
    return tmp;
}

//7.用户按下键盘以后，可以向左或者向右
void graph_left_right(graph* t,shape* p)
{
    int n = get_key();
    if(is_left(n))
    {
        clear_shape(t,p);
        draw_shape(t,p,BACKCOLOR);
        if(can_move(t->x-1,t->y,p))
        {
            t->x--;
            add_shape(t,p);
            draw_shape(t,p,p->s[2][2]);
        }
        else
        {
            draw_shape(t,p,p->s[2][2]);
        }
    }
    else if(is_right(n))
    {
        clear_shape(t,p);
        draw_shape(t,p,BACKCOLOR);
        if(can_move(t->x+1,t->y,p))
        {
            t->x++;
            add_shape(t,p);
            draw_shape(t,p,p->s[2][2]);
        }
        else
        {
            draw_shape(t,p,p->s[2][2]);
        }
    }
    else if(is_up(n)) //如果是上建的话就旋转
    {
        clear_shape(t,p);
        draw_shape(t,p,BACKCOLOR);
        *p = trun_90_right(*p);
        if(can_move(t->x,t->y,p) == 0)
        {
            *p = trun_90_right(*p);
            *p = trun_90_right(*p);
            *p = trun_90_right(*p);
        }
        add_shape(t,p);
        draw_shape(t,p,p->s[2][2]);
    }
    else if(is_down(n))
    {
        clear_shape(t,p);
        draw_shape(t,p,BACKCOLOR);
        if(can_move(t->x,t->y+1,p))
        {
            t->y++;
            add_shape(t,p);
            draw_shape(t,p,p->s[2][2]);
        }
        else
        {
            draw_shape(t,p,p->s[2][2]);
        }
    }
}

//8.如果一行满了，就消除一整行，并将上面的移到下面
void clear_line()
{
    int i = 0;
    int j = 0;
    for(i = 0; i < HIGH; ++i)
    {
        int count = 0;
        for(j = 0; j < WIDTH; ++j)
        {
            if(BackGround[i][j] != 0)
            {
                ++count;
            }
        }
        if(count == WIDTH) //如果一行已经满了，那么这一行就没有0
        {
            int k = i;
            for(; k > 0; --k)
            {
                memcpy(BackGround[k],BackGround[k-1],sizeof(BackGround[0]));
            }
            memset(BackGround[0],0x00,sizeof(BackGround[0]));
        }
    }
}

void MyHandler(int sig)
{
    (void)sig;
    printf("\033[?25h");
    recover_keyboard();
    exit(0);
}

void handler(int s)
{
    (void)s;
    if(flag == 1)
    {
        int n = rand()%7;
        p = shape_arr[n];
        flag = 0;
    }
    graph_down(&t,&p);
    draw_back();
    PrintArr();
}

int main()
{
    srand((unsigned int)time(NULL));
    signal(SIGINT,MyHandler);

    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, NULL);

    struct itimerval it;
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = 1;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 654321;
    setitimer(ITIMER_REAL, &it, NULL);

    p = shape_arr[4];//用 shape_arr[0] 进行测试
    init_keyboard();
    draw_back();    //首先要绘制背景
    while(1)
    {
        graph_left_right(&t,&p);
    }

    recover_keyboard();
    return 0;
}
