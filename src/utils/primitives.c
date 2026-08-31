#include "primitives.h"

size_t	draw_line(uint32_t *buff, t_point a, t_point b, uint32_t color)
{
	if (a.x > b.x) {
		int t;
		t = a.x; a.x = b.x; b.x = t;
		t = a.y; a.y = b.y; b.y = t;
	}
	int dx = b.x - a.x;
	if (!dx)
		return (0);
	int dy = b.y - a.y;
	for (int x = a.x; x <= b.x; x++) {
		int y = a.y + dy * (x - a.x) / dx;
		plot(buff, POS(x, y), color);
	}
}

size_t	draw_rect(uint32_t *buff, t_point origin, t_point size, uint32_t color, bool fill)
{
	for (int y = 0; y <= size.y; y++) {
		for (int x = 0; x <= size.x; x++) {
			if (!fill && (x == 0 || y == 0 || x == size.x || y == size.y))
				plot(buff, POS(x + origin.x, y + origin.y), color);
			else if (fill)
				plot(buff, POS(x + origin.x, y + origin.y), color);
		}
	}
	return ((fill)? size.x * size.y : size.x * 2 + size.y * 2 - 4);
}

size_t draw_circ(uint32_t *buf, t_point o, unsigned r, uint32_t color) {
	int	x = r;
	int	y = 0;
	int	err = 0;

	plot(buf, o.x + o.y * WIDTH, color);
	while (x >= y) {
		plot(buf, POS(o.x + x, o.y + y), color);
		plot(buf, POS(o.x + y, o.y + x), color);
		plot(buf, POS(o.x - y, o.y + x), color);
		plot(buf, POS(o.x - x, o.y + y), color);
		plot(buf, POS(o.x - x, o.y - y), color);
		plot(buf, POS(o.x - y, o.y - x), color);
		plot(buf, POS(o.x + y, o.y - x), color);
		plot(buf, POS(o.x + x, o.y - y), color);
		y++;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0) {
			x--;
			err += 1 - 2 * x;
		}
	}
	return (2 * M_PI * r);
}

