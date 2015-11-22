#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// To get rid of bool, we use root of type **tree, and check whether or not
// *root is NULL (Lf) or not (Br) and in recursive calls, pass &(*root)->left.

/*
   Alternatively, the following would work

	   typedef struct branch { <current tree def> } branch;
	   typedef struct tree { branch *br; };

  and now that's in the type system :-)

  But really, you just want to use an array for a heap.

*/

typedef struct tree {
	bool Lf;
	int val;
	struct tree *left;
	struct tree *right;
} tree;

void insert(const int val, tree *const t)
{
	if (t->Lf) {

		t->Lf = false;
		t->val = val;
		t->left = calloc(1, sizeof(tree));
		t->left->Lf = true;
		t->right = calloc(1, sizeof(tree));
		t->right->Lf = true;

	} else {

		int min;
		int new_val;
		if (val < t->val) {
			min = val;
			new_val = t->val;
		} else {
			min = t->val;
			new_val = val;
		}

		insert (new_val, t->right);
		t->val = min;
		tree *const tmp = t->left;
		t->left = t->right;
		t->right = tmp;
	}
}

void heapify(int *const arr, const int len, tree *const t)
{
	for (int i = 0; i < len; i++) insert(arr[i], t);
}

void pretty_print(tree *const t, const int indent, const int inc)
{
	if (!t->Lf) {

		pretty_print(t->left, indent + inc, inc);
		for (int i = 0; i < indent; i++)
			printf(" ");
		printf("%d\n", t->val);
		pretty_print(t->right, indent + inc, inc);

	}
}

int main()
{
	int check[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	const tree t = {.Lf=true, .val=0, .left=NULL, .right=NULL};
	pretty_print((tree *const) &t, 0, 4);
	heapify(&check[0], 15, (tree *const) &t);
	pretty_print((tree *const) &t, 0, 4);
}
