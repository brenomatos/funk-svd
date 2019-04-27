all: recommender

recommender: main.cpp
	g++ main.cpp -o recommender -O2 -Wall -Wextra

clean:
	rm recommender
