#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_next_value(int *val, int vals) {
	int predict[128], predictions, i;

	predictions = vals - 1;

	for (i = 1; i < vals; i++)
		predict[i - 1] = val[i] - val[i - 1];
	for (i = 0; i < predictions; i++)
		if (predict[i])
			break;
	return val[vals - 1] + ((i == predictions) ? 0 : find_next_value(predict, predictions));
}


int find_next_value2(int *val, int vals) {
	int predict[128] = { 0 }, predictions, i;

	predictions = vals - 1;

	for (i = 0; i < vals - 1; i++)
		predict[i] = val[i + 1] - val[i];
	for (i = 0; i < predictions; i++)
		if (predict[i])
			break;
	return val[0] - ((i == predictions) ? 0 : find_next_value2(predict, predictions));
}


int main(int argc, char **argv) {
	char buff[512], *next;
	int acc = 0, acc2 = 0, val[128], vals;

	while (fgets(buff, 512, stdin)) {
		vals = 0;
		for (next = strtok(buff, "\n "); next; next = strtok(NULL, "\n "))
			val[vals++] = atoi(next);
		acc += find_next_value(val, vals);
		acc2 += find_next_value2(val, vals);
	}

	printf("Result: %i %i\n", acc, acc2);
	return 0;
}
