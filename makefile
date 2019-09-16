CXX = g++
CXXFLAGS = -Wall

compile: BusCompany.o Route.o driver.cpp
	$(CXX) $(CXXFLAGS) Route.o BusCompany.o driver.cpp -o optimize

BusCompany.o: Route.o BusCompany.cpp BusCompany.h
	$(CXX) $(CXXFLAGS) -c BusCompany.cpp

Route.o: Route.cpp Route.h
	$(CXX) $(CXXFLAGS) -c Route.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./optimize route.txt
