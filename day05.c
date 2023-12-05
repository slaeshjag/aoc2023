#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define	MAX_TABLE	128

struct OffsetTable {
	int64_t		src_start;
	int64_t		dest_start;
	int64_t		len;
};

static int64_t _seed_list[256];
struct OffsetTable seed_to_soil[MAX_TABLE];
struct OffsetTable soil_to_fertilizer[MAX_TABLE];
struct OffsetTable fertilizer_to_water[MAX_TABLE];
struct OffsetTable water_to_light[MAX_TABLE];
struct OffsetTable light_to_temperature[MAX_TABLE];
struct OffsetTable temperature_to_humidity[MAX_TABLE];
struct OffsetTable humidity_to_location[MAX_TABLE];

int num_seeds;
int num_seedsoil, num_soilfert, num_fertwat, num_watlig, num_ligtemp, num_temphum, num_humloc;

void read_table(struct OffsetTable *tab, int *count) {
	int i;
	char buff[256];

	fgets(buff, 256, stdin);
	
	for (i = 0; fgets(buff, 256, stdin), sscanf(buff, "%li %li %li\n", &tab[i].dest_start, &tab[i].src_start, &tab[i].len) == 3; i++);
	*count = i;
	return;
}


void load_seeds(char *buff) {
	char *tok;

	tok = strtok(buff, " \n");
	for (tok = strtok(NULL, " \n"); tok; tok = strtok(NULL, " \n"), num_seeds++)
		sscanf(tok, "%li", &_seed_list[num_seeds]);
}


int compare_table(const void *s1, const void *s2) {
	const struct OffsetTable *o1 = s1, *o2 = s2;
	
	if (o1->src_start - o2->src_start < 0)
		return -1;
	if (o1->src_start - o2->src_start > 0)
		return 1;
	return 0;
}


int64_t table_lookup(int64_t key, struct OffsetTable *o, int table_len) {
	int i;

	for (i = 0; i < table_len; i++) {
		if (o[i].src_start > key)
			return key;
		if (o[i].src_start + o[i].len > key)
			return key - o[i].src_start + o[i].dest_start;
	}

	return key;
}


int main(int argc, char **argv) {
	char buff[256];
	int64_t min_seed = LLONG_MAX, min_seed_num = -1, min_seed2 = LLONG_MAX, min_seed_num2 = -1, i, j, q;

	fgets(buff, 256, stdin);
	load_seeds(buff);
	fgets(buff, 256, stdin);
	
	read_table(seed_to_soil, &num_seedsoil);
	read_table(soil_to_fertilizer, &num_soilfert);
	read_table(fertilizer_to_water, &num_fertwat);
	read_table(water_to_light, &num_watlig);
	read_table(light_to_temperature, &num_ligtemp);
	read_table(temperature_to_humidity, &num_temphum);
	read_table(humidity_to_location, &num_humloc);

	qsort(seed_to_soil, num_seedsoil, sizeof(struct OffsetTable), compare_table);
	qsort(soil_to_fertilizer, num_soilfert, sizeof(struct OffsetTable), compare_table);
	qsort(fertilizer_to_water, num_fertwat, sizeof(struct OffsetTable), compare_table);
	qsort(water_to_light, num_watlig, sizeof(struct OffsetTable), compare_table);
	qsort(light_to_temperature, num_ligtemp, sizeof(struct OffsetTable), compare_table);
	qsort(temperature_to_humidity, num_temphum, sizeof(struct OffsetTable), compare_table);
	qsort(humidity_to_location, num_humloc, sizeof(struct OffsetTable), compare_table);

	for (i = 0; i < num_seeds; i++) {
		q = table_lookup(_seed_list[i], seed_to_soil, num_seedsoil);
		q = table_lookup(q, soil_to_fertilizer, num_soilfert);
		q = table_lookup(q, fertilizer_to_water, num_fertwat);
		q = table_lookup(q, water_to_light, num_watlig);
		q = table_lookup(q, light_to_temperature, num_ligtemp);
		q = table_lookup(q, temperature_to_humidity, num_temphum);
		q = table_lookup(q, humidity_to_location, num_humloc);
		if (q < min_seed)
			min_seed_num = i, min_seed = q;
	}
	
	for (i = 0; i < num_seeds; i += 2) {
		for (j = _seed_list[i]; j < _seed_list[i] + _seed_list[i+1]; j++) {
			q = table_lookup(j, seed_to_soil, num_seedsoil);
			q = table_lookup(q, soil_to_fertilizer, num_soilfert);
			q = table_lookup(q, fertilizer_to_water, num_fertwat);
			q = table_lookup(q, water_to_light, num_watlig);
			q = table_lookup(q, light_to_temperature, num_ligtemp);
			q = table_lookup(q, temperature_to_humidity, num_temphum);
			q = table_lookup(q, humidity_to_location, num_humloc);
			if (q < min_seed2)
				min_seed_num2 = j, min_seed2 = q;
		}
	}

	printf("Seed %li: %li\n", _seed_list[min_seed_num], min_seed);
	printf("Seed %li: %li\n", min_seed_num2, min_seed2);
	return 0;
}

