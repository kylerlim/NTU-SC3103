# C Programming Makefile Tutorial

This `Makefile` helps automate the process of compiling, assembling, and linking C programs. It also includes steps for debugging and profiling.

## Available Make Commands

### `make`
Builds the project by running all steps in order:
1. **Preprocess**: Converts `.c` to `.i` files.
2. **Compile**: Converts `.i` to `.s` assembly files.
3. **Assemble**: Converts `.s` to `.o` object files.
4. **Link**: Links the object files into the final executable.

### `make process`
Runs the preprocessor (`gcc -E`), creating `.i` files from `.c` files.

### `make compile`
Compiles `.i` files into `.s` assembly files (`gcc -S`).

### `make assemble`
Assembles `.s` files into `.o` object files (`gcc -c`).

### `make link`
Links `.o` files into the final executable (`helloworld.exe`).

### `make debug`
Compiles the code with debugging information and runs the debugger:
```
gcc -g -o helloworld.debug $(SOURCES)
gdb helloworld.debug
```


### `make profile`
Profiles the code with gprof:

```
gcc -pg -o $(PROFILER) $(SOURCES)
./$(PROFILER) -o gmon.out
gprof $(PROFILER) gmon.out > $(PROFILER_TXT)
```
### `make clean`
Removes all generated files, including object files, assembly files, and executables.