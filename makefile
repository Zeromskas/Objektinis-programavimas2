CPPFLAGS = -O3 -std=c++20

main: cleanStud prog
	./prog

prog: clean functions 
	g++ $(CPPFLAGS) main.cpp functions.o -o prog

test: cleanStud testCompile
	./test

testCompile: clean functions
	g++ $(CPPFLAGS) testing.cpp functions.o -o test

test2: cleanStud test2Compile
	./test2

test2Compile: clean functions
	g++ $(CPPFLAGS) testing2.cpp functions.o -o test2

functions:
	g++ $(CPPFLAGS) -c functions.cpp

clean:
	rm -f *.o main test test2
	
cleanStud:
	rm -f studFail.txt studPass.txt