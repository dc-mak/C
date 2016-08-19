/* 2010, P3 Q6: Doubly-linked List using XOR'd pointers. */
/* Assume malloc works and not worry about error handling here. */

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// CRITICAL: for any Node pointers prev, curr, next,
//					curr->xor = (prev ^ next)

typedef struct Node {
	void *val;
	uintptr_t xor;
} Node;

typedef Node* List;

List create_list()
{
	return (List) malloc(sizeof(Node));
}

void init_list(List l, void *val)
{
	assert(l);
	printf("Init --  l: %p, val: %p\n", (void *) l, val);
	l->val = val;
	l->xor = NULL;	// (prev = NULL ^ next = NULL)
}

// Must be pointing to head/last of (non-empty) List
void insert(List *l, void *val)
{
	assert(*l);

	printf("Insr -- *l: %p, val: %p, *val: %s\n",
			(void *) *l, val, * (char **) val);

	List top = (List) malloc(sizeof(Node));
	top->val = val;
	top->xor = *l;		// (prev = NULL ^ next = *l)
	(*l)->xor ^= top;	// (prev = top  ^ next = *l->xor)
	*l = top;
}

// Must be pointing to head/last of (non-empty) List
void delete_top(List *l)
{
	assert(*l);
	// free((*l)->val);

	// We know: l->xor	  = next = (prev = NULL ^ next)
	//			next->xor = (prev = (*l) ^ next_next)
	// so for   next->xor = (prev = NULL ^ next_next)
	//					  =  next_next
	//					  = (prev = (*l) ^ next->xor)
	// undo the (*l) bits for a straight next_next pointer as needed.

	List next = (*l)->xor;
	if (next) next->xor ^= *l;
	*l = next;
}

typedef void (*process_cb)(void *);

// Must be pointing to head/last of (non-empty) List
void traverse(List l, process_cb f)
{
	assert(l);
	List prev = l;
	f(prev->val);
	List curr  = l->xor;

	if (!curr) return; // one element list
	List next = (List) ((uintptr_t) prev ^ (uintptr_t) curr->xor);
	while (prev != curr->xor) {
		f(curr->val);
		next = (List) ((uintptr_t) prev ^ (uintptr_t) curr->xor);
		prev = curr;
		curr = next;
	}

	// two element list, l = (l->xor)->xor,
	// curr is guaranteed but since prev = curr->xor, next = 0
	if (!next) {
		f(curr->val);
	} else {
		// > 2 element list
		f(next->val);
	}
}

void showStr(char **result) { printf("Out = %s\n", *result); }

int main()
{
	char *strings[6] = {"Hello,", "my", "name", "is", "Slim", "Shady"};
	List test = create_list();
	init_list(test, &strings[5]);
	for (int i = 4; i >= 0; i--) insert(&test, &strings[i]);
	traverse(test, (process_cb) &showStr);

	printf("-- After 3 deletions\n");
	delete_top(&test);
	delete_top(&test);
	delete_top(&test);
	traverse(test, (process_cb) &showStr);

	printf("-- Only one element\n");
	delete_top(&test);
	delete_top(&test);
	traverse(test, (process_cb) &showStr);

	printf("-- Fail non-empty assertion.\n");
	fflush(stdout);
	delete_top(&test);
	traverse(test, (process_cb) &showStr);
}
