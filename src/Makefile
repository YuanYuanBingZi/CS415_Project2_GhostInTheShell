CC = gcc
CFLAGS = -Wall
TARGETS = part1 part2 part3 part4 iobound cpubound

all: $(TARGETS)

part1: part1.c string_parser.c string_parser.h
	$(CC) $(CFLAGS) -o part1 part1.c string_parser.c

part2: part2.c string_parser.c string_parser.h
	$(CC) $(CFLAGS) -o part2 part2.c string_parser.c

part3: part3.c string_parser.c string_parser.h
	$(CC) $(CFLAGS) -o part3 part3.c string_parser.c

part4: part4.c string_parser.c string_parser.h
	$(CC) $(CFLAGS) -o part4 part4.c string_parser.c

iobound: iobound.c
	$(CC) $(CFLAGS) -o iobound iobound.c

cpubound: cpubound.c
	$(CC) $(CFLAGS) -o cpubound cpubound.c

clean:
	rm -f $(TARGETS)
