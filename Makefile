
CC = gcc
CFLAGS = -Wall -g
OBJS = main.o bloom_filter.o skip_list.o records.o

vaccinationMonitor: $(OBJS)
	$(CC) $(CFLAGS) -o vaccinationMonitor $(OBJS)

main.o: main.c records.h
	$(CC) $(CFLAGS) -c main.c

bloom_filter.o: bloom_filter.c bloom_filter.h structures.h
	$(CC) $(CFLAGS) -c bloom_filter.c

skip_list.o: skip_list.c skip_list.h structures.h
	$(CC) $(CFLAGS) -c skip_list.c

records.o: records.c records.h bloom_filter.h skip_list.h structures.h
	$(CC) $(CFLAGS) -c records.c

clean:
	rm -f *.o vaccinationMonitor
