#include "BusCompany.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

string END = "End Route";

// default constructor (should not be called)
BusCompany::BusCompany(){

	// initialize route
	m_newRoute = new Route();

}


// constructor with file
BusCompany::BusCompany(string fileName){
	
	// initialize route, get stops and display menu
	m_newRoute = new Route();
	ReadFile(fileName);
	MainMenu();

}


// destructor
BusCompany::~BusCompany(){

	// clear all the routes
	for(unsigned int i = 0; i < m_routes.size(); i++){

		m_routes.at(i)->Clear();

	}

}


// read stops from file
void BusCompany::ReadFile(string fileName){

	// open file for reading
	fstream file(fileName);

	//initialize necessary variables
	string name, newLine;
	int location, riders, cost;
	
	//loop through lines in file
	while(getline(file, name, ',')){

		// when still in a route
		if(name != "End Route"){

			// read in rest of the variables and remove newline character
			file >> location >> riders >> cost;
			getline(file, newLine);

			m_newRoute->InsertAt(name, location, riders, cost);

		} else {

			//remove newline character
			getline(file, newLine);

			// end of route, add route to list and reinitialize
			m_routes.push_back(m_newRoute);
			cout << "Route " << m_routes.size() << " loaded with " << m_newRoute->GetSize() << " stops" << endl;
			m_newRoute = new Route();

		}

	}

	// close file
	file.close();

}


// display menu
void BusCompany::MainMenu(){

	int choice = 0;

	cout << "Welcome to the UMBC Transit Simulator!" << endl << endl;

	// continue until user quits
	while(choice != 4){

		// display choices and get input
		cout << "What would you like to do?" << endl;
		cout << "1. Display Routes" << endl;
		cout << "2. Display Earnings vs Expenses By Route" << endl;
		cout << "3. Optimize Route" << endl;
		cout << "4. Exit" << endl;
		cin >> choice;
		cout << endl;

		// do action based on input
		switch(choice){

			case 1:
				DisplayRoutes();
				break;
			case 2:
				DisplayRouteData();
				break;
			case 3:
				OptimizeRoute();
				break;

		}

	}
	
}


// display all stops in all routes
void BusCompany::DisplayRoutes(){

	// display each route in m_routes
	for(unsigned int i = 0; i < m_routes.size(); i++){

		cout << "****ROUTE " << i + 1 << "****" << endl;
		cout << *m_routes.at(i);

	}
	
}


// remove routes that don't generate income
void BusCompany::OptimizeRoute(){

	// if route is empty
	if(m_routes.size() == 0){

		cout << "The route is empty" << endl << endl;

	// when there is only one route
	} else if(m_routes.size() == 1){

		m_routes.at(0)->OptimizeRoute(RIDER_FARE);
		cout << "Route optimized" << endl << endl;

	} else{

		// get desired route from user and optimize it
		unsigned int toOptimize = 0;
		while(toOptimize < 1 || toOptimize > m_routes.size()){

			cout << "Which route to you want to optimize (1 - " << m_routes.size() << ")? ";
			cin >> toOptimize;

		}

		m_routes.at(toOptimize - 1)->OptimizeRoute(RIDER_FARE);
		cout << "Route optimized" << endl << endl;

	}

}


// display route earnings, expenses, total
void BusCompany::DisplayRouteData(){

	// display data for each route in m_routes
	for(unsigned int i = 0; i < m_routes.size(); i++){

		cout << "****ROUTE " << i + 1 << "****" << endl;
		m_routes.at(i)->DisplayStopData(RIDER_FARE);

	}

}