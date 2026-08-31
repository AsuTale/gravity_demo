#include "fb.h"
#include "utils/primitives.h"

int WIDTH = 0;
int HEIGHT = 0;

int main(int argc, char **argv)
{
	if (argc < 3)
		return (printf("Usage: ./demo <width> <height>. MUST BE YOUR SCREEN RESOLUTION\n"));
	WIDTH  = atoi(argv[1]);
	HEIGHT = atoi(argv[2]);

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

		if (mfb_update(win, buffer) != MFB_STATE_OK) break;
	}
	mfb_timer_destroy(chrono);
	free(buffer);
	return 0;
}

