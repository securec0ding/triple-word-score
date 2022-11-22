all: scrabble

scrabble: scrabble.cpp
	g++ -g -fno-stack-protector -no-pie -o scrabble scrabble.cpp

clean:
	rm scrabble