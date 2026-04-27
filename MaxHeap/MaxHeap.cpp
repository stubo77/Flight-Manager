// Author: Stuart King
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.

#include "MaxHeap.h"

using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main(){
	char input1 = 'Z';
	string airLine;
    	int flightNum;
	string deptDate;
	int capacity;   //array capacity

	bool success = false;

	int index, newIndex, oldIndex, newFlightNum;

    	Flight oneFlight;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do{
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		cin.ignore(20, '\n');	//flush the buffer
		input1 = toupper(input1);

		// matches one of the cases
		switch (input1){
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

				heap1 = new MaxHeap(capacity); //create new heap

				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
					if (heap1 != nullptr){ //if heap exists
        				delete heap1; //delete heap
        				heap1 = nullptr;
    				}

				//re-initialize it with default capacity 4
				heap1 = new MaxHeap(4); //create new heap

				break;

			case 'E':	//Extract the maximum node
                		if (heap1 == nullptr){
                    			cout << "\nEmpty heap, can NOT extract max" << endl;
                		}else{
					cout << "\nBefore extract heap max operation:" << endl;
        				heap1->printHeap(); //print heap

        				heap1->extractHeapMax(); //extract max

        				cout << "\nAfter extract heap max operation:" << endl;
        				heap1->printHeap(); //print heap
                	}
                	break;

			case 'F':	//Find a Flight
				cout << "\nEnter the flight number you want to search: ";
				cin >> flightNum;
				cin.ignore(20, '\n');	//flush the buffer

				index = heap1->isFound(flightNum);
        			if (index != -1){ //if flight is found
            				cout << "\nFlight with number: " << flightNum << " is found" << endl;
        			}else{
            				cout << "\nFlight with number: " << flightNum << " is NOT found" << endl;
				}
				break;

			case 'I':	//Insert a Flight
				cout << "\nEnter the flight airLine: ";
				cin >> airLine; //get airline input

				cout << "\nEnter the flight number: ";
				cin >> flightNum; //get flight num input

				cout << "\nEnter the flight departure date: ";
				cin >> deptDate; //get dept date input

                		cin.ignore(20, '\n');	//flush the buffer

				success = heap1->heapInsert(airLine, flightNum, deptDate);
        			if (success){ //if input was successful
            				cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is added" << endl;
        			}else{
            				cout << "\nFlight: " << airLine << " " << flightNum << " on " << deptDate << " is NOT added" << endl;
				}

				break;

			case 'K':	//increase the FlightNum
				cout << "\nEnter the original flight number which you want to increase: ";
				cin >> flightNum; //get flight num input
				cout << "\nEnter the new flight number: ";
				cin >> newFlightNum; //get new flight num input
				cin.ignore(20, '\n');	//flush the buffer

				oldIndex = heap1->isFound(flightNum); //is old flight num in heap
        			newIndex = heap1->isFound(newFlightNum); //is new flight num in heap

        			if (newFlightNum <= flightNum){ //if newflight num < old flight num
            				cout << "\nIncrease flight number error: new number is smaller than current number" << endl;
        			}else if (oldIndex == -1){ //if old flight num not present
            				cout << "\nThe old flight number you try to increase does not exist" << endl;
        			}else if (newIndex != -1){ //if new flight num present
            				cout << "\nThe new flight number you entered already exist, increase flight number operation failed" << endl;
        			}else{
            				cout << "\nBefore increase flight number operation:" << endl;
            				heap1->printHeap(); //print heap

            				// Create updated Flight object
            				Flight updatedFlight = heap1->getFlightArr()[oldIndex]; 
            				updatedFlight.flightNum = newFlightNum;

            				bool success = heap1->heapIncreaseFlightNum(oldIndex, updatedFlight);
            				if (success){ //if increase was success
                				cout << "\nFlight with old number: " << flightNum << " is increased to new number: " << newFlightNum << endl;

                				cout << "\nAfter increase flight number operation: " << endl;
                				heap1->printHeap(); //print heap
            				}
        			}


				break;

			case 'M':	//get maximum node
				if (heap1 == nullptr || heap1->getSize() == 0){ //if heap is empty
        				cout << "\nEmpty heap, can NOT get max node" << endl;
    				}else{
        				Flight maxFlight = heap1->getHeapMax(); //set maxFlight = heapMax
        				cout << "\nThe maximum heap node is:" << endl;
        				cout << left;
        				cout << setw(5)  << maxFlight.airLine << setw(10) << maxFlight.flightNum << setw(12) << maxFlight.deptDate << endl;
    				}

				break;

			case 'P':	//Print heap contents
				heap1->printHeap(); //print heap
				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Flights will be sorted in increasing order of their numbers" << endl;
				heapSort(heap1); //sort heap

				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "\nUnknown action" << endl;
				break;
		} //end of switch
	} while (input1 != 'Q');
	return 0;
}

//Given a max heap, we want to sort it in increasing order of flightNum, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap){
	if (oneMaxHeap == nullptr || oneMaxHeap->getSize() == 0)
        return;

    	int originalSize = oneMaxHeap->getSize();

    	// Create a temporary array to hold sorted flights
    	Flight* sortedArr = new Flight[originalSize];

    	// Extract max repeatedly and store in reverse order
    	for (int i = originalSize - 1; i >= 0; i--){
        	sortedArr[i] = oneMaxHeap->getHeapMax();
        	oneMaxHeap->extractHeapMax();
    	}

    	// Print sorted flights in increasing order
    	cout << left;
    	for (int i = 0; i < originalSize; i++){
        	cout << setw(5)  << sortedArr[i].airLine
             	     << setw(10) << sortedArr[i].flightNum
             	     << setw(12) << sortedArr[i].deptDate << endl;
    	}
    	// Clean up
    	delete[] sortedArr;
}

//**The function displays the menu to a user**//
void printMenu(){
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a flight by number\n";
	cout << "I\t\tInsert a flight\n";
	cout << "K\t\tIncrease a flight number\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
