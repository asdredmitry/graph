#include <stdio.h>
#include "plot_x11.h"
#include <math.h>
double begin(-10),end(10),c(2);
double accuracy(0.001);
/* Вариант рисуемого графика */
static int variant = 0;

/* Нарисовать содержимое окна */
 double func(double x)
{
  return 10*sin(x);
}
static void
DrawWindowContent (void)
{
  int width = nWWidth;		/* Текущая ширина экрана */
  int height = nWHeight;	/* Текущая высота экрана */

  WSetColor (DARKGRAY);
  WFillRectangle (0, 0, width, height);

  WSetColor (BLACK);
  WDrawLine (0, height / 2, width, height / 2);
  WDrawLine (width / 2, 0, width / 2, height);

  double up,down;
  up = func(begin);
  down = up;
  for(double i = begin; i < end; i+= accuracy)
  {
    if(up < func(i))
      up = func(i);
    if(up < func(c*i))
        up = func(i);
    if(down > func(c*i))
        down = func(c*i);
    if(down > func(i))
      down = func(i);
  }
  double abswidth = end - begin;
  double absheight = (down < 0) ? up - down : 2*up;
  double aspectRatio = absheight/abswidth;
  double windowAspectRatio = (double)height/(double)width;
  WSetColor (BLUE);
  if(aspectRatio <= windowAspectRatio)
  {
  double ratio = ((double)width)/abswidth;
    for(double i = begin; i < end; i += accuracy)
    {
        WSetColor (BLUE);
        WDrawLine ((i + accuracy)*ratio + width/2, -func(i + accuracy)*ratio + height/2, (i)*ratio + width/2, -func(i)*ratio + height/2);
        WSetColor(RED);
        WDrawLine ((i + accuracy)*ratio + width/2, -func(c*(i + accuracy))*ratio + height/2, (i)*ratio + width/2, -func(c*i)*ratio + height/2);
    }  
  }
  else
  {
    double ratio = (double)height/absheight;
    for(double i = begin; i < end; i += accuracy)
    { 
        WSetColor (BLUE);
        WDrawLine (i*ratio + width/2, -func(i)*ratio + height/2, (i+accuracy)*ratio + width/2, -func(i + accuracy)*ratio + height/2);
        WSetColor(RED);
        WDrawLine (i*ratio + width/2, -func(c*i)*ratio + height/2, (i+accuracy)*ratio + width/2, -func(c*(i+accuracy))*ratio + height/2);
    }  
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

  /* Вывод на экран X11. */
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
