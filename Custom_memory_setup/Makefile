CC = gcc
CFLAGS = -Wall -std=c18 -ggdb -I.

SOURCES = memory_manager.c bitmap.c
OBJECTS = $(SOURCES:.c=.o)
OUTPUT = prj1.a

all: $(OUTPUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(OUTPUT)
