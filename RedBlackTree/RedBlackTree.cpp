// Author: Stuart King
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition

#include "RedBlackTree.h"

using namespace std;

//constructor
RedBlackTree::RedBlackTree(){
	root = NULL; //set root node to null
}


//destructor
RedBlackTree::~RedBlackTree(){
	int nodeNum = 0; //new var to count deleted nodes
	nodeNum = deleteNode(root); //recursive delete function
	root = NULL; //remove floating pointer

	cout << "The number of deleted nodes: " << nodeNum << endl;
}

//helper function for the destructor
int RedBlackTree::deleteNode(Node* node){
	if(node == NULL) return 0; //if this node is null it has no children

	int count = 0; //int for counting # of deleted nodes

	count += deleteNode(node->leftChild); //delete leftChild's tree
	count += deleteNode(node->rightChild); //delete rightChild's tree

	delete node; //delete this node
	count ++; //increase count
	return count;
}

//accessor for root
Node* RedBlackTree::getRoot(){
	return root;
}



//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
//Note: duplicated node should not be added inside
void RedBlackTree::insertNode(Node *node){
    	Node *parent = NULL; //parent to be filled later
    	Node *current = root; //current pointer to move through tree

	while(current != NULL){ //while current is pointing to an existing node
		parent = current;
		if(node->airLine == current->airLine && node->flightNum == current->flightNum && node->deptDate == current->deptDate){ //if current & node info matches
        		cout << "Duplicated node. NOT added" << endl;
        		delete node;
			return;
    		}
		string nodeFlightStr = to_string(node->flightNum); //convert flight NodeFlighNum to string
		string currentFlightStr = to_string(current->flightNum); //convert currentFlightNum to string

		if(node->airLine < current->airLine){ //if nodeairline is less than current
			current = current->leftChild; //iterate down to left
		}else if(node->airLine > current->airLine){ //if nodeAirline is greater than current
			current = current->rightChild; //iterate down to right
		}else if(nodeFlightStr < currentFlightStr){ //if node flight num is less than current
			current = current->leftChild; //iterate down to left
		}else if(nodeFlightStr > currentFlightStr){ //if node flight num is greater than current
			current = current->rightChild; //iterated down to right
		}else if(node->deptDate < current->deptDate){ //if node dept date is less than current
			current = current->leftChild; //iterate down to left
		}else{
			current = current->rightChild;
		}
	} //once a place to inset is found:
	node->parent = parent; //set parent
	node->leftChild = NULL; //no left child
	node->rightChild = NULL; //no right child

	string nodeFlightStr = to_string(node->flightNum); //convert node flight num to string

	if(parent == NULL){ // new node is root
		root = node;
	}else{
    		string parentFlightStr = to_string(parent->flightNum); //convert parent flight to sting

    		if(node->airLine < parent->airLine){ //next 12 lines same as above but comparing to parent not current
        		parent->leftChild = node;
    		}else if(node->airLine > parent->airLine){
        		parent->rightChild = node;
    		}else if(nodeFlightStr < parentFlightStr){
        		parent->leftChild = node;
    		}else if(nodeFlightStr > parentFlightStr){
        		parent->rightChild = node;
    		}else if(node->deptDate < parent->deptDate){
        		parent->leftChild = node;
    		}else{
        		parent->rightChild = node;
    		}
	}
}

void RedBlackTree::leftRotate(Node *node){
    	Node *x = node->rightChild; //x is node right child
    	if(x == NULL) return; //cant rotate if right child is NULL

    	// x subtree becomes node subtree
    	node->rightChild = x->leftChild;
    	if(x->leftChild != NULL){
        	x->leftChild->parent = node;
	}

    	//link parents
    	x->parent = node->parent;
    	if(node->parent == NULL){
       		root = x; //x becomes root
	}else if(node == node->parent->leftChild){
        	node->parent->leftChild = x;
    	}else{
        	node->parent->rightChild = x;
	}

    	//put node on xs left
    	x->leftChild = node;
    	node->parent = x;
}

void RedBlackTree::rightRotate(Node *node){
    	Node *x = node->leftChild;   //x is node left child
    	if(x == NULL) return;       //cannot rotate if left child is NULL

    	//x subtree becomes node subtree
    	node->leftChild = x->rightChild;
    	if(x->rightChild != NULL){
        	x->rightChild->parent = node;
	}

    	//link parents
    	x->parent = node->parent;
    	if(node->parent == NULL){
        	root = x; //x becomes root
    	}else if(node == node->parent->leftChild){
        	node->parent->leftChild = x;
    	}else{
        	node->parent->rightChild = x;
	}

    	//put node on xs right
    	x->rightChild = node;
    	node->parent = x;
}

//fix property 4 violation
void RedBlackTree::fixUp(Node *node){
	if(node == NULL) return;
	while(node != root && node->parent != NULL && node->parent->color == "RED"){ //while parent is red and new node is not root
		Node *parent = node->parent; //set parent pointer
		Node *grandparent = parent->parent; //set grandparent pointer
		if(grandparent == NULL) break;

		if(parent == grandparent->leftChild){
			Node* uncle = grandparent->rightChild; //set uncle pointer

			if(uncle != NULL && uncle->color == "RED"){ //case #1
				parent->color = "BLACK"; //change parent color
				uncle->color = "BLACK"; //cahnge uncle color
				grandparent->color = "RED"; //change gp color
				node = grandparent;
			}else{ //case #2
				if(node == parent->rightChild){ //case #2.1
					leftRotate(parent);
					node = parent;
					parent = node->parent;
					grandparent = parent->parent;
				}else{ //case #2.2
					parent->color = "BLACK"; //change parent color
					grandparent->color = "RED"; //change gp color
					rightRotate(grandparent);
				}
			}
		}else{
			Node *uncle = grandparent->leftChild; //set uncle pointer

			if(uncle != NULL && uncle->color == "RED"){ //case #1
				parent->color = "BLACK"; //change parent color
				uncle->color = "BLACK"; //change uncle color
				grandparent->color = "RED"; //cahnge gp color
				node = grandparent;
			}else{
				if(node == parent->leftChild){ //case #2
					rightRotate(parent);
					node = parent;
					parent = node->parent;
					grandparent = parent->parent;
				}else{
					parent->color = "BLACK"; //change parent color
					grandparent->color = "RED"; //Change gp color
					leftRotate(grandparent);
				}
			}
		}
	}
	root->color = "BLACK"; //root always black no matter what
}

//performs preorderTraversal on given node
void RedBlackTree::preOrderTraversal(Node *node){
	if(node == NULL) return;
	print(node); //prints info of current node
	preOrderTraversal(node->leftChild); //performs preorder traveral on the left
	preOrderTraversal(node->rightChild); //performs preorder traversal on the right
}

//performs inorderTraversal on given node
void RedBlackTree::inOrderTraversal(Node *node){
	if(node == NULL) return;
	inOrderTraversal(node->leftChild); //in order traversal on left child
	print(node); //print this node
	inOrderTraversal(node->rightChild); //inorder traversal on right child
}

//performs postorderTraversal on given node
void RedBlackTree::postOrderTraversal(Node *node){
	if(node == NULL) return;
	postOrderTraversal(node->leftChild); //post order traversal on left child
	postOrderTraversal(node->rightChild); // post order traversal on right child
	print(node); //print current node
}

Node* RedBlackTree::findMinimumNode(Node *node){
	if(node == NULL || node->leftChild == NULL){
		return node;
	}
	return findMinimumNode(node->leftChild); //recursivley search left children until no child is found
}

Node* RedBlackTree::findMaximumNode(Node *node){
    	if(node == NULL || node->rightChild == NULL){
        	return node;
	}
    	return findMaximumNode(node->rightChild); //reccursively search right unitl no child is found
}

Node* RedBlackTree::treeSearch(string airLine, int flightNum, string deptDate){
    	Node *current = root;

    	while(current != NULL){
        	//check for exact match
        	if(current->airLine == airLine && current->flightNum == flightNum && current->deptDate == deptDate){
            		cout << left;
            		cout << setw(5) << airLine
                 	     << setw(10) << flightNum << " on "
                 	     << setw(12) << deptDate << " is found" << endl;
            		return current;
        	}

		string flightStr = to_string(flightNum); //convert flightNum input to string
		string currentFlightStr = to_string(current->flightNum); //convert current flightnum to string

        	//compare airlines, flightnums, and dept dates as before
        	if(airLine < current->airLine){
            		current = current->leftChild;
        	}else if(airLine > current->airLine){
            		current = current->rightChild;
        	}else if(flightStr < currentFlightStr){
            		current = current->leftChild;
        	}else if(flightStr > currentFlightStr){
            		current = current->rightChild;
        	}else if(deptDate < current->deptDate){
            		current = current->leftChild;
		}else{
            		current = current->rightChild;
		}
    	}

    	//not found
    	cout << left;
    	cout << setw(5) << airLine
             << setw(10) << flightNum << " on "
             << setw(12) << deptDate << " is NOT found" << endl;
    	return NULL;
}

Node* RedBlackTree::findPredecessorNode(Node *node){
    	Node *predecessor = NULL;

    	//if left subtree exist: predecessor is its maximum
    	if(node->leftChild != NULL){
        	predecessor = findMaximumNode(node->leftChild);
    	}else{
        	//go up until we find a parent where node is in the right subtree
        	Node *current = node;
        	while (current->parent != NULL && current == current->parent->leftChild){
            		current = current->parent;
        	}
        	predecessor = current->parent;
    	}

    	if(predecessor != NULL){
        	cout << "Its Predecessor is: " << endl;
        	cout << left;
        	cout << setw(5)  << predecessor->airLine
        	     << setw(10) << predecessor->flightNum
        	     << setw(12) << predecessor->deptDate
        	     << right << setw(7) << predecessor->color << endl;
    	}else{
        	cout << "Its Predecessor does NOT exist" << endl;
    	}
    	return predecessor;
}

Node* RedBlackTree::findSuccessorNode(Node *node){
    	Node *successor = NULL;

    	//if right subtree exists: successor is its minimum
    	if(node->rightChild != NULL){
        	successor = findMinimumNode(node->rightChild);
    	}else{
        	//go up until we find a parent where node is in the left subtree
        	Node *current = node;
        	while(current->parent != NULL && current == current->parent->rightChild){
        	    	current = current->parent;
        	}
        	successor = current->parent;
    	}

    	if(successor != NULL){
        	cout << "Its Successor is: " << endl;
        	cout << left;
        	cout << setw(5)  << successor->airLine
        	     << setw(10) << successor->flightNum
        	     << setw(12) << successor->deptDate
        	     << right << setw(7) << successor->color << endl;
    	}else{
        	cout << "Its Successor does NOT exist" << endl;
    	}
    	return successor;
}

void RedBlackTree::treeMinimum(){
	if(root == NULL){
		cout << "Tree is empty" << endl;
		return;
	}else{
		Node *min = findMinimumNode(root); //call min from root

		cout << "The MINIMUM is:" << endl;
    		cout << left;
    		cout << setw(5)  << min->airLine
    		     << setw(10) << min->flightNum
    		     << setw(12) << min->deptDate
       		     << right << setw(7) << min->color << endl;
	}
}

void RedBlackTree::treeMaximum(){
	if(root == NULL){
		cout << "Tree is empty" << endl;
		return;
	}else{
		Node *max = findMaximumNode(root);  //call max from root

		cout << "The MAXIMUM is:" << endl;
    		cout << left;
    		cout << setw(5)  << max->airLine
    		     << setw(10) << max->flightNum
    		     << setw(12) << max->deptDate
       		     << right << setw(7) << max->color << endl;
	}
}

void RedBlackTree::treePreorder(){
	preOrderTraversal(root); //call traversal from root
}

void RedBlackTree::treeInorder(){
	inOrderTraversal(root); //call traversal from root
}

void RedBlackTree::treePostorder(){
	postOrderTraversal(root); //call traversal from root
}

void RedBlackTree::treePredecessor(string airLine, int flightNum, string deptDate){
	Node *node = treeSearch(airLine, flightNum, deptDate); //search for nod

	if(node != NULL){
		Node *predecessor = findPredecessorNode(node); //call predecessor if node found
	}else{
		cout << "Its Predecessor does NOT exist" << endl;
	}
}

void RedBlackTree::treeSuccessor(string airLine, int flightNum, string deptDate){
	Node *node = treeSearch(airLine, flightNum, deptDate); //search for node

	if(node != NULL){
		Node *successor = findSuccessorNode(node); //call successor if node found
	}else{
		cout << "Its Successor does NOT exist" << endl;
	}
}

void RedBlackTree::treeInsert(string airLine, int flightNum, string deptDate){
	Node *node = new Node; //create new node
	node->airLine = airLine; //set airline
	node->flightNum = flightNum; //set flightnum
	node->deptDate = deptDate; //set dept dadte
	node->color = "RED"; //set color to red
	node->leftChild = NULL; //no child
	node->rightChild = NULL; //no child
	node->parent = NULL; //no parent yet

	insertNode(node); //insert
	fixUp(node); //fix
}

//Given a 'node', this function prints the node information on screen
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(5)  << node->airLine
           << setw(10) << node->flightNum
           << setw(12) << node->deptDate;
      cout << right << setw(7) << node->color << endl;
}
