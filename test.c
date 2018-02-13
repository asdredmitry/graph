#include <stdio.h>
#include "plot_x11.h"

/* ������� ��������� ������� */
static int variant = 0;

/* ���������� ���������� ���� */
static void
DrawWindowContent (void)
{
  int width = nWWidth;		/* ������� ������ ������ */
  int height = nWHeight;	/* ������� ������ ������ */

  WSetColor (DARKGRAY);
  WFillRectangle (0, 0, width, height);

  WSetColor (BLACK);
  WDrawLine (0, height / 2, width, height / 2);
  WDrawLine (width / 2, 0, width / 2, height);

  WDrawString ("Press Q to quit, F1...F4 to change function", 10, 20);

  switch (variant)
  {
  case 1:
    WSetColor (BLUE);
    WDrawLine (0, height, width, 0);
    break;
  case 2:
    WSetColor (GREEN);
    WDrawLine (0, 0, width, height);
    break;
  case 3:
    WSetColor (BLUE);
    {
      int i;
      double x_start, y_start, x_end, y_end;

      for (i = 1; i < width; i++)
	{
	  x_start = i - 1;
	  y_start = (x_start - width / 2) * (x_start  - width / 2) / (width / 2 * width / 2) * height;
	  x_end = i;
	  y_end = (x_end  - width / 2) * (x_end  - width / 2) / (width / 2 * width / 2) * height;
	  WDrawLine (x_start, y_start, x_end, y_end);
	}
    }
    break;
  case 4:
    WSetColor (GREEN);
    {
      int i;
      double x_start, y_start, x_end, y_end;

      for (i = 1; i < width; i++)
	{
	  x_start = i - 1;
	  y_start = (1. - (x_start - width / 2) * (x_start  - width / 2) / (width / 2 * width / 2)) * height;
	  x_end = i;
	  y_end = (1. - (x_end	- width / 2) * (x_end  - width / 2) / (width / 2 * width / 2)) * height;
	  WDrawLine (x_start, y_start, x_end, y_end);
	}
    }
    break;
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

  /* ����� �� ����� X11. */
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