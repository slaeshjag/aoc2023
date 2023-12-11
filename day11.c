#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define	SPACE_W		256
#define	SPACE_H		256
#define	MAX_GALAXY	10000

int g_space[SPACE_W * SPACE_H];
int g_galaxy[MAX_GALAXY];
int g_galaxies;
int w_expansion[SPACE_W], h_expansion[SPACE_H];

void read_space() {
	int i, j, flag, q;
	char buff[256];

	for (i = q = 0; fgets(buff, 256, stdin); i++) {
		for (j = flag = 0; buff[j] != '\n' && buff[j]; j++) {
			if (buff[j] == '#')
				g_space[i*SPACE_W + j] = 1, flag = 1, q++;
		}
		
		if (!flag)
			h_expansion[i] = 1, i++;
	}

	printf("%i galaxies (%i)\n", q, i);
}


void expand_col() {
	int i, j, c, flag;
	int space2[SPACE_W * SPACE_H] = { 0 }; // the sequel

	for (i = c = 0; c < SPACE_W; i++, c++) {
		for (j = flag = 0; j < SPACE_H; j++)
			if (g_space[i + j * SPACE_W])
				space2[c + j * SPACE_W] = 1, flag = 1;
		if (!flag)
			w_expansion[c] = 1, c++;
	}

	memcpy(g_space, space2, sizeof(*g_space) * SPACE_W * SPACE_H);
}


void find_galaxies() {
	int i;

	for (i = 0; i < SPACE_W * SPACE_H; i++)
		if (g_space[i])
			g_galaxy[g_galaxies++] = i;
}


int calculate_distance() {
	int acc, i, j, x, y, q;


	for (i = acc = q = 0; i < g_galaxies; i++)
		for (j = i + 1; j < g_galaxies; j++) {
			x = abs((g_galaxy[i] % SPACE_W) - (g_galaxy[j] % SPACE_W));
			y = abs((g_galaxy[i] / SPACE_W) - (g_galaxy[j] / SPACE_W));
			acc += x + y;
			q++;
		}
	return acc;
}


int voids_w(int x, int x2) {
	int i, q;

	if (x > x2)
		q = x2, x2 = x, x = q;

	for (q = 0, i = x; i < x2; i++)
		if (w_expansion[i])
			q++;
	return q;
}


int voids_h(int y, int y2) {
	int i, q;

	if (y > y2)
		q = y2, y2 = y, y = q;

	for (q = 0, i = y; i < y2; i++)
		if (h_expansion[i])
			q++;
	return q;
}


int64_t calculate_distance2() {
	int64_t acc, i, j, x, y;


	for (i = acc = 0; i < g_galaxies; i++)
		for (j = i + 1; j < g_galaxies; j++) {
			x = abs((g_galaxy[i] % SPACE_W) - (g_galaxy[j] % SPACE_W));
			y = abs((g_galaxy[i] / SPACE_W) - (g_galaxy[j] / SPACE_W));
			x += 999998L * voids_w(g_galaxy[i] % SPACE_W, g_galaxy[j] % SPACE_W);
			y += 999998L * voids_h(g_galaxy[i] / SPACE_W, g_galaxy[j] / SPACE_W);
			acc += x + y;
		}
	return acc;
}


int main(int argc, char **argv) {
	read_space();
	expand_col();
	find_galaxies();
	printf("Result: %i\n", calculate_distance());
	printf("Result: %li\n", calculate_distance2());

	return 0;
}
