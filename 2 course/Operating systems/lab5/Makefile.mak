FLAGS = -g -O2 -pedantic -std=c11 -Wall -Werror

all: static1 static2 dynamic

static1: lib1 program1
        gcc $(FLAGS) lib1.o program1.o -o stat1 -lm

lib1: lib1.c
        gcc $(FLAGS) -c lib1.c -lm

static2: lib2 program1
        gcc $(FLAGS) lib2.o program1.o -o stat2 -lm

lib2: lib2.c
        gcc $(FLAGS) -c lib2.c -lm

program1: program1.c
        gcc $(FLAGS) -c program1.c

dynamic: program2 dynamic1 dynamic2
        gcc $(FLAGS) program2.o -o dyn3 -ldl

program2: program2.c
        gcc $(FLAGS) -c program2.c -ldl

dynamic1: lib1.c
        gcc $(FLAGS) -shared -o lib1.so -fPIC lib1.c -lm

dynamic2: lib2.c
        gcc $(FLAGS) -shared -o lib2.so -fPIC lib2.c -lm

clean:
        rm -rf *.o *.so stat1 stat2 dyn3




