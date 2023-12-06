#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int64_t make_one(int64_t *arr, int64_t num) {
	int64_t i;
	char buff[256] = { 0 }, buff2[32];

	for (i = 0; i < num; i++) {
		sprintf(buff2, "%li", arr[i]);
		strcat(buff, buff2);
	}

	return atol(buff);
}


int main(int argc, char **argv) {
	int64_t rtime[4], rdist[4], rtime2, rdist2, num, i, j, acc, this_race, acc2;
	char buff[256];
	

	fgets(buff, 256, stdin), num = sscanf(buff, "Time: %li %li %li %li\n", &rtime[0], &rtime[1], &rtime[2], &rtime[3]);
	fgets(buff, 256, stdin), num = sscanf(buff, "Distance: %li %li %li %li\n", &rdist[0], &rdist[1], &rdist[2], &rdist[3]);
	rtime2 = make_one(rtime, num);
	rdist2 = make_one(rdist, num);
	acc = 1;
	acc2 = 0;

	for (i = 0; i < num; i++) {
		this_race = 0;
		for (j = 0; j < rtime[i]; j++)
			if ((rtime[i] - j) * j > rdist[i])
				this_race++;
		acc *= this_race;
	}
		
	for (j = 0; j < rtime2; j++)
		if ((rtime2 - j) * j > rdist2)
			acc2++;

	printf("Total: %li %li\n", acc, acc2);
	return 0;
}
