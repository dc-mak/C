#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scope_demo(int count)
{
	log_info("count is %d", count);

	if (count > 10) {
		int i = 100; // BAD! BUGS!

		log_info("count in this scope is %d", i);
	}

	debug("this");
	log_info("count is at exit: %d", count);
	count = 3000;
	log_info("count after assign: %d", count);

	// scope_demo(count);
}

void byRef(int *a) 
{
	*a = 5;
	log_info("by reference: %d", *a);
}

void byVal(int a)
{
	a = -6;
	log_info("by value: %d", a);
}

void val_ref()
{
	int a = 10;
	log_info("Original: %d", a);
	byRef(&a);
	log_info("After ref: %d", a);
	byVal(a);
	log_info("After val: %d", a);
}

int main(int argc, char *argv[])
{
	struct State s = {.the_size = 1000, .the_age = 37 };

	// test out THE_AGE accessors
	log_info("My name: %s, age: %d", MY_NAME, get_age(&s));

	// test out THE_SIZE of extern
	log_info("THE_SIZE is %d:", s.the_size);
	print_size(&s);

	s.the_size = 9;

	log_info("THE SIZE is now: %d", s.the_size);
	print_size(&s);

	// test the ratio function static
	log_info("Ratio at first: %f", *update_ratio(2.0));
	log_info("Ratio again: %f", *update_ratio(10.0));
	double *tmp = update_ratio(300.0);
	log_info("Ratio once more: %f", *tmp);
	log_info("Ratio address: %p", tmp);
	*tmp = 45.0;
	log_info("Ratio once more: %f", *tmp);

	// test the scope demo
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);

	log_info("count after calling scop_demo: %d", count);
	
	// extern
	log_info("external: %d", EXTERNAL);

	// test by value and by reference
	val_ref();
	return 0;
}
