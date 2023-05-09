CPPFLAGS = -O3 -std=c++20

main: clean functions 
	g++ $(CPPFLAGS) main.cpp functions.o -o prog
	rm functions.o

launch: cleanStud main
	./prog
	make clean

test: cleanStud speedTestCompile
	./speedTest
	make clean

speedTestCompile: clean functions
	g++ $(CPPFLAGS) speedTesting.cpp functions.o -o speedTest

functions:
	g++ $(CPPFLAGS) -c functions.cpp

unitTest: clean
	g++ -std=c++20 functions.cpp unitTest.cpp -lgtest -lgtest_main -pthread -o unitTest
	./unitTest

clean:
	rm -f *.o prog speedTest unitTest
	
cleanStud:
	rm -f studFail.txt studPass.txt
