#include "../utils/primitives.h"
#include <immintrin.h>

typedef struct {
	int		mass;
	float	x;
	float	y;
	float	dx;
	float	dy;
	bool	alive;
}			particule_t;

#define G 0.1
#define DUST_MAX 10000

static bool	create_particule = false;
static int	mouse_x = 0;
static int	mouse_y = 0;
static particule_t	*dust = NULL;
static bool	paused = false;
static size_t creation_quantity = 1;

void	on_kb_press(struct mfb_window *win, mfb_key key, mfb_key_mod mod, bool pressed)
{
	if (!pressed)
		return ;
	switch (key) {
		case MFB_KB_KEY_SPACE:
			paused = !paused;
			break;
		case MFB_KB_KEY_M:
			creation_quantity--;
			break;
		case MFB_KB_KEY_P:
			creation_quantity++;
			break;
		case MFB_KB_KEY_ESCAPE:
			mfb_close(win);
			free(dust);
			return ;
	}
}

void	on_mouse_click(struct mfb_window *win, mfb_mouse_button btn, mfb_key_mod mod, bool pressed)
{
	if (btn == MFB_MOUSE_BTN_1 && pressed) {
		mouse_x = mfb_get_mouse_x(win);
		mouse_y = mfb_get_mouse_y(win);
	}
	if (btn == MFB_MOUSE_BTN_1 && !pressed) {
		create_particule = true;
	}
}

static inline void	draw_particule(uint32_t *buffer, particule_t p)
{
		int speed = fabs(p.dx) + fabs(p.dy);
		uint32_t color = (speed < 255)? MFB_RGB(255, 255 - speed, 255 - speed) \
						: MFB_RGB(255 - speed % 255, 0, speed % 255);
		plot(buffer, POS((int)(p.x), (int)(p.y)), color);

}

void	calculate_collision(particule_t *a, particule_t *b)
{
	float	Fax = a->dx * a->mass;
	float	Fay = a->dy * a->mass;
	float	Fbx = b->dx * b->mass;
	float	Fby = b->dy * b->mass;
	float	m = a->mass + b->mass;
	a->dx = (Fax + Fbx) / m;
	a->dy = (Fay + Fby) / m;
	b->dx = (Fax + Fbx) / m;
	b->dy = (Fay + Fby) / m;
	a->x += a->dx / (fabs(a->dx) + fabs(a->dy));
	a->y += a->dy / (fabs(a->dx) + fabs(a->dy));
}

void	calculate_particules_movement(uint32_t *buffer)
{
	float	acc, ax, ay;

	for (int i = 0; i < DUST_MAX; i++) {
		if (dust[i].x < 0 || dust[i].y < 0 || dust[i].x > WIDTH || dust[i].y > HEIGHT)
			dust[i].alive = false;
		if (!dust[i].alive)
			continue;
		acc = 0;
		ax = 0;
		ay = 0;
		for (int j = 0; j < DUST_MAX; j++) {
			if (i == j || !dust[j].alive)
				continue;
			if ((int)dust[i].x == (int)dust[j].x && (int)dust[i].y == (int)dust[j].y) {
				calculate_collision(&dust[i], &dust[j]);
			}
			float	normt = norm(dust[i].x, dust[i].y, dust[j].x, dust[j].y);
			float	normx = norm(dust[i].x, 0, dust[j].x, 0);
			float	normy = norm(0, dust[i].y, 0, dust[j].y);
			acc = G * dust[i].mass * dust[j].mass / (normt * dust[i].mass); // F / Mass
			ax +=(dust[j].x - dust[i].x > 0)? (normx * acc / normt) : -(normx * acc / normt);
			ay +=(dust[j].y - dust[i].y > 0)? (normy * acc / normt) : -(normy * acc / normt);
		}
		dust[i].dx += ax;
		dust[i].dy += ay;
		draw_particule(buffer, dust[i]);
	}
}

void	demo_gravity(struct mfb_window *win, uint32_t *buffer, double dt)
{
	static int	dust_nb = 0;
	if (!dust)	dust = calloc(DUST_MAX + 1, sizeof(particule_t));
	if (!dust)	return ;

	mfb_set_mouse_button_callback(win, on_mouse_click);
	mfb_set_keyboard_callback(win, on_kb_press);
	write_unb(buffer, POS(WIDTH - 10, 10), creation_quantity, MFB_RGB(255, 255, 255));
	if (create_particule) {
		for (int i = 0; i < creation_quantity; i++) {
			bool test_max_count = false;
			while(dust[dust_nb].alive) {
				dust_nb++;
				dust_nb %= DUST_MAX;
				if (dust_nb == DUST_MAX - 1) {
					if (test_max_count) {
						break;
					}
					test_max_count = true;
					write_str(buffer, POS(10, 20), "Max particule count!", MFB_RGB(255, 255, 255));
				}
			}
			int sqr = sqrt(creation_quantity);
			dust[dust_nb] = (particule_t){2, mouse_x + i % sqr - sqr / 2, mouse_y + i / sqr - sqr / 2, \
							mfb_get_mouse_x(win) - mouse_x, mfb_get_mouse_y(win) - mouse_y, true};
			dust_nb++;
			dust_nb %= DUST_MAX;
		}
		mouse_x = 0;
		mouse_y = 0;
		create_particule = false;
	}
	if (mouse_x && mouse_y)
		draw_line(buffer, (t_point){{mouse_x, mouse_y}}, \
				(t_point){{mfb_get_mouse_x(win), mfb_get_mouse_y(win)}}, MFB_RGB(255, 255, 255));
	if (paused) {
		write_str(buffer, POS(10, 10), "Paused!", MFB_RGB(255, 255, 255));
		for (int i = 0; i < DUST_MAX; i++) {
			if (!dust[i].alive)
				continue;
			draw_particule(buffer, dust[i]);
		}
	}
	else {
		calculate_particules_movement(buffer);
		for	(int i = 0; i < DUST_MAX; i++) {
			dust[i].x += dust[i].dx * dt;
			dust[i].y += dust[i].dy * dt;
		}
	}
}

