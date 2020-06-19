
#include "panel.h"
#include "core.h"
#include "winrend.h"
#include "grid.h"
#include "rule.h"
#include <SDL2/SDL.h>

int g_panel_scroll = 0;

static SDL_Texture* s_panel_texture = NULL;

void init_panel(void)
{
	s_panel_texture = SDL_CreateTexture(
		g_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 800);
}

void close_panel(void)
{

}

void refresh_panel(void)
{
	/* Do it on s_panel_texture */
	SDL_SetRenderTarget(g_renderer, s_panel_texture);
	/* Background */
	SDL_Rect rect = {.x = 0, .y = 0, .w = 500, .h = 800};
	SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(g_renderer, &rect);
	/* Rule name */
	int current_y = g_panel_scroll;
	TTF_SizeText(g_font, g_rule.name, &rect.w, NULL);
	rect.y = current_y; rect.w += 6; rect.h = 20;
	SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
	SDL_RenderFillRect(g_renderer, &rect);
	draw_text(g_rule.name, 0, 0, 0, 3, current_y, 0);
	current_y += 20;
	/* Rule state_count */
	char string[100];
	sprintf(string, "%d", g_rule.state_count);
	TTF_SizeText(g_font, string, &rect.w, NULL);
	rect.y = current_y; rect.w += 6;
	SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
	SDL_RenderFillRect(g_renderer, &rect);
	draw_text(string, 0, 0, 0, 3, current_y, 0);
	current_y += 20;
	/* Rule states */
	for (int s = 0; s < g_rule.state_count; s ++)
	{
		state_t* state = &g_rule.state_l[s];
		/* State id */
		sprintf(string, "%d", s);
		rect.x = 0; rect.y = current_y; rect.w = 20; rect.h = 20;
		SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
		SDL_RenderFillRect(g_renderer, &rect);
		draw_text(string, 0, 0, 0, 10, current_y, 1);
		/* State color */
		rect.x = 20;
		SDL_SetRenderDrawColor(g_renderer,
			state->r, state->g, state->b, 255);
		SDL_RenderFillRect(g_renderer, &rect);
		/* State behavior_count */
		sprintf(string, "%d", state->behavior_count);
		TTF_SizeText(g_font, string, &rect.w, NULL);
		rect.x = 40; rect.w += 6;
		SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
		SDL_RenderFillRect(g_renderer, &rect);
		draw_text(string, 0, 0, 0, 43, current_y, 0);
		current_y += 20;
		/* State behaviors */
		for (int b = 0; b < state->behavior_count; b ++)
		{
			behavior_t* behavior = &state->behavior_l[b];
			/* Left bar from state */
			if (b == state->behavior_count-1 && behavior->condition_count == 0)
			{
				rect.x = 7; rect.y = current_y; rect.w = 6; rect.h = 13;
				SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
				SDL_RenderFillRect(g_renderer, &rect);
				rect.y = current_y+7; rect.w = 11; rect.h = 6;
				SDL_RenderFillRect(g_renderer, &rect);
			}
			else
			{
				rect.x = 7; rect.y = current_y; rect.w = 6; rect.h = 20;
				SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
				SDL_RenderFillRect(g_renderer, &rect);
			}
			/* Behavior destination state id */
			int dest_id = behavior->destination_state_id;
			sprintf(string, "%d", dest_id);
			rect.x = 20; rect.y = current_y; rect.w = 20; rect.h = 20;
			SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
			SDL_RenderFillRect(g_renderer, &rect);
			draw_text(string, 0, 0, 0, 30, current_y, 1);
			/* Behavior destination state color */
			rect.x = 40; rect.y = current_y+5; rect.w = 5; rect.h = 10;
			SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
			SDL_RenderFillRect(g_renderer, &rect);
			rect.x = 45; rect.w = 10;
			SDL_SetRenderDrawColor(g_renderer,
				g_rule.state_l[dest_id].r, g_rule.state_l[dest_id].g, g_rule.state_l[dest_id].b, 255);
			SDL_RenderFillRect(g_renderer, &rect);
			/* Behavior condition_count */
			sprintf(string, "%d", behavior->condition_count);
			TTF_SizeText(g_font, string, &rect.w, NULL);
			rect.x = 60; rect.y = current_y; rect.w += 6; rect.h = 20;
			SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
			SDL_RenderFillRect(g_renderer, &rect);
			draw_text(string, 0, 0, 0, 63, current_y, 0);
			current_y += 20;
			/* Behavior conditions */
			for (int c = 0; c < behavior->condition_count; c ++)
			{
				condition_t* condition = &behavior->condition_l[c];
				/* Left bar from state */
				if (b == state->behavior_count-1 && c == behavior->condition_count-1)
				{
					rect.x = 7; rect.y = current_y; rect.w = 6; rect.h = 13;
					SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
					SDL_RenderFillRect(g_renderer, &rect);
					rect.y = current_y+7; rect.w = 11; rect.h = 6;
					SDL_RenderFillRect(g_renderer, &rect);
				}
				else
				{
					rect.x = 7; rect.y = current_y; rect.w = 6; rect.h = 20;
					SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
					SDL_RenderFillRect(g_renderer, &rect);
				}
				/* Left bar from behavior */
				if (c == behavior->condition_count-1)
				{
					rect.x = 27; rect.y = current_y; rect.w = 6; rect.h = 13;
					SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
					SDL_RenderFillRect(g_renderer, &rect);
					rect.y = current_y+7; rect.w = 11; rect.h = 6;
					SDL_RenderFillRect(g_renderer, &rect);
				}
				else
				{
					rect.x = 27; rect.y = current_y; rect.w = 6; rect.h = 20;
					SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
					SDL_RenderFillRect(g_renderer, &rect);
				}
				/* Condition shape */
				rect.x = 40; rect.y = current_y; rect.w = 20; rect.h = 20;
				SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
				SDL_RenderFillRect(g_renderer, &rect);
				SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
				if (condition->shape == PLUS_SHAPE)
				{
					rect.x = 47; rect.y = current_y+1; rect.w = 6; rect.h = 6;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.y = current_y+13;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.x = 41; rect.y = current_y+7;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.x = 53;
					SDL_RenderFillRect(g_renderer, &rect);
				}
				else if (condition->shape == CROSS_SHAPE)
				{
					rect.x = 41; rect.y = current_y+1; rect.w = 6; rect.h = 6;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.x = 53;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.x = 41; rect.y = current_y+13;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.x = 53;
					SDL_RenderFillRect(g_renderer, &rect);
				}
				else if (condition->shape == SQUARE_SHAPE)
				{
					rect.x = 41; rect.y = current_y+1; rect.w = 18; rect.h = 6;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.w = 6; rect.h = 18;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.x = 41; rect.y = current_y+13; rect.w = 18; rect.h = 6;
					SDL_RenderFillRect(g_renderer, &rect);
					rect.x = 53; rect.y = current_y+1; rect.w = 6; rect.h = 18;
					SDL_RenderFillRect(g_renderer, &rect);
				}
				/* Condition numbers */
				rect.y = current_y; rect.w = 20; rect.h = 20;
				for (int n = 0; n < 9; n ++)
				{
					sprintf(string, "%d", n);
					rect.x = 60+n*20;
					if (n > 4 && condition->shape != SQUARE_SHAPE)
					{
						SDL_SetRenderDrawColor(g_renderer, 100, 100, 230, 255);
					}
					else if (condition->number[n])
					{
						SDL_SetRenderDrawColor(g_renderer, 100, 230, 100, 255);
					}
					else
					{
						SDL_SetRenderDrawColor(g_renderer, 230, 100, 100, 255);
					}
					SDL_RenderFillRect(g_renderer, &rect);
					draw_text(string, 0, 0, 0, rect.x+10, current_y, 1);
				}
				/* Condition state id */
				sprintf(string, "%d", condition->state_id);
				rect.x = 240; rect.y = current_y;
				SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
				SDL_RenderFillRect(g_renderer, &rect);
				draw_text(string, 0, 0, 0, 250, current_y, 1);
				/* Condition state color */
				rect.x = 260; rect.y = current_y+5; rect.w = 5; rect.h = 10;
				SDL_SetRenderDrawColor(g_renderer, 230, 230, 230, 255);
				SDL_RenderFillRect(g_renderer, &rect);
				rect.x = 265; rect.w = 10;
				SDL_SetRenderDrawColor(g_renderer, g_rule.state_l[condition->state_id].r,
					g_rule.state_l[condition->state_id].g, g_rule.state_l[condition->state_id].b, 255);
				SDL_RenderFillRect(g_renderer, &rect);
				current_y += 20;
			}
		}
	}
	/* Quit s_panel_texture */
	SDL_SetRenderTarget(g_renderer, NULL);
}

void draw_panel(void)
{
	/* Background */
	SDL_Rect rect = {.x = 800, .y = 0, .w = 500, .h = 800};
	SDL_SetRenderDrawColor(g_renderer, 200, 200, 200, 255);
	SDL_RenderFillRect(g_renderer, &rect);
	/* Panel texture */
	SDL_RenderCopy(g_renderer, s_panel_texture, NULL, &rect);
	/* Performance bar */
	rect.y = 790; rect.w = g_ticks_per_step; rect.h = 10;
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(g_renderer, &rect);
	/* Skip drawings bar */
	rect.y = 780; rect.w = g_draw_every * 10;
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(g_renderer, &rect);
}
