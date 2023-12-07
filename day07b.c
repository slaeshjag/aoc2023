#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Hand {
	char		cards[6];
	int		bid;
};

struct Hand *g_hand;
int g_hands;

char card_point_lookup[256] = {
	['J'] = 1,
	['2'] = 2,
	['3'] = 3,
	['4'] = 4,
	['5'] = 5,
	['6'] = 6,
	['7'] = 7,
	['8'] = 8,
	['9'] = 9,
	['T'] = 10,
	['Q'] = 11,
	['K'] = 12,
	['A'] = 13
};


int is_five_of_a_kind(const struct Hand *h) {
	char ch = 0;
	int i, j;

	for (i = j = 0; i < 5; i++)
		if (h->cards[i] == 'J')
			j++;
	
	for (i = 0; h->cards[i] == 'J'; i++);
	ch = h->cards[i];

	for (i = 0; i < 5; i++) {
		if (h->cards[i] == 'J')
			continue;
		if (h->cards[i] != ch)
			break;
	}
	
	return i == 5;
}


int is_four_of_a_kind(const struct Hand *h) {
	char ch1 = 0, ch2 = 0;
	int i, c1, c2, j;

	for (i = 0; h->cards[i] == 'J'; i++);
	ch1 = h->cards[i];

	for (i = j = 0; i < 5; i++)
		if (h->cards[i] == 'J')
			j++;

	for (i = c1 = c2 = 0; i < 5; i++) {
		if (h->cards[i] == 'J')
			continue;
		if (h->cards[i] == ch1)
			c1++;
		else if (!c2 || ch2 == h->cards[i])
			ch2 = h->cards[i], c2++;
		else
			return 0;
	}

	return (c1 + j == 4) || (c2 + j == 4);
}


int is_full_house(const struct Hand *h) {
	char ch1 = 0, ch2 = 0;
	int i, j, c1, c2;

	for (i = 0; h->cards[i] == 'J'; i++);
	ch1 = h->cards[i];
	
	for (i = j = 0; i < 5; i++)
		if (h->cards[i] == 'J')
			j++;

	for (i = c1 = c2 = 0; i < 5; i++) {
		if (h->cards[i] == 'J')
			continue;
		if (h->cards[i] == ch1)
			c1++;
		else if ((!c2 || ch2 == h->cards[i]) && h->cards[i] != 'J')
			ch2 = h->cards[i], c2++;
		else if (h->cards[i] == 'J')
			j++;
		else
			return 0;
	}

	return (c1 + j == 3) || (c2 + j == 3);
}


int is_three_of_a_kind(const struct Hand *h) {
	char ch1 = 0, ch2 = 0, ch3 = 0;
	int i, j, c1, c2, c3;

	for (i = 0; h->cards[i] == 'J'; i++);
	ch1 = h->cards[i];
	
	for (i = j = 0; i < 5; i++)
		if (h->cards[i] == 'J')
			j++;

	for (i = c1 = c2 = c3 = 0; i < 5; i++) {
		if (h->cards[i] == 'J')
			continue;
		if (h->cards[i] == ch1)
			c1++;
		else if (!c2 || ch2 == h->cards[i])
			ch2 = h->cards[i], c2++;
		else if (!c3 || ch3 == h->cards[i])
			ch3 = h->cards[i], c3++;
		else
			return 0;
	}

	return (c1 + j == 3) || (c2 + j == 3) || (c3 + j == 3);
}


int is_two_pairs(const struct Hand *h) {
	char ch1 = 0, ch2 = 0, ch3 = 0;
	int i, j, c1, c2, c3;

	for (i = 0; h->cards[i] == 'J'; i++);
	ch1 = h->cards[i];
	
	for (i = j = 0; i < 5; i++)
		if (h->cards[i] == 'J')
			j++;

	for (i = c1 = c2 = c3 = 0; i < 5; i++) {
		if (h->cards[i] == 'J')
			continue;
		if (h->cards[i] == ch1)
			c1++;
		else if (!c2 || ch2 == h->cards[i])
			ch2 = h->cards[i], c2++;
		else if (!c3 || ch3 == h->cards[i])
			ch3 = h->cards[i], c3++;
		else
			return 0;
	}

	if (j) {
		if (c1 == 1)
			c1++;
		else if (c2 == 1)
			c2++;
		else if (c3 == 1)
			c3++;
	}

	return (c1 == 2 && c2 == 2) || (c1 == 2 && c3 == 2) || (c2 == 2 && c3 == 2);
}


int is_one_pair(const struct Hand *h) {
	char ch1 = 0, ch2 = 0, ch3 = 0, ch4 = 0;
	int i, j, c1, c2, c3, c4;

	for (i = 0; h->cards[i] == 'J'; i++);
	ch1 = h->cards[i];
	
	for (i = j = 0; i < 5; i++)
		if (h->cards[i] == 'J')
			j++;

	for (i = c1 = c2 = c3 = c4 = 0; i < 5; i++) {
		if (h->cards[i] == 'J')
			continue;
		if (h->cards[i] == ch1)
			c1++;
		else if (!c2 || h->cards[i] == ch2)
			ch2 = h->cards[i], c2++;
		else if (!c3 || h->cards[i] == ch3)
			ch3 = h->cards[i], c3++;
		else if (!c4 || h->cards[i] == ch4)
			ch4 = h->cards[i], c4++;
		else
			return 0;
	}

	return (c1 + j == 2) || (c2 + j == 2) || (c3 + j == 2) || (c4 + j == 2);
}


int compare_cards(const struct Hand *h1, const struct Hand *h2) {
	int i;

	for (i = 0; i < 5; i++)
		if (h1->cards[i] != h2->cards[i])
			return card_point_lookup[(unsigned char) h1->cards[i]] - card_point_lookup[(unsigned char)h2->cards[i]];
	return 0;
}


int hand_compare(const void *s1, const void *s2) {
	const struct Hand *h1 = s1, *h2 = s2;

	if (is_five_of_a_kind(h1) && !is_five_of_a_kind(h2))
		return 1;
	if (!is_five_of_a_kind(h1) && is_five_of_a_kind(h2))
		return -1;
	if (is_five_of_a_kind(h1) && is_five_of_a_kind(h2))
		return compare_cards(h1, h2);
	
	if (is_four_of_a_kind(h1) && !is_four_of_a_kind(h2))
		return 1;
	if (!is_four_of_a_kind(h1) && is_four_of_a_kind(h2))
		return -1;
	if (is_four_of_a_kind(h1) && is_four_of_a_kind(h2))
		return compare_cards(h1, h2);

	if (is_full_house(h1) && !is_full_house(h2))
		return 1;
	if (!is_full_house(h1) && is_full_house(h2))
		return -1;
	if (is_full_house(h1) && is_full_house(h2))
		return compare_cards(h1, h2);
	
	if (is_three_of_a_kind(h1) && !is_three_of_a_kind(h2))
		return 1;
	if (!is_three_of_a_kind(h1) && is_three_of_a_kind(h2))
		return -1;
	if (is_three_of_a_kind(h1) && is_three_of_a_kind(h2))
		return compare_cards(h1, h2);
	
	if (is_two_pairs(h1) && !is_two_pairs(h2))
		return 1;
	if (!is_two_pairs(h1) && is_two_pairs(h2))
		return -1;
	if (is_two_pairs(h1) && is_two_pairs(h2))
		return compare_cards(h1, h2);
	
	if (is_one_pair(h1) && !is_one_pair(h2))
		return 1;
	if (!is_one_pair(h1) && is_one_pair(h2))
		return -1;
	if (is_one_pair(h1) && is_one_pair(h2))
		return compare_cards(h1, h2);
	
	return compare_cards(h1, h2);
}


int read_hand() {
	struct Hand h;
	int n;

	if (fscanf(stdin, "%s %i\n", h.cards, &h.bid) < 2)
		return 0;
	n = g_hands++;
	g_hand = realloc(g_hand, sizeof(*g_hand) * g_hands);
	g_hand[n] = h;
	return 1;
}


int main(int argc, char **argv) {
	int i;
	int64_t acc = 0;

	while (read_hand());

	qsort(g_hand, g_hands, sizeof(*g_hand), hand_compare);
	for (i = 0; i < g_hands; i++)
		acc += g_hand[i].bid * (i + 1);
	
	printf("Total: %li\n", acc);

	return 0;
}
