#include <stdio.h>
#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

/* extern */ int EXTERNAL = 42;

int get_age(struct State *state) { return state->the_age; }

/* All valid for constant pointer to constant structure (I think)
 * const struct State const *
 * struct State const const *
 * struct State const * const
 *
 * struct State const * = pointer to constant structure
 * struct State * const = constant pointer to structure
 */
void set_age(struct State * const state, int age) { state->the_age = age; }

double *update_ratio(const double new_ratio)
{
	static double old_ratio;
	old_ratio = new_ratio;
	return &old_ratio;
}

void print_size(struct State *state)
{
	log_info("I think size is: %d", state->the_size);
}
