// Name of Author: Stuart King
// Description: this is where the design of functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay are found

using namespace std;

class Hash{
    	private:
		LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
		int m;      //m is the slot number of the hash table
		int hashSize = 0;
	public:
      		Hash(int size);
      		~Hash();
      		bool hashSearch(string airLine, int flightNum, string deptDate);
      		bool hashInsert(string airLine, int flightNum, string deptDate);
      		bool hashDelete(string airLine, int flightNum, string deptDate);
      		double hashLoadFactor();
      		void hashDisplay();
      		int hashFunction(string key);
 };


//constructor
Hash::Hash(int size){
  	m = 0; //initialize m to slot 0
   	hashTable = new LinkedList[size]; //create new linked list of size, size
	hashSize = size;
}

//Destructor
Hash::~Hash(){
   	delete[] hashTable; //delete the linked list
   	hashTable = nullptr; //elim dangling pointer
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
bool Hash::hashSearch(string airLine, int flightNum, string deptDate){
   	bool found = false;
   	string key = airLine+std::to_string(flightNum)+deptDate; //create key
   	int location = hashFunction(key); //get hash slot

	found = hashTable[location].searchFlight(airLine, flightNum, deptDate); 

   	if (found == true){
     		cout << "\n"       << left
          	<< setw(5)    << airLine
          	<< setw(10)   << flightNum << " on "
          	<< setw(12)   << deptDate
          	<< " is found inside the hash table" << endl;
		return true;
	}
   	else{
      		cout << "\n"      << left
           	<< setw(5)   << airLine
           	<< setw(10)  << flightNum << " on "
           	<< setw(12)  << deptDate
           	<< " is NOT found inside the hash table" << endl;
		return false;
   	}
}

//hashInsert inserts a Flight with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string airLine, int flightNum, string deptDate){
	string key = airLine+std::to_string(flightNum)+deptDate; //get key
	int location = hashFunction(key); //get location from hash function

	bool inserted = hashTable[location].insertFlight(airLine, flightNum, deptDate); //insert flight and assign instered bool based on result
	return inserted;
}

//hashDelete deletes a Flight with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of airLine, flightNum and deptDate
bool Hash::hashDelete(string airLine, int flightNum, string deptDate){
   	string key = airLine+std::to_string(flightNum)+deptDate; //create key
	int location = hashFunction(key);

	hashSearch(airLine, flightNum, deptDate);

	bool deleted = hashTable[location].deleteFlight(airLine, flightNum, deptDate); //delete flight and assign deleted based on result

	if(deleted){
   		cout << left
        	<< setw(5)   << airLine
        	<< setw(10)  << flightNum << " on "
        	<< setw(12)  << deptDate
        	<< " is deleted from hash table" << endl;
   		return true;
	}else{
   		cout << left
        	<< setw(5)   << airLine
        	<< setw(10)  << flightNum << " on "
        	<< setw(12)  << deptDate
        	<< " is NOT deleted from hash table" << endl;
		return false;
	}
}

//This function computes your hash table real load factor
//it is the longest linked list size
double Hash::hashLoadFactor(){
	double maxLength = 0; //set initial max

	for(int i = 0; i < hashSize; i++){ //for each index in hash
		if(hashTable[i].getSize() > maxLength){ //if the length
			maxLength = hashTable[i].getSize(); //set max length to length of list
		}
	}
	return maxLength;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay(){
   	for(int i = 0; i < hashSize; i++){ //for each index in hash
		int size = hashTable[i].getSize(); //get sizeof list
		cout << "\nHashTable[" << i << "], size = " << size << endl; //display table size

		if(size > 0){ //if list has elements
			hashTable[i].displayList(); //display list
		}
	}
}

//Given a string key, this function returns the
//slot number where the key is hashed to.
int Hash::hashFunction(string key){
	int numericKey = 0; //key made numeric
   	for(char c : key){ //for each char in key
		if(std::isalpha(c)){ //if the char is a-z or A-Z
			char uc = std::toupper(c); //convert char to uppercase
			numericKey += (uc - 'A' + 1); //generate alphabetic numeral and add to sum
		}else if(std::isdigit(c)){ //if the char is a digit
			numericKey += (c - '0'); //add to sum
		}
	}

	int hash = (31 * numericKey) ^ (numericKey >> 7); 
	//mult key by 31 and XOR with shifted key
	hash = (hash * 17) % hashSize; //mult that new hash by 17 and mod by the size of hash
	return hash; //return hash
}
