#include <stdio.h>
#include "plot_x11.h"
#include <math.h>
double begin,end,c;
double accuracy;
/* Вариант рисуемого графика */
static int variant = 0;

/* Нарисовать содержимое окна */
double func(double);
 double func(double x)
{
  return sin(x);
}
static void
DrawWindowContent (void)
{
  double up,down;
  double abswidth,absheight,aspectRatio,windowAspectRatio;
    double ratio;
  int width = nWWidth;		/* Текущая ширина экрана */
  int height = nWHeight;	/* Текущая высота экрана */

  WSetColor (DARKGRAY);
  WFillRectangle (0, 0, width, height);
  //double up,down;
  up = func(begin);
  down = up;
  for(double i = begin; i < end; i+= accuracy)
  {
    if(up < func(i))
      up = func(i);
    if(up < func(c*i))
        up = func(i);
    if(down > func(c*i))
        down = func(c*i);(end - begin)*ratio;
    if(down > func(i))
      down = func(i);
  }
  abswidth = end - begin;
  absheight = (down < 0) ? up - down : 2*up;
  aspectRatio = absheight/abswidth;
  windowAspectRatio = (double)height/(double)width;
  WSetColor (BLUE);
  if(aspectRatio <= windowAspectRatio)
    ratio = ((double)width)/abswidth;
  else
    ratio = (double)height/absheight;
  printf("%lf %lf",up,down);
  WDrawLine(-begin*ratio,0,-begin*ratio,((up - down)*ratio < height) ? height : (up - down)*ratio);
  WDrawLine(0,up*ratio,((end - begin)*ratio < width) ? width  :(end - begin)*ratio ,up*ratio);
  for(double i = begin; i < end; i += accuracy)
  {
    WSetColor (BLUE);
    printf("%lf " ,i);
    WDrawLine ((i - begin + accuracy)*ratio, fabs(func(i + accuracy) - up)*ratio, (i - begin)*ratio , fabs(func(i) - up)*ratio);
        //WSetColor(RED);
        //WDrawLine ((i - begin + accuracy)*ratio, fabs(func(c*(i + accuracy)) - up)*ratio , (i - begin)*ratio, (func(c*i) - up)*ratio);
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

  /* Перерисовать окно */
  return KEY_PRESS_EXPOSE;
}

int
main (void)
{
  int ret_code;
    accuracy = 0.001;  /* Вывод на экран X11. */
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
