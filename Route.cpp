#include "Route.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// default constructor
Route::Route(){

	// initialize variables
	m_start = NULL;
	m_size = 0;

}


// destructor
Route::~Route(){

	Clear();

}


// inserts stop in route
void Route::InsertAt(string name, int location, int riders, double cost){

	// create stop to add
	Stop* newStop = new Stop(name, location, riders, cost);

	// check is list is empty
	if(IsEmpty()){

		m_start = newStop;

	} else{

		// get last stop in route
		Stop* m_end = new Stop();
		for(Stop* current = m_start; current != NULL; current = current->m_next){

			m_end = current;

		}

		// add to beginning
		if(location < m_start->m_location){

			newStop->m_next = m_start;
			m_start = newStop;

		// add to end
		} else if(location > m_end->m_location){

			m_end->m_next = newStop;

		// add in middle
		} else{

			// find location to add the new stop
			Stop* previous = new Stop();
			Stop* next = new Stop();

			for(Stop* current = m_start; !(location > previous->m_location && location < current->m_location); current = current->m_next){

				previous = current;
				next = current->m_next;

			}

			// place new stop in between two others
			previous->m_next = newStop;
			newStop->m_next = next;

		}

	}

	// increase size
	m_size++;
	
}


// display stops in route
void Route::DisplayRoute(){

	if(IsEmpty()){

		cout << "Route is empty";

	} else{

		// print each stop and its location
		int count = 1;
		for(Stop* current = m_start; current != NULL; current = current->m_next){

			cout << "Stop " << count << " - " << current->m_name << " (" << current->m_location << ")" << endl;
			count++;

		}
	}

}


// check if route is empty
bool Route::IsEmpty(){

	return m_size == 0;

}


// calculate earnings for route
double Route::GetRouteEarnings(double riderFare){

	double earnings = 0;

	// add earnings from each stop to total and return the total
	for(Stop* current = m_start; current != NULL; current = current->m_next){

		earnings += (current->m_riders * riderFare);

	}

	return earnings;

}


//calculate expenses for route
double Route::GetRouteExpenses(){

	double expenses = 0;

	// add expenses from each stop to total and return the total
	for(Stop* current = m_start; current != NULL; current = current->m_next){

		expenses += current->m_cost;

	}

	return expenses;

}


// clear route of all stops
void Route::Clear(){

	// start from beginning and delete previous stops
	Stop* current = m_start;
	Stop* previous = m_start;
	
	while(current != NULL){

		current = current->m_next;
		delete previous;
		previous = current;
		m_size--;

	}

	// set all to NULL
	current = previous = NULL;
	m_start = NULL;

}


// delete stops that lose money
void Route::OptimizeRoute(double riderFare){

	// calculate net profit/loss for each stop and remove if there is a loss
	for(Stop* current = m_start; current != NULL; current = current->m_next){

		double earning = current->m_riders * riderFare;
		double expense = current->m_cost;
		double total = earning - expense;

		if(total < 0){

			RemoveStop(current->m_location);

		}

	}

}


// remove stop from route
void Route::RemoveStop(int stopLocation){

	// get last stop in route
	Stop* m_end = new Stop();
	for(Stop* current = m_start; current != NULL; current = current->m_next){

		m_end = current;

	}

	// remove first stop
	if(stopLocation == m_start->m_location){

			m_start = m_start->m_next;
	

	// remove last stop
	} else if(stopLocation == m_end->m_location){

		Stop* current = m_start;
		Stop* previous = new Stop();

		while(current->m_next != NULL){
			previous = current;
			current = current->m_next;	
		}

		m_end = previous;
		previous->m_next = NULL;

	// remove in the middle
	} else{

		Stop* current = m_start;
		Stop* previous = new Stop();

		for(Stop* temp = m_start; temp->m_location != stopLocation; temp = temp->m_next){

			previous = current;
			current = current->m_next;

		}

		previous->m_next = current->m_next;

	}

	m_size--;

}


// display stop earnings, expenses, and total loss/gain
void Route::DisplayStopData(double riderFare){

	cout << "Earnings: " << GetRouteEarnings(riderFare) << endl;
	cout << "Expenses: " << GetRouteExpenses() << endl;

	// calculate total for each stop
	for(Stop* current = m_start; current != NULL; current = current->m_next){

		double earning = current->m_riders * riderFare;
		double expense = current->m_cost;
		double total = earning - expense;
		cout << current->m_name << endl;
		cout << " Earnings: " << current->m_riders << "@" << current->m_cost << " = $" << earning << endl;
		cout << " Expenses: $" << expense << endl;
		cout << " Total: $" << total << endl;

	}

	cout << endl;

}


// get size of route
int Route::GetSize(){

	return m_size;

}


// extraction for displaying a route
ostream &operator<<(ostream &output, Route &myRoute){

	// call display route
	myRoute.DisplayRoute();
	output << "END" << endl << endl;
	return output;

}