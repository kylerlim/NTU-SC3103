# A Tutorial to C Programming with Makefiles

This repository contains various C programs demonstrating threading and socket programming, along with a powerful `Makefile` to build them easily.

## Build Instructions

### Requirements
- GCC compiler (`gcc`)
- macOS/Linux (tested on macOS)
- Make utility

### To build all executables:
```
make all
```

### To build all executables:
```
make pthread1       # Builds pthread1.exe
make pthread2       # Builds pthread2.exe
make mutex_pthread  # Builds mutex_pthread.exe
make server         # Builds server.exe
make client         # Builds client.exe

```

### To clean up all generated executables:
```
make clean
```

## Program Descriptions

- pthread1	Demonstrates basic thread creation in C
- pthread2	Demonstrates a race condition using shared data
- mutex_pthread	Demonstrates how to prevent race conditions using mutexes
- server	A basic server implementation using sockets
```
./server.exe [port_num]
```
- client	A basic client implementation to connect to the server
```
./client.exe [host_addr] [port_num]
```
