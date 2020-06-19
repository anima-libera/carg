
#include "core.h"

#include "rule.h"

int main(int argc, char** argv)
{
	/* Parse command line arguments */
	if (argc > 1)
	{
		for (int i = 1; i < argc; i ++)
		{
			if (argv[i][0] == '-')
			{
				; /* TODO */
			}
			else
			{
				; /* TODO */
			}
		}
	}

	/* Core init, loop and close */
	core_init_everything();
	#if 0
	{
		/* TEST TO DELETE */
		g_rule.state_count = 2;
		state_t test_state_l[2] = {0};
		g_rule.state_l = test_state_l;
		test_state_l[0].r = 255;
		test_state_l[0].g = 255;
		test_state_l[0].b = 255;
		test_state_l[0].behavior_count = 1;
		behavior_t test_s0_behavior_l[1] = {0};
		test_state_l[0].behavior_l = test_s0_behavior_l;
		test_s0_behavior_l[0].condition_count = 1;
		condition_t test_s0_behavior_condition_l[1] = {0};
		test_s0_behavior_l[0].condition_l = test_s0_behavior_condition_l;
		test_s0_behavior_condition_l[0].shape = SQUARE_SHAPE;
		test_s0_behavior_condition_l[0].number[3] = 1;
		test_s0_behavior_condition_l[0].state_id = 1;
		test_s0_behavior_l[0].destination_state_id = 1;
		test_state_l[1].r = 0;
		test_state_l[1].g = 0;
		test_state_l[1].b = 255;
		test_state_l[1].behavior_count = 1;
		behavior_t test_s1_behavior_l[1] = {0};
		test_state_l[1].behavior_l = test_s1_behavior_l;
		test_s1_behavior_l[0].condition_count = 1;
		condition_t test_s1_behavior_condition_l[1] = {0};
		test_s1_behavior_l[0].condition_l = test_s1_behavior_condition_l;
		test_s1_behavior_condition_l[0].shape = SQUARE_SHAPE;
		test_s1_behavior_condition_l[0].number[0] = 1;
		test_s1_behavior_condition_l[0].number[1] = 1;
		test_s1_behavior_condition_l[0].number[4] = 1;
		test_s1_behavior_condition_l[0].number[5] = 1;
		test_s1_behavior_condition_l[0].number[6] = 1;
		test_s1_behavior_condition_l[0].number[7] = 1;
		test_s1_behavior_condition_l[0].number[8] = 1;
		test_s1_behavior_condition_l[0].state_id = 1;
		test_s1_behavior_l[0].destination_state_id = 0;
	}
	#endif
	{
		randomize_rule();
	}
	core_loop();
	core_close_everything();

	/* Bed time */
	return 0;
}
