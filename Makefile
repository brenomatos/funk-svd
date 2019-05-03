all: recommender

recommender: matrix.o svd.o
	g++ -std=c++11 main.cpp matrix.o svd.o -g -o recommender -O2

svd.o: svd.cpp
	g++ -std=c++11 svd.cpp -g -c -o svd.o -O2

matrix.o: matrix.cpp
	g++ -std=c++11 matrix.cpp -g -c -o matrix.o -O2

clean:
	rm recommender
	rm matrix.o
	rm svd.o
