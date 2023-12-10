#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define	MAP_W		256
#define	MAP_H		256

static char map[MAP_W * MAP_H];

int goes_left(char ch) {
	if (ch == '-')
		return 1;
	if (ch == '7')
		return 1;
	if (ch == 'J')
		return 1;
	return 0;
}


int goes_up(char ch) {
	if (ch == '|')
		return 1;
	if (ch == 'J')
		return 1;
	if (ch == 'L')
		return 1;
	return 0;
}


int goes_right(char ch) {
	if (ch == '-')
		return 1;
	if (ch == 'L')
		return 1;
	if (ch == 'F')
		return 1;
	return 0;
}


int goes_down(char ch) {
	if (ch == '|')
		return 1;
	if (ch == 'F')
		return 1;
	if (ch == '7')
		return 1;
	return 0;
}


int main(int argc, char **argv) {
	char buff[MAP_W], ch;
	int i, j, pos_start = 0, pos_last, pos, step, pos_new, inside, tiles, last_dir;

	for (i = 0; fgets(buff, MAP_W, stdin); i++)
		for (j = 0; j < MAP_W && isgraph(buff[j]); j++) {
			map[j + i * MAP_W] = buff[j];
			if (buff[j] == 'S')
				pos_start = j + i * MAP_W;
		}
	pos_last = pos_start;

	if (goes_right(map[pos_start - 1]))
		pos = pos_start - 1;
	else if (goes_down(map[pos_start - MAP_W]))
		pos = pos_start - MAP_W;
	else if (goes_left(map[pos_start + 1]))
		pos = pos_start + 1;
	else
		pos = pos_start + MAP_W;
	map[pos_start] |= 0x80;

	for (step = 1;; step++) {
		if ((map[pos] & 0x7F) == 'S')
			break;
		if (goes_left(map[pos]) && (pos - 1 != pos_last))
			pos_new = pos - 1;
		else if (goes_up(map[pos]) && (pos - MAP_W != pos_last))
			pos_new = pos - MAP_W;
		else if (goes_right(map[pos]) && (pos + 1 != pos_last))
			pos_new = pos + 1;
		else
			pos_new = pos + MAP_W;
		map[pos] |= 0x80;
		pos_last = pos;
		pos = pos_new;
	}

	printf("Result: %i (%i)\n", step / 2 + (step & 1), step);

	for (i = tiles = 0; i < MAP_H; i++) {
		for (j = inside = last_dir = 0; j < MAP_W; j++) {
			ch = map[i * MAP_W + j];
			if (ch & 0x80) {
				if ((ch & 0x7F) == '|')
					inside ^= 0x1;
				if ((ch & 0x7F) == '7' || (ch & 0x7F) == 'F') {
					if (last_dir == 1)
						last_dir = 0;
					else if (last_dir == 2)
						last_dir = 0, inside ^= 0x1;
					else
						last_dir = 1;
				}

				if ((ch & 0x7F) == 'J' || (ch & 0x7F) == 'L') {
					if (last_dir == 2)
						last_dir = 0;
					else if (last_dir == 1)
						last_dir = 0, inside ^= 0x1;
					else
						last_dir = 2;
				}
			} else if (ch != 0)  {
				tiles += !!inside;
			}
		}
	}

	printf("Result: %i\n", tiles);

	return 0;
}

