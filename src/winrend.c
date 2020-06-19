
#include "winrend.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer* g_renderer = NULL;
SDL_Window*   g_window =   NULL;
TTF_Font*     g_font =     NULL;

void init_winrend(void)
{
	/* Create the window and the renderer */
	Uint32 window_flags =
		0 /* | SDL_WINDOW_ALLOW_HIGHDPI */;
	g_window = SDL_CreateWindow("CelAutGen", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 800, window_flags);
	g_renderer = SDL_CreateRenderer(g_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	SDL_SetRenderDrawBlendMode(g_renderer, SDL_BLENDMODE_BLEND);
	//SDL_GetRendererOutputSize(g_renderer, &g_w, &g_h);
	//SDL_ShowCursor(SDL_DISABLE);
	/* Load the font */
	g_font = TTF_OpenFont("assets/ubuntu-font-family-0.83/UbuntuMono-R.ttf", 20);
}

void close_winrend(void)
{
	/* Destroy what has been created */
	if (g_window != NULL)
	{
		SDL_DestroyWindow(g_window);
		g_window = NULL;
	}
	if (g_renderer != NULL)
	{
		SDL_DestroyRenderer(g_renderer);
		g_renderer = NULL;
	}
	if (g_font != NULL)
	{
		TTF_CloseFont(g_font);
		g_font = NULL;
	}
}

SDL_Texture* get_text_texture(char* text, int r, int g, int b)
{
	/* Turns string into texture */
	SDL_Color color = {.r = r, .g = g, .b = b, .a = 255};
	SDL_Surface* surface = TTF_RenderText_Blended(g_font, text, color);
	if (surface == NULL)
	{
		return NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
	if (texture == NULL)
	{
		return NULL;
	}
	SDL_FreeSurface(surface);
	return texture;
}

void draw_text(char* text, int r, int g, int b, int x, int y, int center_x)
{
	/* Draws text and clean up */
	SDL_Texture* text_texture = get_text_texture(text, r, g, b);
	SDL_Rect rect = {.y = y};
	SDL_QueryTexture(text_texture, NULL, NULL, &rect.w, &rect.h);
	rect.x = (center_x) ? x-rect.w/2 : x;
	SDL_RenderCopy(g_renderer, text_texture, NULL, &rect);
	SDL_DestroyTexture(text_texture);
}
