// Author: Stuart King
// Description: this is the main program that reads input from keyboard.
// it then call hash functions to execute hash commands given in the input.

#include "LinkedList.h"
#include "Hash.h"
#include <sstream>

using namespace std;

//This function used to get all info of a Flight object
void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate);

int main(){
   	int size = 0;

   	//a counter used to count number of valid Flight objects entered
   	//Note: duplicated flights will NOT be counted inside
   	int counter = 0;

   	string airLine, deptDate;
   	int flightNum;

   	//declare any other necessary variables here
   	string func, oneLine;

   	cin >> size;
   	cin.ignore(20, '\n');

   	//Instantiate the hash table with the relevant number of slots
   	Hash hashTable(size);

   	do{
        	getline(cin, oneLine);
		if(oneLine == "InsertionEnd"){
			break;
		}

		getFlightInfo(oneLine, airLine, flightNum, deptDate);
		if(hashTable.hashInsert(airLine, flightNum, deptDate)){
			counter++;
		}

   	} while(true);

    	cout << "\nHash table size is: " << size;
    	cout << "\nTotal Flight objects entered is: " << counter;

   	//This do..while loop is used to get the commands until 'End'
   	do{
        	//get one line command
		getline(cin, oneLine); //get line
		size_t pos = oneLine.find(','); //find comma
		string func;

		if(pos == string::npos){ //if no comma (whole line is command
			func = oneLine;
		}else{ //comma found (additional parameters)
			func = oneLine.substr(0, pos);
		}

        	//analyze the first string in tokens[] to determine func
		if(func == "End"){
			break;
		}else if(func == "hashDisplay"){
			hashTable.hashDisplay();
		}else if(func == "hashLoadFactor"){
			cout << fixed << setprecision(2);
			double idealLoadFactor = (double)counter/size;
			cout << "\nThe ideal load factor is: " << idealLoadFactor << endl;
			cout << "My hash table real load factor is: " << hashTable.hashLoadFactor() << endl;
			double performanceRatio = hashTable.hashLoadFactor()/idealLoadFactor;
			cout << "My hash table performance ratio is: " << performanceRatio << endl;
		}else if(func == "hashSearch" || func == "hashDelete"){ //if func is search and there are 4 input parameters
			oneLine.erase(0, pos+1); //strip command and first comma

			pos = oneLine.find(','); //find next comma
			string line = oneLine.substr(0, pos); //extract airline
			oneLine.erase(0, pos+1); //delete substring

			pos = oneLine.find(','); //find next comma
			string numString = oneLine.substr(0, pos); //extract flight num into string
			stringstream ss(numString);
			int num = 0; //initialize num
			ss >> num; //convert string of digits to int
			oneLine.erase(0, pos+1); //delete substrnig

			string date = oneLine; //dept date is all left

			if(func == "hashSearch"){
				hashTable.hashSearch(line, num, date);
			}else{
				hashTable.hashDelete(line, num, date);
			}
		}
	} while(true);
	return 0;
}

//From one line, this function extracts the tokens and get one Flight info.
void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate){
    	string delimiter = ",";
	int pos = oneLine.find(delimiter);
	string token = oneLine.substr(0,pos);
	airLine = token;
	oneLine.erase(0, pos+delimiter.length());

	pos = oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	flightNum = stoi(token);
	oneLine.erase(0, pos+delimiter.length());

	pos=oneLine.find(delimiter);
	token = oneLine.substr(0,pos);
	deptDate = token;
	oneLine.erase(0, pos+delimiter.length());
}
