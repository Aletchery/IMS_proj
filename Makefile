CC=g++
CMP_FLAGS=-std=c++11 -Wextra -Wall -g
SIM_FLAGS=-lsimlib -lm

all: build

build:
	$(CC) $(CMP_FLAGS) -o ims ims.cpp $(SIM_FLAGS)

run: build
	./ims -o referencia.md -t "Referencny experiment" -s 2400 -c 60
	./ims -o optimalne_mozstvo.md -t "Experiment 1: Optimalne mnozstvo" -s 12000 -c 120
	./ims -o overenie.md -t "Experiment 1: Overenie" -s 6200 -c 84.32
	./ims -o zdvojansobenie.md -t "Experiment 2: Zdvojnasobenie" -s 2400 -c 60 -K 2 -k 10 -l 12

clean:
	rm -f ims