#include <glut.h>
#include "mlx.h"

extern t_mlx *M;
extern int keys_glut2mlx[256];

static void timer_f(int value)
{
	M->loop_hook(M->loop_hook_p);
	glutTimerFunc(17, timer_f, 0);
}

void mlx_loop_hook(t_mlx *mlx, void (*loop_hook)(void *p), void *p)
{
	if (mlx->loop_hook)
		ft_error_exit("loop hook called twice");
	mlx->loop_hook = loop_hook;
	mlx->loop_hook_p = p;
	glutTimerFunc(17, timer_f, 0);
}

static void cb_key_press(unsigned char key, int x, int y)
{
	t_mlx_hook *h;
	int keycode;

	h = &M->win->hooks[MLX_EVENT_KEY_PRESS];
	keycode = keys_glut2mlx[key];
	h->f(keycode, h->p);
}

void mlx_hook(t_mlx_win *win, int event, int event_mask,
			  void (*hook)(int keycode, void *p), void *p)
{
	t_mlx_hook *h;

	h = &win->hooks[event];
	h->f = hook;
	h->p = p;
	//todo: protection from calling twice?
	glutKeyboardFunc(cb_key_press);
}