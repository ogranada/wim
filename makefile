
build:
	g++ -Wall -std=c++1z *.cpp -o main

debug-build:
	g++ -Wall -D__DEBUG__=1 -std=c++1z *.cpp -o main

.PHONY:
	build
