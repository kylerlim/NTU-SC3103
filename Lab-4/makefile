CC = gcc
CFLAGS = -lpthread

PROGRAMS = server client pthread1 pthread2 mutex_pthread

EXECUTABLES = $(addsuffix .exe, $(PROGRAMS))

# Default target
all: $(EXECUTABLES)

%.exe: %.c
	$(CC) -o $@ $< $(CFLAGS)

$(PROGRAMS): %: %.exe

# Clean rule
clean:
	rm -f $(EXECUTABLES)
