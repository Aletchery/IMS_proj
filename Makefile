CC=g++
CMP_FLAGS=-std=c++11 -Wextra -Wall -g
SIM_FLAGS=-lsimlib -lm

all: build

build:
	$(CC) $(CMP_FLAGS) -o ims ims.cpp $(SIM_FLAGS)

run: build
	./ims -o result1.md -t "Referencny experiment" -s 2400 -c 60
	./ims -o result2.md -t "Experiment 1: Optimalne mnozstvo" -s 12000 -c 120
	./ims -o result3.md -t "Experiment 1: Overenie" -s 6200 -c 84.32
	./ims -o result4.md -t "Experiment 2: Zdvojnasobenie" -s 2400 -c 60 -K 2 -k 10 -l 12

clean:
	rm -f ims