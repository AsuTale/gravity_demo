#ifndef FB_H
# define FB_H

#include <stdio.h>
#include <unistd.h>
#include <MiniFB.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define WIDTH  1366
#define HEIGHT 768

#define X(pix)		((int)(pix) % WIDTH)
#define Y(pix)		((int)(pix) / WIDTH)
#define POS(x, y)	((x) + (y) * WIDTH)

typedef union	{
	struct {
		int	x;
		int	y;
	};
	int		vec[2];
}			t_point;

void	demo_gravity(struct mfb_window *win, uint32_t *buffer, double dt);

#endif
