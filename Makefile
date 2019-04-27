all: recommender

recommender: matrix.o
	g++ main.cpp   matrix.o -o recommender -O3 -Wall -Wextra

matrix.o: matrix.cpp
	g++ matrix.cpp -c -o matrix.o -O3 -Wall -Wextra

clean:
	rm recommender
	rm matrix.o
