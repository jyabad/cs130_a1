main: main.cpp
	g++ -g -Wall -std=c++11 -o main main.cpp -I/usr/local/opt/openssl@1.1/include -L/usr/local/opt/openssl@1.1/lib -lcrypto
test: main.o
	./main
