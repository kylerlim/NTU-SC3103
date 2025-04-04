# Makefile structure according to Loke Yuan Ren
# Compiler and compiler flags

CC = gcc
CFLAGS = -Wall -O2

# Source files & object files
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))
INTERMEDIATES = $(patsubst %.c, %.i, $(SOURCES))
ASSEMBLERS = $(patsubst %.c, %.s, $(SOURCES))


# Debugger programme
DEBUGGER = helloworld.debug

# Profiler programme
PROFILER = helloworld.profiler

# Profiler profile
PROFILER_TXT = $(PROFILER).txt

# Executable
EXECUTABLE = helloworld.exe

# Phony targets
.PHONY = all clean process compile assemble link

all: process compile assemble link
	

# make process
process: CFLAGS += -E
process: $(INTERMEDIATES)

%.i: %.c
	$(CC) $(CFLAGS) $< -o $@

# make compile
compile: CFLAGS += -S
compile: $(ASSEMBLERS)



%.s: %.i
	$(CC) $(CFLAGS) $< -o $@


# make assemble
assemble: CFLAGS += -c
assemble: $(OBJECTS)



%.o: %.s
	$(CC) $(CFLAGS) $< -o $@

# make link
link: $(EXECUTABLE)
	rm -f $(INTERMEDIATES) $(ASSEMBLERS) $(OBJECTS)

# Explicit rule to build executable
$(EXECUTABLE):$(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

# make debug
debug:
	gcc -g -o $(DEBUGGER) $(SOURCES)
	gdb $(DEBUG)

# make profile
gprof:
	gcc -pg -o $(PROFILER) $(SOURCES)
	./$(PROFILER) -o gmon.out
	gprof $(PROFILER) gmon.out > $(PROFILER_TXT)

# Clean up generated files
clean:
	rm -f $(EXECUTABLE) $(INTERMEDIATES) $(ASSEMBLERS) $(OBJECTS) $(DEBUGGER) $(PROFILER) $(PROFILER_TXT) gmon.out
