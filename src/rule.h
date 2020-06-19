
#ifndef __celautgen_rule_header__
#define __celautgen_rule_header__

typedef struct
{
	enum {PLUS_SHAPE = 0, CROSS_SHAPE = 1, SQUARE_SHAPE = 2} shape;
	int  number[9];
	int  state_id;
}
condition_t;

typedef struct
{
	int          destination_state_id;
	int          condition_count;
	condition_t* condition_l;
}
behavior_t;

typedef struct
{
	int         r, g, b;
	int         behavior_count;
	behavior_t* behavior_l;
}
state_t;

typedef struct
{
	char*    name;
	int      state_count;
	state_t* state_l;
}
rule_t;

extern rule_t g_rule;

void clear_state(state_t* state);
void clear_rule(rule_t* rule);
void randomize_rule(void);
void randomize_rule_colors(void);

void save_rule(void);
void load_rule(void);

#endif /* __celautgen_rule_header__ */
