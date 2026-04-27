// Author: Stuart King
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.

#include "RedBlackTree.h"
#include "RedBlackTree.cpp"

using namespace std;

void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate);

int main(){
   	string airLine;
   	int flightNum;
   	string deptDate;
   	string command, oneLine, token;
   	string delimiter = ",";

   	int pos = 0;

   	RedBlackTree rbt;

   	do{
     		getline(cin, oneLine);
      		pos = oneLine.find(delimiter);
      		token = oneLine.substr(0, pos);
      		command = token;
      		oneLine.erase(0, pos + delimiter.length());

      		if(command.compare("quit")==0){
         		cout << "\nCommand: quit" << endl;
         		//call the relevant function on the red black tree
         		break;
      		}else if(command.compare("tree_preorder")==0){
         		cout << "\nCommand: tree_preorder" << endl;
         		//call the relevant function on the red black tree
         		rbt.treePreorder();
      		}else if(command.compare("tree_inorder")==0){
         		cout << "\nCommand: tree_inorder" << endl;
         		//call the relevant function on the red black tree
         		rbt.treeInorder();
      		}else if(command.compare("tree_postorder")==0){
         		cout << "\nCommand: tree_postorder" << endl;
         		//call the relevant function on the red black tree
         		rbt.treePostorder();
      		}else if(command.compare("tree_minimum")==0){
         		cout << "\nCommand: tree_minimum" << endl;
         		//call the relevant function on the red black tree
         		rbt.treeMinimum();
      		}else if(command.compare("tree_maximum")==0){
         		cout << "\nCommand: tree_maximum" << endl;
         		//call the relevant function on the red black tree
         		rbt.treeMaximum();
      		}else if(command.compare("tree_predecessor")==0){
         		//call the relevant function to get the Flight info. first
         		getFlightInfo(oneLine, airLine, flightNum, deptDate);
         		cout << "\nCommand: tree_predecessor" << endl;

         		//call the relevant function on the red black tree
         		rbt.treePredecessor(airLine, flightNum, deptDate);
      		}else if(command.compare("tree_successor")==0){
         		//call the relevant function to get the Flight info. first
         		getFlightInfo(oneLine, airLine, flightNum, deptDate);
         		cout << "\nCommand: tree_successor" << endl;

         		//call the relevant function on the red black tree
         		rbt.treeSuccessor(airLine, flightNum, deptDate);
      		}else if(command.compare("tree_search")==0){
         		//call the relevant function to get the Flight info. first
         		getFlightInfo(oneLine, airLine, flightNum, deptDate);
         		cout << "\nCommand: tree_search" << endl;

         		//call the relevant function on the red black tree
         		rbt.treeSearch(airLine, flightNum, deptDate);
      		}else if(command.compare("tree_insert")==0){
         		//call the relevant function to get the Flight info. first
         		getFlightInfo(oneLine, airLine, flightNum, deptDate);
         		cout << "\nCommand: tree_insert" << endl;
         		cout << left;
         		cout << setw(5)  << airLine
         		     << setw(10) << flightNum
         		     << setw(12) << deptDate   << endl;

        		//call the relevant function to insert the Flight inside the RBT
        		rbt.treeInsert(airLine, flightNum, deptDate);
      		}
   	} while(true);  //continue until 'quit'
   	return 0;
}

//This function from one line, extracts the airLine, flightNum and deptDate of a Flight
void getFlightInfo(string oneLine, string& airLine, int& flightNum, string& deptDate){
   	string find = ","; //character that seperates values
	int pos = 0;

	pos = oneLine.find(find); //find first comma
	airLine = oneLine.substr(0, pos); //extract airline
	oneLine.erase(0, pos + find.length()); //delete airline and comma

	pos = oneLine.find(find); //find next comma
	string flightNumStr = oneLine.substr(0, pos); //extract flight num
	flightNum = stoi(flightNumStr); //convert flight num to int
	oneLine.erase(0, pos + find.length()); //erase flight num and comma

	deptDate = oneLine; //dept date is all that remains; extract it
}
