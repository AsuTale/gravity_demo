#include "fb.h"
#include "utils/primitives.h"

int main(void)
{
	struct mfb_window *win = mfb_open_ex("Demo", WIDTH, HEIGHT, MFB_WF_FULLSCREEN);
	if (!win) return 1;

	uint32_t *buffer = malloc(WIDTH * HEIGHT * sizeof(uint32_t));
	if (!buffer) { mfb_close(win); return 1; }

	struct mfb_timer *chrono = mfb_timer_create();
	mfb_set_target_fps(60);

	while (mfb_wait_sync(win)) {
		double t =	mfb_timer_now(chrono);
		double dt = mfb_timer_delta(chrono);
		memset(buffer, 0, WIDTH * HEIGHT * sizeof(uint32_t));

		demo_gravity(win, buffer, dt);
//		write_str(buffer, POS(10, 10), "Hello World!", MFB_RGB(200, 100, 100));
//		draw_line(buffer, (t_point){{0, 0}}, (t_point){{0, 190}}, MFB_RGB(255, 0, 0));
//		draw_rect(buffer, (t_point){{0, 0}}, (t_point){{4 * t, 200 + 4 * t}}, MFB_RGB(150, 0, 100), true);
//		draw_circ(buffer, (t_point){{55, 50}}, 25, MFB_RGB(0, 100, 255));

		if (mfb_update(win, buffer) != MFB_STATE_OK) break;
	}
	mfb_timer_destroy(chrono);
	free(buffer);
	return 0;
}

