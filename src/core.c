
#include "core.h"
#include "winrend.h"
#include "grid.h"
#include "rule.h"
#include "random.h"
#include "panel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int g_core_loop_running = 0;
int g_ticks_per_step    = 1;

void core_init_everything(void)
{
	/* Itit thing in the right order */
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	TTF_Init();
	seed_timestamp_random();
	init_winrend();
	init_grid();
	init_panel();
}

void core_close_everything(void)
{
	/* Close thing in the right order */

	close_winrend();

	/* TODO */
}

void core_loop(void)
{
	int steps_since_drawing = 0;
	g_core_loop_running = 1;
	while (g_core_loop_running)
	{
		int init_time = SDL_GetTicks();
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					g_core_loop_running = 0;
				break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							g_core_loop_running = 0;
						break;

						case SDLK_g:
							randomize_grid();
						break;

						case SDLK_r:
							randomize_rule();
							refresh_panel();
							randomize_grid();
						break;

						case SDLK_c:
							randomize_rule_colors();
							refresh_panel();
						break;

						case SDLK_p:
							if (g_grid_size < 800)
							{
								int new_size = g_grid_size + 1;
								while ((800 / new_size) * new_size != 800)
								{
									new_size ++;
								}
								change_grid_size(new_size);
							}
						break;

						case SDLK_m:
							if (g_grid_size >= 2)
							{
								int new_size = g_grid_size - 1;
								while ((800 / new_size) * new_size != 800)
								{
									new_size --;
								}
								change_grid_size(new_size);
							}
						break;

						case SDLK_o:
							g_draw_every ++;
						break;

						case SDLK_l:
							if (g_draw_every >= 2)
							{
								g_draw_every --;
							}
						break;

						case SDLK_i:
							steps_since_drawing --;
						break;

						case SDLK_s:
							save_rule();
						break;

						case SDLK_k:
							load_rule();
							refresh_panel();
							verify_grid();
						break;

						case SDLK_u:
							g_panel_scroll += 20;
							refresh_panel();
						break;

						case SDLK_j:
							g_panel_scroll -= 20;
							refresh_panel();
						break;
					}
				break;
			}
		}
		/* Run */
		steps_since_drawing ++;
		run_grid();
		swap_cur_next_grid();

		/* Draw */
		if (g_draw_every <= steps_since_drawing)
		{
			steps_since_drawing = 0;
			draw_cur_grid();
		}
		draw_panel();
		SDL_RenderPresent(g_renderer);

		/* Speed evaluation */
		g_ticks_per_step = SDL_GetTicks() - init_time;
	}
}
