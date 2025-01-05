CXX = g++
CXXFLAGS = -Wall -g
IODIR =../../browsersim_IO/

browsersim: NavigationEntry.o Browser.o Stack.o browsersim.cpp
	$(CXX) $(CXXFLAGS) NavigationEntry.o Browser.o Stack.o browsersim.cpp -o browsersim

NavigationEntry.o: NavigationEntry.h NavigationEntry.cpp
	$(CXX) $(CXXFLAGS) -c NavigationEntry.cpp

Browser.o: Browser.h Browser.cpp Stack.o NavigationEntry.o
	$(CXX) $(CXXFLAGS) -c Browser.cpp

Stack.o: Stack.cpp
	$(CXX) $(CXXFLAGS) -c Stack.cpp

##Use this when you want to test just your Queue
stest: Stack.o stack_test.cpp
	$(CXX) $(CXXFLAGS) Stack.o stack_test.cpp -o stest

##Use this when you want to valgrind your Queue tests
stest2:
	valgrind ./stest

clean:
	rm *.o*
	rm *~ 

run1:
	./browsersim browsersim_data1.txt

run2:
	./browsersim browsersim_data2.txt

run3:
	./browsersim browsersim_data3.txt

val1:
	valgrind ./browsersim browsersim_data1.txt

val2:
	valgrind ./browsersim browsersim_data2.txt

val3:
	valgrind ./browsersim browsersim_data3.txt

##Used for grading and testing
##Copies all test files into current directory
copy:
	cp $(IODIR)browsersim* .

submit:
	cp NavigationEntry.h NavigationEntry.cpp Browser.h Browser.cpp Stack.cpp browsersim.cpp ~/cs202proj/browsersim

