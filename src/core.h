
#ifndef __celautgen_core_header__
#define __celautgen_core_header__

extern int g_core_loop_running;
extern int g_ticks_per_step;

void core_init_everything(void);
void core_close_everything(void);

void core_loop(void);

#endif /* __celautgen_core_header__ */
