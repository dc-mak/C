#include <stdio.h>
#include <assert.h> // assertions
#include <stdlib.h> // malloc and free
#include <string.h> // strdup - string duplication

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
	struct Person *who = malloc(sizeof(struct Person));
	assert (who != NULL);

	who->name = strdup(name);
	who->age  = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
{
	assert (who != NULL);

	free(who->name);
	free(who);
}

void Person_print(struct Person *who)
{
	printf("Name: %s\n\tAge: %d\n\tHeight: %d\n\tWeight: %d\n",
			who->name, who->age, who->height, who->weight);
}

void Person_bigPass(struct Person who)
{
	printf("Big pass by value whole struct as argument\n");
	Person_print(&who);
}

int main(int argc, char *argv[])
{
	struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	// print them out and where they are in memory
	printf("Joe is at memory location: %p\n", joe);
	Person_print(joe);

	printf("Frank is at memory location: %p\n", frank);
	Person_print(frank);

	// make everyone age 20 years and print them again
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	Person_print(frank);

	// on stack
	struct Person stack;
	stack.name = "Jim Bob";
	stack.age = 30;
	stack.height=89;
	stack.weight=160;
	Person_print(&stack);
	Person_bigPass(stack);

	// destroy both so we can clean up
	// Person_destroy(joe);
	Person_destroy(frank);
	Person_print(NULL);
	Person_destroy(NULL);

	return 0;
}

/* valgrind show a leak summary by default, for more:
 *    --leak-check=full --show-leak-kinds=all
 *
 * if you forget to free who->name then the string is "definitely lost"
 *
 * create something on stack by not using malloc
 */
