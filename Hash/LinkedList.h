// Author: Stuart King
// Description: A simple linked list that implements a list of Flight objects. A user can
//              perform searching, insertion or deletion on the linked list.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Flight{
    	string airLine;
    	int flightNum;
    	string deptDate;
    	struct Flight* next;
};

class LinkedList{
	private:
		struct Flight* head;
		int size;      //number of Flight objects inside the linked list
    	public:
       		LinkedList();
       		~LinkedList();
       		Flight* getHead();
       		int getSize();
       		bool searchFlight(string airLine, int flightNum, string deptDate);
       		bool insertFlight(string airLine, int flightNum, string deptDate);
       		bool deleteFlight(string airLine, int flightNum, string deptDate);
       		void displayList();
};

//Constructor
LinkedList::LinkedList(){
    	head = nullptr; //no head 
    	size = 0; //no flight in list
}

//Destructor
LinkedList::~LinkedList(){
    	Flight* current = head; //new current pointer
    	while(current != nullptr){ //while current is pointing to a valid flight
		Flight* prev = current; //new prev pointer
		current = current->next; // iterate current
		delete prev; //delete prev
	}
	head = nullptr; //no head
	size = 0; //no flights in list
}

Flight* LinkedList::getHead(){
    	return head; //return head node
}

//Return number of Flights inside the Linked list
int LinkedList::getSize()
{
    	return size; //return sizeof list
}

//This function does a linear search on the Flight list with the given flight info.
//it returns true if the corresponding Flight is found, otherwise it returns false.
//Note: each flight is uniquely identified by combination of airLine, flightNum and deptDate
bool LinkedList::searchFlight(string airLine, int flightNum, string deptDate){
    	Flight* current = head; //new current pointer
    	while(current != nullptr){ //while current is pointing to something
		if(current->airLine == airLine && current->flightNum == flightNum && current->deptDate == deptDate){ //if all info matches input
			return true;
		}
		current = current->next;
	}
	return false;
}

//Insert the parameter Flight at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertFlight(string airLine, int flightNum, string deptDate){
     	//if the Flight already exist, return false
     	if (searchFlight(airLine, flightNum, deptDate)){
         	cout << "\n" << airLine << " " << flightNum << " on " << deptDate << " duplicated. NOT added" << endl;
         	return false;
     	}

	Flight* newFlight = new Flight; //new flight object
	newFlight->airLine = airLine; //set airline
	newFlight->flightNum = flightNum; //set flight num
	newFlight->deptDate = deptDate; //set deptdate

	newFlight->next = head; //set next flight = head
     	head = newFlight; //set head = flight
	size++; //add one to size

	return true;
}

//Delete the Flight with the given info. from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteFlight(string airLine, int flightNum, string deptDate){
    	Flight* current = head; //new current pointer
    	Flight* prev = nullptr; //new prev pointer

	while(current != nullptr){ //while current is pointing to an object
		if(current->airLine == airLine && current->flightNum == flightNum && current->deptDate == deptDate){ //if flight data matches input
			if(current == head){ //if object to be deleted is head
				head = current->next; //move head forward
			}else{
				prev->next = current->next; //fix prev->next because current will be destroyed
			}

			delete current;
			size--;
			return true;
		}
		prev = current; //move prev forward
		current = current->next; //move current
	}
	return false; //flight not found
}

//This function displays the content of the linked list.
void LinkedList::displayList(){
    	Flight* temp = head; //new temp pointer
    	while(temp != nullptr){ //while temp is pointing to a flight
    		cout    << left<< setw(5)  << temp->airLine
            		<< setw(10) << temp->flightNum
            		<< setw(12) << temp->deptDate  << "\n";
		temp = temp->next;
	}
}
