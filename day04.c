#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	SEPARATOR " \n"

int main(int argc, char **argv) {
	char buff[256], *tok, buff2[256];
	int winning[128], copies[512], nowin, this_card, this_card2, cardno, i, j, q;
	int acc = 0;

	for (i = 0; i < 512; i++)
		copies[i] = 1;

	for (j = 0; fgets(buff, 256, stdin);) {
		this_card = this_card2 = 0;
		strcpy(buff2, buff);
		if (sscanf(buff, "Card %i:", &cardno) < 1)
			break;
		while (copies[cardno]) {
			nowin = 0;
			strcpy(buff2, buff);
			this_card = this_card2 = 0;
			strtok(buff2, SEPARATOR);
			tok = strtok(NULL, SEPARATOR);
			
			for (tok = strtok(NULL, SEPARATOR); *tok != '|'; tok = strtok(NULL, SEPARATOR))
				winning[nowin] = atoi(tok), nowin++;

			for (tok = strtok(NULL, SEPARATOR); tok; tok = strtok(NULL, SEPARATOR)) {
				q = atoi(tok);
				for (i = 0; i < nowin; i++)
					if (q == winning[i]) {
						this_card = (this_card) ? this_card * 2 : 1, this_card2++;
						break;
					}

			}

			for (i = 0; i < this_card2; i++)
				copies[cardno + i + 1]++;
			j++;
			copies[cardno]--;
		}
		
		acc += this_card;

	}

	printf("Total: %i %i\n", acc, j);
	return 0;
}
