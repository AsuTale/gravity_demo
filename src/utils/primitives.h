#ifndef PRIMITIVES_H
# define PRIMITIVES_H

#include "../fb.h"

static inline void plot(uint32_t *buf, int pos, uint32_t color) {
	if (X(pos) > 0 && X(pos) < WIDTH && Y(pos) > 0 && Y(pos) < HEIGHT)
		buf[pos] = color;
}
static inline float norm(float x1, float y1, float x2, float y2) {
	return (sqrtf(\
			(x2 - x1) * (x2 - x1) + \
			(y2 - y1) * (y2 - y1)));
}
size_t	draw_line(uint32_t *buff, t_point a, t_point b, uint32_t color);
size_t	draw_rect(uint32_t *buff, t_point origin, t_point size, uint32_t color, bool fill);
size_t	draw_circ(uint32_t *buff, t_point o, unsigned r, uint32_t color);
void	write_char(uint32_t *buffer, size_t pos, char c, uint32_t color);
void	write_str(uint32_t *buffer, size_t pos, char *str, uint32_t color);
void	write_unb(uint32_t *buffer, size_t pos, size_t nb, uint32_t color);

#endif

