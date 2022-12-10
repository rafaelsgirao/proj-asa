CFLAGS = -std=c++11 -O3 -Wall -g

all: main

main: main.cpp
	g++ $(CFLAGS) main.cpp -o main -lm

clean:
	rm -f *.o main

fmt:
	clang-format -i main.cpp

run: main
	./main
