all: compile link run

compile:
	g++ -I src/include -c mainkian.cpp -static-libgcc -static-libstdc++
link:
	g++ mainkian.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system
run:
	./main