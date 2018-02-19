#include <stdio.h>
#include "plot_x11.h"
#include <math.h>
double begin,end,c;
double accuracy;
/* ������� ��������� ������� */
static int variant = 0;

/* ���������� ���������� ���� */
double func(double);
double func(double x)
{
    return 2*sin(x) + 2.4;
}
static void
DrawWindowContent (void)
{
    double up,down;
    double abswidth,absheight,aspectRatio,windowAspectRatio;
    double ratio,add,addx;
    int width = nWWidth;		/* ������� ������ ������ */
    int height = nWHeight;	/* ������� ������ ������ */

    WSetColor (DARKGRAY);
    WFillRectangle (0, 0, width, height);
    //double up,down;
    up = func(begin);
    down = up;
    //printf("%lf up1  %lf down1 \n",up,down);
    for(double i = begin; i < end; i+= accuracy)
    {
        if(up < func(i))
        {
            up = func(i);
        }
        if(up < func(c*i))
        {
            up = func(c*i);
        }
        if(down > func(c*i))
            down = func(c*i);
        if(down > func(i))
            down = func(i);
    }
    //printf("%lf up  %lf down \n",up,down);
    abswidth = end - begin;
    absheight = (down < 0) ? up - down : up;
    aspectRatio = absheight/abswidth;
    windowAspectRatio = (double)height/(double)width;
    WSetColor (BLUE);
    add = 0;
    addx = 0;
    if(aspectRatio <= windowAspectRatio)
    {
        ratio = ((double)width)/abswidth;
        add = height - absheight*ratio;
        add /= 2;
    }
    else
    {
        ratio = ((double)height)/absheight;
        addx = width - abswidth*ratio;
        addx /= 2;
    }
    //addx = 0;
    //add = 0;
    if(begin*end < 0)
        WDrawLine(-begin*ratio + addx,0 ,-begin*ratio + addx,(((up - down)*ratio < height) ? height : (up - down)*ratio) + add);
    if(up*down < 0)
        WDrawLine(0,up*ratio + add ,(((end - begin)*ratio < width) ? width  :(end - begin)*ratio) + addx ,up*ratio + add);
    for(double i = begin; i < end; i += accuracy)
    {
        WSetColor (BLUE);
        if (variant == 1 || variant == 3)
            WDrawLine ((i - begin + accuracy)*ratio + addx, fabs(func(i + accuracy) - up)*ratio + add, (i - begin)*ratio  + addx, fabs(func(i) - up)*ratio + add);
        WSetColor(RED);
        if(variant == 2 || variant == 3)
            WDrawLine ((i - begin + accuracy)*ratio + addx, fabs(func(c*(i+ accuracy)) - up)*ratio + add, (i - begin)*ratio + addx , fabs(func(c*i) - up)*ratio + add);
    }

}

static int
KeyPressFunction (int nKeySym)
{
    switch (nKeySym)
    {
    case XK_Q:
    case XK_q:
        return KEY_PRESS_QUIT;

    case XK_F1:
    case XK_1:
        variant = 1;
        WSetTitle ("Function 1");
        break;
    case XK_F2:
    case XK_2:
        variant = 2;
        WSetTitle ("Function 2");
        break;
    case XK_F3:
    case XK_3:
        variant = 3;
        WSetTitle ("Function 3");
        break;
    case XK_F4:
    case XK_4:
        variant = 4;
        WSetTitle ("Function 4");
        break;

    default:
        return KEY_PRESS_NOTHING;
    }

    /* ������������ ���� */
    return KEY_PRESS_EXPOSE;
}

int
main (void)
{
    int ret_code;
    accuracy = 0.001;  /* ����� �� ����� X11. */
    printf("Enter begin, end, c: \n");
    if(scanf("%lf %lf %lf",&begin, &end, &c) != 3)
    {
        printf("Error");
        return 0;
    }
    printf("%lf\n",(end - begin)/accuracy);
    if((end - begin)/accuracy > 1000000)
        accuracy = (end - begin)/1000000;
    ret_code = DrawWindow (DrawWindowContent, KeyPressFunction);
    if (ret_code)
    {
        switch (ret_code)
        {
        case PLOT_X11_ERR_1:
            printf ("%s\n", PLOT_X11_ERR_MSG_1);
            break;
        case PLOT_X11_ERR_2:
            printf ("%s\n", PLOT_X11_ERR_MSG_2);
            break;
        case PLOT_X11_ERR_3:
            printf ("%s\n", PLOT_X11_ERR_MSG_3);
            break;
        case PLOT_X11_ERR_4:
            printf ("%s\n", PLOT_X11_ERR_MSG_4);
            break;
        case PLOT_X11_ERR_5:
            printf ("%s\n", PLOT_X11_ERR_MSG_5);
            break;
        default:
            printf ("%s\n", PLOT_X11_ERR_MSG_DEF);
            break;
        }
        return ret_code;
    }

    return 0;
}
