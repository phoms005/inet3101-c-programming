CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDLIBS = -lgdbm -lm

TARGET = billing
OBJECTS = main.o billing.o database.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDLIBS)

main.o: main.c billing.h database.h
	$(CC) $(CFLAGS) -c main.c

billing.o: billing.c billing.h database.h
	$(CC) $(CFLAGS) -c billing.c

database.o: database.c database.h
	$(CC) $(CFLAGS) -c database.c

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
