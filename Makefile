.PHONY: clean all

BINS = day01.elf day02.elf day03.elf day04.elf day05.elf day06.elf day07.elf day07b.elf day08.elf day09.elf \
	day10.elf

all: $(BINS)


%.elf: %.c
	$(CC) -Wall -O3 $< -o $@ 

clean:
	rm *.elf
