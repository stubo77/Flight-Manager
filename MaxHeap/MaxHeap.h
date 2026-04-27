// Author: Stuart King
// Description: header file for Assignment3.cpp,
//              cotains all the functions necessary
//              for manipulating the heap.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Assume each Flight has a unique flightNum
struct Flight{
    	string airLine;
    	int flightNum;
    	string deptDate;
};

//class MaxHeap represents a max heap that contains Flight objects. The underline data structure
//is a one dimensional array of Flight.
class MaxHeap{
    	private:
    		struct Flight* flightArr;	//an array of Flight
    		int capacity, size;

	public:
    		MaxHeap(int capacity);
    		~MaxHeap();

		Flight* getFlightArr();
		int getSize();
		int getCapacity();
		int isFound(int aFlightNum);
		bool heapIncreaseFlightNum(int index, Flight oneFlightWithNewFlightNum);
		bool heapInsert(string airLine, int flightNum, string deptDate);
		void heapify(int index);
		Flight getHeapMax();
		void extractHeapMax();
		int leftChild(int parentIndex);
		int rightChild(int parentIndex);
		int parent(int childIndex);
		void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity){
	this->capacity = capacity; //set capcacity
	this->size = 0; //set size=0
	this->flightArr = new Flight[capacity]; //set new array
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap(){
	int numOfFlights = size; //set numOfFlights
	delete[] flightArr; //delete the array
	cout << "\nThe number of deleted flights is: " << numOfFlights << endl;
}

Flight* MaxHeap::getFlightArr(){
    	return flightArr;
}

int MaxHeap::getSize(){
    	return size;
}

int MaxHeap::getCapacity(){
    	return capacity;
}

int MaxHeap::isFound(int aFlightNum){
    	for (int i = 0; i < size; i++){ //for each flight in array
        	if (flightArr[i].flightNum == aFlightNum){ //if flight num matches
            		return i;  // found, return index
        	}
    	}
    	return -1; // not found
}

bool MaxHeap::heapIncreaseFlightNum(int index, Flight oneFlightWithNewFlightNum){
    	if (oneFlightWithNewFlightNum.flightNum < flightArr[index].flightNum){ //if new num is smaller
        	cout << "\nIncrease flight number error: new flightNum is smaller than the current flightNum" << endl;
        	return false;
    	}

    	flightArr[index] = oneFlightWithNewFlightNum; //update index

    	while (flightArr[parent(index)].flightNum < flightArr[index].flightNum){ //while index is smaller than parent index
        	swap(flightArr[index], flightArr[parent(index)]); //swap flight with parent
        	index = parent(index); //exchange index
    	}
    	return true;
}

//Insert the relevant Flight object inside the heap at the correct location
bool MaxHeap::heapInsert(string airLine, int flightNum, string deptDate){
	//if the flight already exist, return false
	if(isFound(flightNum) != -1){
		cout << "\nDuplicated flight. Not added" << endl;
		return false;
	}
	if (size == capacity){
		cout << "\nReach the capacity limit, double the capacity now.\n" << endl;
        	capacity *= 2;
        	cout << "The new capacity now is " << capacity << endl;

        	Flight* newArr = new Flight[capacity]; //allocate array with new capacity

        	for (int i = 0; i < size; i++){ //for each flight in old array
            		newArr[i] = flightArr[i]; //move to new array
        	}

        	delete[] flightArr; //delete old array

        	flightArr = newArr; //point to new array
    	}

	Flight temp; //create temp flight
    	temp.airLine = airLine;
    	temp.flightNum = -1;  //small value
    	temp.deptDate = deptDate;

    	flightArr[size] = temp;

    	size++; //increase size

    	Flight newFlight; //new flight
    	newFlight.airLine = airLine; //set airline
    	newFlight.flightNum = flightNum; //set num
    	newFlight.deptDate = deptDate; //set date

    	return heapIncreaseFlightNum(size - 1, newFlight); //increase 
}

void MaxHeap::heapify(int index){
   	while (true){
        	int left  = 2 * index + 1; //get left child
        	int right = 2 * index + 2; //get right child
        	int largest = index;

        	//check left child
        	if (left < size && flightArr[left].flightNum > flightArr[largest].flightNum){
            		largest = left;
        	}

        	//check right child
        	if (right < size && flightArr[right].flightNum > flightArr[largest].flightNum){
            		largest = right;
        	}

        	if (largest == index){ //if index is largest
			break; //stop
		}else{ //otherwise
        		swap(flightArr[index], flightArr[largest]); //swap index with the larger child
        	}
		index = largest; //index now largest
    	}
}

Flight MaxHeap::getHeapMax(){
   	return flightArr[0]; // root of the max-heap
}

void MaxHeap::extractHeapMax(){
    	if (size == 1){ //if only one element
        	size--; //reduce size
        	return;
    	}

    	flightArr[0] = flightArr[size - 1]; //set root node = to smallest node

    	size--; //reduce heap size

    	heapify(0); //restore order
}

int MaxHeap::leftChild(int parentIndex){
    	return 2 * parentIndex + 1;
}

int MaxHeap::rightChild(int parentIndex){
    	return 2 * parentIndex + 2;
}

int MaxHeap::parent(int childIndex){
    	return (childIndex - 1) / 2;
}

void MaxHeap::printHeap()
{
	if (size == 0){ //if empty heap
        	cout << "\nEmpty heap, no elements" << endl;
        	return;
    	}

	cout << "\nHeap capacity = " << getCapacity() << endl;
	cout << "\nHeap size = " << getSize() << "\n" << endl;

	for(int i = 0; i < size; i++){ //for each flight in heap
    		cout << left;
    		cout << setw(5)  << flightArr[i].airLine << setw(10) << flightArr[i].flightNum << setw(12) << flightArr[i].deptDate << endl;
	}
}
