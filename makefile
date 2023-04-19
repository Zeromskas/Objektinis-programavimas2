CPPFLAGS = -O3 -std=c++20

main: cleanStud prog
	./prog
	make clean

prog: clean functions 
	g++ $(CPPFLAGS) main.cpp functions.o -o prog

test: cleanStud testCompile
	./test
	make clean

testCompile: clean functions
	g++ $(CPPFLAGS) testing.cpp functions.o -o test

functions:
	g++ $(CPPFLAGS) -c functions.cpp

clean:
	rm -f *.o prog test test2
	
cleanStud:
	rm -f studFail.txt studPass.txt