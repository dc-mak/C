#ifndef _ex22_h
#define _ex22_h

/* A static variable in a function keeps its value between invocations.
 * A static global variable or function is accessible to only the file it is
 * declared in.
 * You cannot use static for members of structure.
 */
struct State {
	int the_age;
	int the_size;
};

extern int EXTERNAL;

int get_age(struct State *state);

void set_age(struct State *state, int age);

// updates a static variable that's inside update_ratio
double *update_ratio(double new_ratio);

void print_size(struct State *state);

#endif
