// Author: Stuart King
// Description: Header file responsible for the Linked List functionality

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Flight represents a departure flight
struct Flight{
    	string airLine;
    	int flightNum;
   	string deptDate; 
    	struct Flight* next;
};

//class LinkedList will contains a linked list of flights
class LinkedList{
	private:
        	struct Flight* head;

    	public:
   		LinkedList();
   		~LinkedList();
   		bool searchFlight(string airLine, int flightNum, string deptDate);
   		bool addFlight(string airLine, int flightNum, string deptDate);
   		int countTotalFlights();
   		int countFlightsByAirLine(string airLine);
   		int countFlightsByDate(string deptDate);
   		bool cancelOneFlight(string airLine, int flightNum, string deptDate);
   		bool cancelFlightsByAirLine(string airLine);
   		bool cancelFlightsByDate(string deptDate);
   		bool delayAFlight(string airLine, int flightNum, string oldDeptDate, string newDeptDate);
   		bool changeAFlightAirLine(string oldAirLine, int flightNum, string deptDate, string newAirLine);
  		void displayAllFlights();
   		void displayFlightsByAirLine(string airLine);
   		void displayFlightsByDate(string date);
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList(){
    	head = nullptr;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList(){
    	int flightCount = 0; 
    	Flight* current = head; //set current to head
    	while (current != nullptr){ //while current is not at the end
		Flight* del = current; //set temp pointer for deletion
		current = current->next; //increment current
		delete del; //delete temp pointer
		flightCount++; 
    	}
    	head = nullptr; //return the linked list to a default state

    	cout<< "\nThe number of deleted flights is: " << flightCount <<"\n";
}

string formatDate(string date){
    	string m = date.substr(0,2); //get the month substring from the date input
    	string d = date.substr(3,2); //get the day substring from the date input
    	string y = date.substr(6,4); //get the year substring from the date input
    	return y+m+d; //reformate the date as yyyymmdd
}

//A function to find if the parameterized flight is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::searchFlight(string airLine, int flightNum, string deptDate){
    	Flight* current = head; //set current pointer to head
    	while(current != nullptr){
		if(current->airLine == airLine && current->flightNum == flightNum && current->deptDate == deptDate){ //if current pointer is equal to input
	    		return true;
		}
		current = current->next; //move current forward
    	}
    	return false;
}

//Creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of flights by the airLine, flight number
//and departure date. i.e. first by airLine, then by flight numbers. i.e. if two flights
//come from the same airline, the flight should be inserted by the increasing order of
//their flight numbers.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addFlight(string airLine, int flightNum, string deptDate){
    	if(searchFlight(airLine, flightNum, deptDate)) return false; //if the flight is in the list instantly return false

    	Flight* newFlight = new Flight; //create a new flight

    	string headDate = "placeholder"; //sets head->deptDate to a temp placeholder

    	newFlight->airLine = airLine; //assign airline
    	newFlight->flightNum = flightNum; //assign flight num
    	newFlight->deptDate = deptDate; //assign departure date
    	newFlight->next = nullptr;

    	deptDate = formatDate(deptDate); //format the input date
    	if(head != nullptr){
		string headDate = formatDate(head->deptDate); //formate the head pointer date
    	}

   	//if empty list
    	if(head == nullptr){
		newFlight->next = head; //set newFlight pointing to head
		head = newFlight; //set head equal to new flight
		return true;
    	}

    	//if insert at head
    	if(head != nullptr && (airLine < head->airLine || (airLine == head->airLine && flightNum < head->flightNum) || (airLine == head->airLine && flightNum == head->flightNum && deptDate < headDate))){
		newFlight->next = head; //set newFlight pointing to head;
		head = newFlight; //set head equal to new flight
		return true;
    	}

    	//if insert somewhere in the middle
    	Flight* previous = nullptr;
    	Flight* current = head;
    	while(current != nullptr){
		string currentDate = formatDate(current->deptDate); //format current->deptDate
		if(airLine < current->airLine || (airLine == current->airLine && flightNum < current->flightNum) || (airLine == current->airLine && flightNum == current->flightNum && deptDate < currentDate)) break;	
			previous = current; //move previous forward
			current = current->next; //move current forward
    	}
    	previous->next = newFlight; //set previous pointing to newFlight
    	newFlight->next = current; //set newFlight pointing to current
    	return true;
}

//This function counts total number of flights inside the list and return it.
int LinkedList::countTotalFlights(){
    	int count = 0;
    	Flight* counter = head; //new counter pointer
    	while(counter != nullptr){
		count++; //add
		counter = counter->next; //traverse
    	}
    	return count;
}

//This function counts total number of flights by the specified airLine and return it.
int LinkedList::countFlightsByAirLine(string airLine){
    	int count = 0;
    	Flight* counter = head; //new counter pointer
    	while(counter != nullptr){
		if(counter->airLine == airLine) count++; //add
		counter = counter->next; //traverse
    	}
    	return count;
}

//This function counts total number of flights on the specified date and return it.
int LinkedList::countFlightsByDate(string deptDate){
    	int count = 0;
    	Flight* counter = head; //new counter pointer
    	while(counter != nullptr){
		if(counter->deptDate == deptDate) count++; //add
		counter = counter->next; //traverse
    	}
    	return count;
}

//Display all flights in the linked list starting from the head.
void LinkedList::displayAllFlights(){
    	Flight* temp = head; //new temp ointer
    	while(temp != nullptr){ 
		cout << left    << setw(5)  << temp->airLine
                     << setw(10) << temp->flightNum
                     << setw(12) << temp->deptDate   << "\n";
		temp = temp->next; //traverse
    	}
}

//Display all flights in the list with the specified airLine.
void LinkedList::displayFlightsByAirLine(string airLine){
   	Flight* temp = head; //new temp pointer
   	while(temp != nullptr){
		if(temp->airLine == airLine){ //only display if airlines match
    	    		cout << left    << setw(5)  << temp->airLine
            	             << setw(10) << temp->flightNum
                	     << setw(12) << temp->deptDate   << "\n";
		}
		temp = temp->next; //traverse
    	}
}

//Display all flights with the specified date
void LinkedList::displayFlightsByDate(string date){
    	Flight* temp = head; //new temp pointer
    	while(temp != nullptr){
		if(temp->deptDate == date){ //only display if deptDate matches
    	    		cout << left    << setw(5)  << temp->airLine
            	             << setw(10) << temp->flightNum
                	     << setw(12) << temp->deptDate   << "\n";
		}
		temp = temp->next; //traverse
    	}
}

//Cancel the specified flight from the list, releases the memory and updates pointers.
//Return true if it is successfully canceled, false otherwise.
bool LinkedList::cancelOneFlight(string airLine, int flightNum, string deptDate){
    	if(head == nullptr) return false; //if there is no head there is no flight to cancel

    	if(head->airLine == airLine && head->flightNum == flightNum && head->deptDate == deptDate){ //if head==input
		Flight* del = head; //set new pointer del = head
		head = head->next; //advance head
		delete del;
		return true;
    	}

    	Flight* previous = nullptr;
    	Flight* current = head;
    	while(current != nullptr){
		if(current->airLine == airLine && current->flightNum == flightNum && current->deptDate == deptDate){ //if current==input
	    		previous->next = current->next; //set previous pointer one further
	    		delete current;
	    		return true;
		}
    		previous = current; //traverse
    		current = current->next; //traverse
    	}
    	return false;
}

//Cancel all flights from a specific airline, releases the memory and updates pointers.
//Return true if it is successfully canceled, false otherwise. Note: multiple flights
//might be canceled
bool LinkedList::cancelFlightsByAirLine(string airLine){
    	bool deleted = false; //default return is false

    	if(head == nullptr) return false;

    	while(head->airLine == airLine){ //if head airline matches input
		Flight* del = head; //set del=head
		head = head->next; //traverse head
		delete del;
		deleted = true; //delete has occured
    	}

    	Flight* previous = nullptr;
    	Flight* current = head;

    	while(current != nullptr){
		if(current->airLine == airLine){ //if current==input airline
	    		previous->next = current->next; //just previous pointer ahead
	    		delete current;
	    		current = previous->next; //reconfigure current
	    		deleted = true; //delete has occured
		}else{
	    		previous = current; //traverse
	    		current = current->next; //traverse
		}
    	}
    	return deleted;
}

//Removes all flights with the specified date, releases the memory and updates pointers.
//Return true if they are successfully removed, false otherwise. Note: all Flights with
//the same departure date should be removed from the list.
bool LinkedList::cancelFlightsByDate(string deptDate){
    	bool deleted = false; //default is not deleted

    	if(head == nullptr) return false;

    	while(head->deptDate == deptDate){ //if head==input departure date
		Flight* del = head; //set del = head
		head = head->next; //traverse head
		delete del;
		deleted = true; //deleted occured
    	}

    	Flight* previous = nullptr;
    	Flight* current = head;

    	while(current != nullptr){
		if(formatDate(current->deptDate) == formatDate(deptDate)){ //if current==input departure date
	    		previous->next = current->next; //jump previous over current
	    		delete current;
	    		current = previous->next; //reconfigure current
	    		deleted = true; //delete occured
		}else{
	    		previous = current; //traverse
	    		current = current->next; //traverse
		}
    	}
    	return deleted;
}

//Modifies the departure date of the given flight. Return true if it modifies successfully and
//false otherwise.
bool LinkedList::delayAFlight(string airLine, int flightNum, string oldDeptDate, string newDeptDate){
    	Flight* previous = nullptr;
    	Flight* current = head;
    	if(cancelOneFlight(airLine, flightNum, oldDeptDate)){ //cancel the old flight
		return addFlight(airLine, flightNum, newDeptDate); //add the same flight with updated deptDAte
    	}else{
    		return false; //change has not occured
    	}
}

//Change a specific flight airline info. if it is found and change its airline successfully, return
//true; otherwise return false. Note: after successfully change its airline information, the linked list must
//still be in alphabetical order
bool LinkedList::changeAFlightAirLine(string oldAirLine, int flightNum, string deptDate, string newAirLine){
    	if(cancelOneFlight(oldAirLine, flightNum, deptDate)){ //cancel the old flight
		return addFlight(newAirLine, flightNum, deptDate); //add the same flight with updated airline
    	}else{
		return false;
    	}
}
