
#ifndef __celautgen_random_header__
#define __celautgen_random_header__

void seed_random(unsigned int seed);
void seed_timestamp_random(void);

int raw_random(void);
#define RAW_RANDOM_MAX 16777215

int random_int(int a, int b);
float random_float(float a, float b);
#define randint random_int

#endif /* __celautgen_random_header__ */
