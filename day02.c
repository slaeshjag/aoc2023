#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
	char buff[512], *input, *segment, *segment_save, *token, *token_save, color[32];
	int game, possible, acc, acc2, num, mred, mgreen, mblue;

	for (acc = acc2 = 0; fgets(buff, 512, stdin); ) {
		if (sscanf(buff, "Game %i:", &game) < 1)
			continue;
		input = strchr(buff, ':') + 1;
		possible = 1;
		mgreen = mred = mblue = 0;

		for (segment = strtok_r(input, ";", &segment_save); segment; segment = strtok_r(NULL, ";", &segment_save)) {
			for (token = strtok_r(segment, ",", &token_save); token; token = strtok_r(NULL, ",", &token_save)) {
				if (sscanf(token, "%i %s", &num, color) < 2)
					continue;

				if (!strcmp(color, "red"))
					mred = (num > mred) ? num : mred;
				else if (!strcmp(color, "green"))
					mgreen = (num > mgreen) ? num : mgreen;
				else if (!strcmp(color, "blue"))
					mblue = (num > mblue) ? num : mblue;
			}

		}

		if (mblue > 14 || mgreen > 13 || mred > 12)
			possible = 0;

		if (possible)
			acc += game;
		acc2 += mred * mblue * mgreen;
	}

	printf("total: %i, %i\n", acc, acc2);
	return 0;
}
