
#ifndef __celautgen_grid_header__
#define __celautgen_grid_header__

extern int  g_grid_size;
extern int* g_grid_cur;
extern int* g_grid_next;
extern int  g_draw_every;

#define GCOORDS(x_, y_)     ((x_) + g_grid_size * (y_))
#define GCOORDSWARP(x_, y_) GCOORDS(((x_)+g_grid_size)%g_grid_size, ((y_)+g_grid_size)%g_grid_size)

void init_grid(void);
void close_grid(void);

void change_grid_size(int new_size);
void swap_cur_next_grid(void);
void draw_cur_grid(void);

void randomize_grid(void);
void verify_grid(void);

void run_grid(void);

#endif /* __celautgen_grid_header__ */
