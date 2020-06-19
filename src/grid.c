
#include "grid.h"
#include "rule.h"
#include "winrend.h"
#include "random.h"
#include <stdlib.h>

int  g_grid_size  = 0;
int* g_grid_cur   = NULL;
int* g_grid_next  = NULL;
int  g_draw_every = 1;

void init_grid(void)
{
	g_grid_size = 100;
	g_grid_cur  = calloc(g_grid_size * g_grid_size, sizeof(int));
	g_grid_next = calloc(g_grid_size * g_grid_size, sizeof(int));
}

void close_grid(void)
{
	g_grid_size = 0;
	if (g_grid_cur != NULL)
	{
		free(g_grid_cur);
		g_grid_cur = NULL;
	}
	if (g_grid_next != NULL)
	{
		free(g_grid_next);
		g_grid_next = NULL;
	}
}

void change_grid_size(int new_size)
{
	int* new_grid_cur  = calloc(new_size * new_size, sizeof(int));
	int* new_grid_next = calloc(new_size * new_size, sizeof(int));
	int minsize = (new_size < g_grid_size) ? new_size : g_grid_size;
	for (int y = 0; y < minsize; y ++)
	for (int x = 0; x < minsize; x ++)
	{
		new_grid_cur[ x + new_size * y] = g_grid_cur[ GCOORDS(x, y)];
		new_grid_next[x + new_size * y] = g_grid_next[GCOORDS(x, y)];
	}
	free(g_grid_cur);
	free(g_grid_next);
	g_grid_size = new_size;
	g_grid_cur  = new_grid_cur;
	g_grid_next = new_grid_next;
}

void swap_cur_next_grid(void)
{
	int* temp = g_grid_next;
	g_grid_next = g_grid_cur;
	g_grid_cur = temp;
}

void draw_cur_grid(void)
{
	int case_side = 800 / g_grid_size;
	SDL_Rect rect = {.w = case_side, .h = case_side};
	for (int y = 0; y < g_grid_size; y ++)
	for (int x = 0; x < g_grid_size; x ++)
	{
		rect.x = x * case_side;
		rect.y = y * case_side;
		state_t* state = &g_rule.state_l[g_grid_cur[GCOORDS(x, y)]];
		SDL_SetRenderDrawColor(g_renderer, state->r, state->g, state->b, 255);
		SDL_RenderFillRect(g_renderer, &rect);
	}
}

void randomize_grid(void)
{
	for (int y = 0; y < g_grid_size; y ++)
	for (int x = 0; x < g_grid_size; x ++)
	{
		g_grid_cur[GCOORDS(x, y)] = random_int(0, g_rule.state_count-1);
	}
}

void verify_grid(void)
{
	for (int y = 0; y < g_grid_size; y ++)
	for (int x = 0; x < g_grid_size; x ++)
	{
		if (g_grid_cur[GCOORDS(x, y)] >= g_rule.state_count)
		{
			g_grid_cur[GCOORDS(x, y)] = 0;
		}
	}
}

void run_grid(void)
{
	int* plus_count   = malloc(g_rule.state_count * sizeof(int));
	int* cross_count  = malloc(g_rule.state_count * sizeof(int));
	int* square_count = malloc(g_rule.state_count * sizeof(int));
	for (int y = 0; y < g_grid_size; y ++)
	for (int x = 0; x < g_grid_size; x ++)
	{
		/* Count neighbor states */
		for (int i = 0; i < g_rule.state_count; i ++)
		{
			plus_count[i]   = 0;
			cross_count[i]  = 0;
			square_count[i] = 0;
		}
		plus_count[  g_grid_cur[GCOORDSWARP(x  , y-1)]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x  , y-1)]] += 1;
		plus_count[  g_grid_cur[GCOORDSWARP(x  , y+1)]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x  , y+1)]] += 1;
		plus_count[  g_grid_cur[GCOORDSWARP(x-1, y  )]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x-1, y  )]] += 1;
		plus_count[  g_grid_cur[GCOORDSWARP(x+1, y  )]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x+1, y  )]] += 1;
		cross_count[ g_grid_cur[GCOORDSWARP(x-1, y-1)]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x-1, y-1)]] += 1;
		cross_count[ g_grid_cur[GCOORDSWARP(x+1, y-1)]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x+1, y-1)]] += 1;
		cross_count[ g_grid_cur[GCOORDSWARP(x-1, y+1)]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x-1, y+1)]] += 1;
		cross_count[ g_grid_cur[GCOORDSWARP(x+1, y+1)]] += 1;
		square_count[g_grid_cur[GCOORDSWARP(x+1, y+1)]] += 1;
		/* Apply to the state rule */
		state_t* state = &g_rule.state_l[g_grid_cur[GCOORDS(x, y)]];
		int behavior_applyed = 0;
		for (int b = 0; b < state->behavior_count; b ++)
		{
			behavior_t* behavior = &state->behavior_l[b];
			int all_respected = 1;
			for (int c = 0; c < behavior->condition_count; c ++)
			{
				int respected = 1;
				condition_t* condition = &behavior->condition_l[c];
				if (condition->shape == PLUS_SHAPE)
				{
					if (condition->number[plus_count[condition->state_id]] == 0)
					{
						respected = 0;
					}
				}
				else if (condition->shape == CROSS_SHAPE)
				{
					if (condition->number[cross_count[condition->state_id]] == 0)
					{
						respected = 0;
					}
				}
				else if (condition->shape == SQUARE_SHAPE)
				{
					if (condition->number[square_count[condition->state_id]] == 0)
					{
						respected = 0;
					}
				}
				if (respected == 0)
				{
					all_respected = 0;
					break;
				}
			}
			if (all_respected)
			{
				g_grid_next[GCOORDS(x, y)] = behavior->destination_state_id;
				behavior_applyed = 1;
				break;
			}
		}
		if (behavior_applyed == 0)
		{
			g_grid_next[GCOORDS(x, y)] = g_grid_cur[GCOORDS(x, y)];
		}
	}
}

