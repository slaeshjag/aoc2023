#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *words[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int main(int argc, char **argv) {
	int acc, accb, num1, num1b, num2, num2b, i, j;
	char buff[128], *ptr;
	for (i = acc = accb = 0; !feof(stdin); i++) {
		*buff = 0;
		num1 = num1b = num2 = num2b = -1;
		fgets(buff, 128, stdin), buff[127] = 0;
		for (ptr = buff; *ptr; ptr++) {
			if (isdigit(*ptr))
				num2 = num2b = *ptr - '0';
			else
				for (j = 1; j < 10; j++)
					if (!strncmp(ptr, words[j], strlen(words[j]))) {
						num2b = j;
						break;
					}

			if (num1 < 0)
				num1 = num2 * 10;
			if (num1b < 0)
				num1b = num2b * 10;
		}
		
		if (num1 < 0)
			break;
		acc += (num1 + num2);
		accb += (num1b + num2b);
	}

	printf("Total: %i %i\n", acc, accb);
	return 0;
}
