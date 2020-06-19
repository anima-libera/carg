
#include "random.h"
#include <time.h>

#define LCG_COUNT 1000
static unsigned int s_lcg_l[LCG_COUNT] = {0};
static int          s_lcg_cur          = 0;

void seed_random(unsigned int seed)
{
	for (int i = 0; i < LCG_COUNT; i ++)
	{
		s_lcg_l[i] = seed + 1007 * i;
	}
	s_lcg_cur = seed % LCG_COUNT;
}

void seed_timestamp_random(void)
{
	seed_random(time(NULL));
	s_lcg_cur = time(NULL) % LCG_COUNT;
}

int raw_random(void)
{
	s_lcg_l[s_lcg_cur] = (s_lcg_l[s_lcg_cur] * 1103515245 + 12345) % 2147483648;
	int ret = s_lcg_l[s_lcg_cur];
	s_lcg_cur = (s_lcg_cur + (ret & 0xff)) % LCG_COUNT;
	return ret >> 7;
}

int random_int(int a, int b)
{
	return raw_random() % (b-a+1) + a;
}

float random_float(float a, float b)
{
	return ((float)raw_random() / (float)RAW_RANDOM_MAX) * (b-a) + a;
}
