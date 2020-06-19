
#ifndef __celautgen_winrend_header__
#define __celautgen_winrend_header__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Renderer* g_renderer;
extern SDL_Window*   g_window;
extern TTF_Font*     g_font;

void init_winrend(void);
void close_winrend(void);

SDL_Texture* get_text_texture(char* text, int r, int g, int b);
void draw_text(char* text, int r, int g, int b, int x, int y, int center_x);

#endif /* __celautgen_winrend_header__ */
