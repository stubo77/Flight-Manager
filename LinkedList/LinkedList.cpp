// Author: Stuart King
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

#include "LinkedList.h"

using namespace std;

void printMenu();

int main(){
        // local variables, can be accessed anywhere from the main method
        char input1 = 'Z';
        string inputInfo;
        string airLine, deptDate;
        int flightNum;
        string line;
        bool success = false;

        string oldDeptDate, newDeptDate, oldAirLine, newAirLine;

        // instantiate a LinkedList object
        LinkedList* list1 = new LinkedList();

        printMenu();

	do{
        	cout << "\nWhat action would you like to perform?\n";
           	cin >> input1;
           	input1 = toupper(input1); //change it to upper case
           	cin.ignore(1000, '\n'); //flush the buffer whenever you enter a char, integer or double

           	// matches one of the case statement
           	switch (input1){
             		case 'A':   //Add the flight
               			cout << "\nEnter the flight information: ";
               			cout << "\nEnter airline code: ";
               			// get airline input
	       			cin >> airLine;

               			cout << "\nEnter flight num: ";
               			// get flight number input
	       			cin >> flightNum;

               			cin.ignore(20, '\n'); //flush the buffer

               			cout << "\nEnter departure date: ";
               			// get departure date input
	       			cin >> deptDate;
	       			cin.ignore(20, '\n');
               			// set success equal to the output of add flight
	       			success = list1->LinkedList::addFlight(airLine, flightNum, deptDate);

               			if (success == true)
                			cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is added\n";
               			else
                			cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is NOT added\n";
               			break;

            		case 'C':  //Cancel one flight
                		cout << "\nEnter the flight info. which you want to cancel: ";
                		cout << "\nEnter airline: ";
                		// get airline input
				cin >> airLine;
                		cout << "\nEnter flight num: ";
                		// get flight number input
				cin >> flightNum;
                		cin.ignore(20, '\n'); //flush the buffer.
                		cout << "\nEnter departure date: ";
               			// get departure date input
				cin >> deptDate;
                		// set success equal to the output of cancel one flight
				success = list1->LinkedList::cancelOneFlight(airLine, flightNum, deptDate);
                		if (success == false)
                    			cout << "\nNo such flight inside the list, cannot cancel it\n";
                		else
                    			cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is canceled\n";
                		break;

             		case 'D':   //Display all Flights
               			// display the flights
	       			list1->LinkedList::displayAllFlights();
               			cout << "\nTotal # of flights: " << list1->LinkedList::countTotalFlights() << "\n";
               			break;

             		case 'E':   //Display Flights by airline
                		cout << "\nWhich airline you want to display flights: \n";
                		// get airline from input
				cin >> airLine;
                		// display the flights
				list1->LinkedList::displayFlightsByAirLine(airLine);
                		cout << "\nTotal # of flights by "<< airLine << " is: " << list1->LinkedList::countFlightsByAirLine(airLine) << "\n";
                		break;

              		case 'F':   //Display Flights by departure date
                		cout << "\nWhich date you want to display flights: \n";
                		// get deptarture date from input
				cin >> deptDate;
                		// display the flights
				list1->LinkedList::displayFlightsByDate(deptDate);
                		cout << "\nTotal # of flights on "<< deptDate << " is: " << list1->LinkedList::countFlightsByDate(deptDate) << "\n";
                		break;

             		case 'O':  //Cancel all flights by a specific airline
                		cout << "\nWhich airline you want to cancel all flights with: ";
                		//get airline input
				cin >> airLine;
				//set success equal to output of cancel flights by airline
				success = list1->LinkedList::cancelFlightsByAirLine(airLine);

                		if (success)
                    			cout << "\nAll flights with " << airLine << " are canceled\n";
                		else
                    			cout << "\nFlights with " << airLine << " does NOT exist. Cancel failed\n";
                		break;

            		case 'R':  //Cancel all flights by a specific departure date
               			cout << "\nWhich date you want to cancel flights with: ";
                		// get departure date input
				cin >> deptDate;
                		// set success equal to the output of cancel flights by date
				success = list1->LinkedList::cancelFlightsByDate(deptDate);

                		if (success)
                    			cout << "\nAll flights on " << deptDate << " are canceled\n";
                		else
                    			cout << "\nFlight on " << deptDate << " does NOT exist, cancel failed\n";
                		break;

            		case 'S':  //search a specific flight
                		cout << "\nSearch a flight: ";
                		cout << "\nEnter airline: ";
                		// get airline input
				cin >> airLine;

                		cout << "\nEnter flight num: ";
                		// get flight number input
				cin >> flightNum;
                		cin.ignore(20, '\n'); //flush the buffer

                		cout << "\nEnter departure date: ";
                		// get departure date input
				cin >> deptDate;
                		// set success equal to the output of search flight
				success = list1->LinkedList::searchFlight(airLine, flightNum, deptDate);

                		if (success == false)
                    			cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is NOT found\n";
                		else
                    			cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is found\n";
                		break;

            		case 'U':  //Delay a flight, i.e. update a flight departure date
                		cout << "\nEnter airline code: ";
                		// get airline input
				cin >> airLine;

                		cout << "\nEnter flight num: ";
                		// get flight number input
				cin >> flightNum;
                		cin.ignore(20, '\n'); //flush the buffer

                		cout << "\nEnter old departure date: ";
                		// get old departure date input
				cin >> oldDeptDate;

                		cout << "\nEnter new departure date: ";
                		// get new departure date input
				cin >> newDeptDate;
                		// set success equal to the output of delay a flight
				success = list1->LinkedList::delayAFlight(airLine, flightNum, oldDeptDate, newDeptDate);

                		if (success == true)
                     			cout << "\nFlight: " << airLine << " " << flightNum << " on " << oldDeptDate << " departure date is changed to " << newDeptDate << "\n";
                		else
                     			cout << "\nFlight: " << airLine << " " << flightNum << " on " << oldDeptDate << " departure date is NOT changed" << "\n";
                		break;

             		case 'V':  //Change a flight airline code
                		cout << "\nEnter airline code: ";
                		// get old airline input
				cin >> oldAirLine;

                		cout << "\nEnter flight num: ";
                		// get flight number input
				cin >> flightNum;
                		cin.ignore(20, '\n'); //flush the buffer

               		 	cout << "\nEnter departure date: ";
                		// get departure date input
				cin >> deptDate;

                		cout << "\nEnter new airline code: ";
                		// get new airline input
				cin >> newAirLine;
                		// sset success equal to the output of change a flight airline
				success = list1->LinkedList::changeAFlightAirLine(oldAirLine, flightNum, deptDate, newAirLine);
                		if (success == true)
                     			cout << "\nFlight: " << oldAirLine << " " << flightNum << " on " << deptDate << " airline is changed to " << newAirLine << "\n";
                		else
                     			cout << "\nFlight: " << oldAirLine << " " << flightNum << " on " << deptDate << " airline is NOT changed" << "\n";
                		break;

             		case 'Q':   //Quit
		    		list1->LinkedList::~LinkedList();
                    		break;

             		case '?':   //Display Menu
                    		printMenu();
                    		break;

             		default:
               			cout << "\nUnknown action\n";
               			break;
            	}

        }
	while (input1 != 'Q');
      	return 0;
}

/** The method displays the menu to a user**/
void printMenu(){
     	cout << "Choice\t\tAction\n";
     	cout << "------\t\t------\n";
     	cout << "A\t\tAdd a Flight\n";
     	cout << "C\t\tCancel One Flight\n";
     	cout << "D\t\tDisplay All Flights\n";
     	cout << "E\t\tDisplay Flights by Airline\n";
     	cout << "F\t\tDisplay Flights by Date\n";
     	cout << "O\t\tCancel Flights by Airline\n";
     	cout << "R\t\tCancel Flights by Date\n";
     	cout << "S\t\tSearch one Flight\n";
     	cout << "U\t\tDelay a Flight\n";
     	cout << "V\t\tChange a Flight Airline\n";
     	cout << "Q\t\tQuit\n";
     	cout << "?\t\tDisplay Help\n\n";
}
