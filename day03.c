#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH		256

static char _linebuff[3][LINE_LENGTH];
static int _cur_line;
static int _last_line;
static int _acc, _acc2;
static int _gear1, _gear2;

int check_symbol(int pos) {
	int ch;
	int j, k, flag = 0;

	for (j = pos - 1; j < pos + 2; j++) {
		if (j < 0)
			continue;
		for (k = 0; k < 3; k++) {
			ch = _linebuff[k][j];
			if (ch != '.' && !isdigit(ch) && isgraph(ch))
				flag = 1;
		}
	}

	return flag;
}


int gear_num(int g) {
	if (g == 0)
		return _gear1 = _gear2 = 0;
	else {
		if (!_gear1)
			return _gear1 = g, 0;
		return _gear2 = g, _gear1 * _gear2;
	}
}


int gear_number(int line, int col) {
	int i, q;

	if (line == -1 && col == -1)
		return gear_num(0);
	for (i = col; i >= 0 && isdigit(_linebuff[line][i]); i--);
	if (!isdigit(_linebuff[line][i]))
		i++;
	q = atoi(&_linebuff[line][i]);
	return gear_num(q);
}


void find_gears(int cl) {
	int i, nl, pl, g;

	nl = (cl + 1) % 3;
	pl = (cl + 2) % 3;

	for (i = 0; _linebuff[cl][i]; i++) {
		if (_linebuff[cl][i] != '*')
			continue;
	
		g = gear_number(-1, -1);
		if (isdigit(_linebuff[pl][i]))
			g = gear_number(pl, i);
		else {
			if (i > 0 && isdigit(_linebuff[pl][i-1]))
				g = gear_number(pl, i-1);
			if (isdigit(_linebuff[pl][i+1]))
				g = gear_number(pl, i+1);
		}

		if (i > 0 && isdigit(_linebuff[cl][i-1]))
			g = gear_number(cl, i-1);
		if (isdigit(_linebuff[cl][i+1]))
			g = gear_number(cl, i+1);

		if (isdigit(_linebuff[nl][i]))
			g = gear_number(nl, i);
		else {
			if (i > 0 && isdigit(_linebuff[nl][i-1]))
				g = gear_number(nl, i-1);
			if (isdigit(_linebuff[nl][i+1]))
				g = gear_number(nl, i+1);
		}

		if (g)
			_acc2 += g;

	}
}


void check_line() {
	int i, j, cl, flag;
	char numbuff[32];
		
	cl = _cur_line % 3;

	for (i = 0; _linebuff[cl][i]; i++) {
		if (!isdigit(_linebuff[cl][i]))
			continue;
		flag = 0;
		for (j = 0; isdigit(_linebuff[cl][i + j]); j++) {
			numbuff[j] = _linebuff[cl][i + j];
			flag |= check_symbol(i + j);
		}

		numbuff[j] = 0;
		if (flag)
			_acc += atoi(numbuff);

		i += j;
	}

	find_gears(cl);
	_cur_line++;
}


int main(int argc, char **argv) {

	fgets(_linebuff[_last_line++], LINE_LENGTH, stdin);
	fgets(_linebuff[_last_line++], LINE_LENGTH, stdin);
	memset(_linebuff[_last_line], 0, LINE_LENGTH);

	while (!feof(stdin)) {
		check_line();
		memset(_linebuff[_last_line % 3], 0, LINE_LENGTH);

		if ((fgets(_linebuff[_last_line % 3], LINE_LENGTH, stdin)))
			_last_line++;
		else
			break;

	}

	check_line();
	printf("Total: %i %i\n", _acc, _acc2);
}
