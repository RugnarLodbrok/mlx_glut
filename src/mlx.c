#include <glut.h>
#include "mlx.h"
#include "mlx_consts.h"
#include "string.h"
#include "stdlib.h"

t_mlx *M;

static void display_f(void)
{
	int i;
	int j;
	unsigned int color;
	t_mlx_win *win;

	win = M->win;
	glBegin(GL_POINTS);
	for (i = 0; i < win->w; ++i)
	{
		for (j = 0; j < win->h; ++j)
		{
			color = win->framebuffer[win->w * j + i];
			glColor4ubv((GLubyte *)&color);
			glVertex2i(i, j);
		}
	}
	glEnd();
	glFlush();  // Render now
}

void *mlx_init()
{
	t_mlx *mlx;

	mlx = calloc(1, sizeof(t_mlx));
	M = mlx;
	mlx_init_glut_key_map();
	return mlx;
}

void mlx_pixel_put(t_mlx *mlx, t_mlx_win *win, int x, int y, unsigned int color)
{
	win->framebuffer[win->w * y + x] = color;
}

void *mlx_new_window(t_mlx *mlx, int w, int h, const char *title)
{
	int ac;
	char **av;
	t_mlx_win *win;

	win = calloc(1, sizeof(t_mlx));
	win->w = w;
	win->h = h;
	win->framebuffer = calloc(w*h, sizeof(unsigned int));
	win->hooks = calloc(MLX_EVENTS_NUMBER, sizeof(t_mlx_hook));
	mlx->win = win;
	ac = 0;
	av = 0;
	glutInit(&ac, av);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(w, h);
	glutCreateWindow(title);

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, h, 0.0);
	glutDisplayFunc(display_f);
	return (win);
}

void mlx_string_put(t_mlx *mlx, t_mlx_win *win, int x, int y, unsigned int color, const char *str)
{

}

void mlx_loop(t_mlx *mlx)
{
	glutMainLoop();
}
