all: recommender

recommender: matrix.o svd.o
	g++ -std=c++11 main.cpp matrix.o svd.o -g -o recommender -Ofast

svd.o: svd.cpp
	g++ -std=c++11 svd.cpp -g -c -o svd.o -Ofast

matrix.o: matrix.cpp
	g++ -std=c++11 matrix.cpp -g -c -o matrix.o -Ofast

clean:
	rm recommender
	rm matrix.o
	rm svd.o
