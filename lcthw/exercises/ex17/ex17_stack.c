#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#define STACK_SIZE 100

struct Stack {
	int top;
	int s[STACK_SIZE];
};

bool Stack_empty(struct Stack *stack)
{
	return stack->top == 0;
}

int Stack_pop(struct Stack *stack)
{
	if (stack->top == -1) {
		printf("Stack Empty\n"); // ideally fprint(stderr, ...);
		exit(1);
	}

	return stack->s[stack->top--];
}

void Stack_push(struct Stack *stack, int push)
{
	if (stack->top == STACK_SIZE-1) {
		printf("Stack overflow\n"); // ideally fprint(stderr, ...);
		exit(1);
	}

	stack->s[++stack->top] = push;
}

void Stack_print(struct Stack *stack)
{
	if (stack->top != -1) {
		int i = 0;
		for (i = 0; i <= stack->top; i++) {
			printf("%d ", stack->s[i]);
		}

		printf("\n");
	} else {
		printf("-\n");
	}
}

int main(int argc, char *argv[]) 
{
	struct Stack s = {.top = -1 };

	Stack_push(&s, 3);
	Stack_push(&s, 9);
	Stack_push(&s, -1);
	Stack_push(&s, -5);

	printf("Top: %d\n", s.top);
	Stack_print(&s);

	Stack_pop(&s);
	Stack_pop(&s);
	Stack_pop(&s);
	Stack_pop(&s);

	printf("stack after pops: ");
	Stack_print(&s);
	Stack_pop(&s);
}
