CC=g++
CMP_FLAGS=-std=c++11 -Wextra -Wall -g
SIM_FLAGS=-lsimlib -lm

all: build

build:
	$(CC) $(CMP_FLAGS) -o ims ims.cpp $(SIM_FLAGS)

run:
	# todo

clean:
	rm -f ims