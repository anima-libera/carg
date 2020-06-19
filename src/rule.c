
#include "rule.h"
#include "grid.h"
#include "random.h"
#include <stdlib.h>
#include <stdio.h>

rule_t g_rule = {.name = NULL, .state_count = 0, .state_l = NULL};

static int s_randomisation_count = 0;

void clear_state(state_t* state)
{
	state->r = 0; state->g = 0; state->b = 0;
	for (int b = 0; b < state->behavior_count; b ++)
	{
		free(state->behavior_l[b].condition_l);
	}
	free(state->behavior_l);
	state->behavior_l = NULL;
	state->behavior_count = 0;
}

void clear_rule(rule_t* rule)
{
	for (int s = 0; s < rule->state_count; s ++)
	{
		clear_state(&rule->state_l[s]);
	}
	free(rule->state_l);
	rule->state_l = NULL;
	rule->state_count = 0;
}

void randomize_rule(void)
{
	clear_rule(&g_rule);
	s_randomisation_count ++;
	g_rule.name = calloc(30, sizeof(char));
	sprintf(g_rule.name, "Rule %d", s_randomisation_count);
	g_rule.state_count = randint(2, 5);
	g_rule.state_l = calloc(g_rule.state_count, sizeof(state_t));
	for (int s = 0; s < g_rule.state_count; s ++)
	{
		g_rule.state_l[s].r = randint(0, 255);
		g_rule.state_l[s].g = randint(0, 255);
		g_rule.state_l[s].b = randint(0, 255);
		g_rule.state_l[s].behavior_count = randint(1, (randint(1, 4) == 1) ? 5 : 2);
		g_rule.state_l[s].behavior_l = calloc(g_rule.state_l[s].behavior_count, sizeof(behavior_t));
		for (int b = 0; b < g_rule.state_l[s].behavior_count; b ++)
		{
			g_rule.state_l[s].behavior_l[b].destination_state_id = randint(0, g_rule.state_count-1);
			g_rule.state_l[s].behavior_l[b].condition_count = randint(1, (randint(1, 4) == 1) ? 4 : 1);
			g_rule.state_l[s].behavior_l[b].condition_l = calloc(
				g_rule.state_l[s].behavior_l[b].condition_count, sizeof(condition_t));
			for (int c = 0; c < g_rule.state_l[s].behavior_l[b].condition_count; c ++)
			{
				g_rule.state_l[s].behavior_l[b].condition_l[c].shape = randint(0, 2);
				for (int n = 0; n < 9; n ++)
				{
					g_rule.state_l[s].behavior_l[b].condition_l[c].number[n] = randint(0, 1);
				}
				g_rule.state_l[s].behavior_l[b].condition_l[c].state_id = randint(0,
					g_rule.state_count-1);
			}
		}
	}
}

void randomize_rule_colors(void)
{
	for (int s = 0; s < g_rule.state_count; s ++)
	{
		g_rule.state_l[s].r = randint(0, 255);
		g_rule.state_l[s].g = randint(0, 255);
		g_rule.state_l[s].b = randint(0, 255);
	}
}

void save_rule(void)
{
	FILE* file = fopen("data/rules/save", "w");
	fprintf(file, "%s\n", g_rule.name);
	fprintf(file, "%d\n", g_rule.state_count);
	for (int s = 0; s < g_rule.state_count; s ++)
	{
		fprintf(file, "%d\n%d\n%d\n", g_rule.state_l[s].r, g_rule.state_l[s].g, g_rule.state_l[s].b);
		fprintf(file, "%d\n", g_rule.state_l[s].behavior_count);
		for (int b = 0; b < g_rule.state_l[s].behavior_count; b ++)
		{
			fprintf(file, "%d\n", g_rule.state_l[s].behavior_l[b].destination_state_id);
			fprintf(file, "%d\n", g_rule.state_l[s].behavior_l[b].condition_count);
			for (int c = 0; c < g_rule.state_l[s].behavior_l[b].condition_count; c ++)
			{
				fprintf(file, "%d\n", g_rule.state_l[s].behavior_l[b].condition_l[c].shape);
				for (int n = 0; n < 9; n ++)
				{
					fprintf(file, "%d\n", g_rule.state_l[s].behavior_l[b].condition_l[c].number[n]);
				}
				fprintf(file, "%d\n", g_rule.state_l[s].behavior_l[b].condition_l[c].state_id);
			}
		}
	}
	fprintf(file, "\n");
	fclose(file);
}

void load_rule(void)
{
	clear_rule(&g_rule);
	FILE* file = fopen("data/rules/save", "r");
	fscanf(file, "%s\n", g_rule.name);
	fscanf(file, "%d\n", &g_rule.state_count);
	g_rule.state_l = calloc(g_rule.state_count, sizeof(state_t));
	for (int s = 0; s < g_rule.state_count; s ++)
	{
		fscanf(file, "%d\n", &g_rule.state_l[s].r);
		fscanf(file, "%d\n", &g_rule.state_l[s].g);
		fscanf(file, "%d\n", &g_rule.state_l[s].b);
		fscanf(file, "%d\n", &g_rule.state_l[s].behavior_count);
		g_rule.state_l[s].behavior_l = calloc(g_rule.state_l[s].behavior_count, sizeof(behavior_t));
		for (int b = 0; b < g_rule.state_l[s].behavior_count; b ++)
		{
			fscanf(file, "%d\n", &g_rule.state_l[s].behavior_l[b].destination_state_id);
			fscanf(file, "%d\n", &g_rule.state_l[s].behavior_l[b].condition_count);
			g_rule.state_l[s].behavior_l[b].condition_l = calloc(
				g_rule.state_l[s].behavior_l[b].condition_count, sizeof(condition_t));
			for (int c = 0; c < g_rule.state_l[s].behavior_l[b].condition_count; c ++)
			{
				fscanf(file, "%d\n", (int*)(&g_rule.state_l[s].behavior_l[b].condition_l[c].shape));
				for (int n = 0; n < 9; n ++)
				{
					fscanf(file, "%d\n", &g_rule.state_l[s].behavior_l[b].condition_l[c].number[n]);
				}
				fscanf(file, "%d\n", &g_rule.state_l[s].behavior_l[b].condition_l[c].state_id);
			}
		}
	}
	fclose(file);
}
