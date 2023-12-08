#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Node {
	char		pos[16];
	struct Node	*left;
	char		left_txt[16];
	struct Node	*right;
	char		right_txt[16];
};

struct Node *g_list;
int g_lists;

void add_node(char *this, char *left, char *right) {
	int q;
	struct Node *n;

	q = g_lists++;
	g_list = realloc(g_list, sizeof(*g_list) * g_lists);
	n = &g_list[q];
	strcpy(n->pos, this);
	strcpy(n->left_txt, left);
	strcpy(n->right_txt, right);
}


struct Node *find_node(char *name) {
	int i;

	for (i = 0; i < g_lists; i++)
		if (!strcmp(g_list[i].pos, name))
			return &g_list[i];
	return NULL;
}


int find_length(struct Node *node, char *tape) {
	int i, n;

	for (n = 0;;) {
		for (i = 0; tape[i] == 'L' || tape[i] == 'R'; i++, n++) {
			if (node->pos[2] == 'Z') 
				return n;
			if (tape[i] == 'L')
				node = node->left;
			if (tape[i] == 'R')
				node = node->right;
		}
	}

}


int64_t find_lcd(int *arr, int len) {
	int64_t acc = 1;
	int i, j, end, flag;

	for (i = end = 0; i < len; i++)
		if (arr[i] > end)
			end = arr[i];

	for (i = 2; i < end; i++) {
		flag = 0;

		for (j = 0; j < len; j++) {
			if (!(arr[j] % i))
				flag = 1, arr[j] /= i;
		}

		if (flag)
			acc *= i, i = 1;
	}

	return acc;

}


int main(int argc, char **argv) {
	char tape[1024];
	char this[32], left[32], right[32];
	int i, w;
	int64_t w2;
	struct Node *pos;
	int lengths[32];
	int starting_nodes;

	fgets(tape, 1024, stdin);
	while (fscanf(stdin, "%s = (%[^, ], %[^)])\n", this, left, right) == 3)
		add_node(this, left, right);
	for (i = 0; i < g_lists; i++) {
		g_list[i].left = find_node(g_list[i].left_txt);
		g_list[i].right = find_node(g_list[i].right_txt);
	}

	pos = find_node("AAA");

	for (w = 0;;)
		for (i = 0; tape[i] == 'L' || tape[i] == 'R'; i++, w++) {
			if (!strcmp(pos->pos, "ZZZ"))
				goto done;
			if (tape[i] == 'L')
				pos = pos->left;
			if (tape[i] == 'R')
				pos = pos->right;
		}
done:
	
	for (i = starting_nodes = 0; i < g_lists; i++)
		if (g_list[i].pos[2] == 'A') {
			lengths[starting_nodes++] = find_length(&g_list[i], tape);
		}

	w2 = find_lcd(lengths, starting_nodes);
	
	printf("%i %li steps\n", w, w2);
	return 0;
}
