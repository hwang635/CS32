#include "Map.h"
#include <iostream>
using namespace std;

Map::Map() //Creates empty map/linked list
	: m_size(0)
{
	head = nullptr;
}

//Destructor: when Map obj deleted, nodes in linked list must be dealloc
Map::~Map() {
	Node* temp = head;
	while (temp != nullptr) { //Loop through until no more Nodes to delete
		Node* tempNext = temp->next; //Store next node, so access isn't lost when current node is deleted
		delete temp; //Delete current node
		temp = tempNext; //Go to the next node
	}
}

//Copy constructor: when new Map created as copy of existing Map, enough new nodes must be alloc to hold duplicate of orig list
Map::Map(const Map& other) {
	this->head = nullptr; //Init head pointer

	Node* temp = other.head;
	//Loop through all items, stop when reach no more items
	while (temp != nullptr) {
		//ERROR: was incrementing size two times bc addToFront also increments size
		//moved this->m_size = other.m_size to bottom
		this->addToFront(temp->m_key, temp->m_value); //Add key+value pair to front of linked list
		temp = temp->next;
	}

	this->m_size = other.m_size;
}

//Assignment op: Copied object sb duplicate of other obj with no memory leak of list nodes
Map& Map::operator=(const Map& other) {
	//If other is the same as the current map, don't delete this and return
	if (&other == this)
		return *this;

	//Delete current nodes in list
	Node* temp = this->head;
	while (temp != nullptr) { //Loop through until no more Nodes to delete
		Node* tempNext = temp->next; //Store next node, so access isn't lost when current node is deleted
		delete temp; //Delete current node
		temp = tempNext; //Go to the next node
	}

	this->m_size = 0; //(Add to front increments m_size)

	//Loop through all items in other list m_data and add key+value pair to front of list
	this->head = nullptr; //Init head pointer
	temp = other.head;
	while (temp != nullptr) {
		this->addToFront(temp->m_key, temp->m_value);
		temp = temp->next;
	}

	this->m_size = other.m_size;
	return *this;
}

//Adds key+value pair to top of linkedlist, increments size
void Map::addToFront(const KeyType& key, const ValueType& value) {
	//Alloc and put key+value in new node
	Node* n = new Node;
	n->m_key = key;
	n->m_value = value;

	//Link new node to old top/head node
	n->next = head;
	n->prev = nullptr; //New node is first, so prev pointer doesn't point to anything

	//Link head pointer to new top node
	head = n; //

	m_size++;
}

//Returns true if the linked list contains a key+value pair w/the parameter key, false if not
bool Map::contains(const KeyType& key) const {
	if (head == nullptr) //List is empty, so can't contain that key
		return false;

	Node* temp = head;
	while (temp != nullptr) { //Loop through all Nodes, stop right when reach end of list
		if (temp->m_key == key)
			return true;
		temp = temp->next;
	}

	return false;
}

//Update key+value pair in map w/ matching key so that the key maps to parameter value
//Return true if successful, false is not
bool Map::updateItem(const KeyType& key, const ValueType& value) {
	Node* temp = head;

	//Loop through all valid nodes until reach end of list
	while (temp != nullptr) {
		if (temp->m_key == key) { //If a node has matching key, update value and return true
			temp->m_value = value;
			return true;
		}
		temp = temp->next;
	}

	return false;
}

//If parameter key matches key currently in map, remove key+value pair from map and return true
//If parameter key isn't in map, don't change map and return false
bool Map::erase(const KeyType& key)
{
	if (head == nullptr) //If list is empty, nothing to delete so immediately return
		return false;

	//If the key isn't in the map, immediately return false
	if (!contains(key))
		return false;

	//Otherwise, delete the key+value pair, decrement the size counter, and return true
	if (head->m_key == key) { //If top node has the matching key
		Node* deleteMe = head; //Address of top node
		head = deleteMe->next; //Update head to point to second node
		delete deleteMe; //Delete target top node

		//ERROR: forgot to decrement size
		m_size--;
		return true;
	}

	Node* temp = head;
	//Loops until finds node above the to-delete node or reaches end of list
	while (temp != nullptr) { //Check that ptr is valid
		if (temp->next != nullptr && temp->next->m_key == key) //Finds node right above to-delete node w/ matching key
			break;

		temp = temp->next;
	}

	//If target node has been found
	if (temp != nullptr) {
		Node* deleteMe = temp->next; //Address of node to-delete
		temp->next = deleteMe->next; //Link node above to node below
		//ERROR: If the node to be delete is the last node ==> its next ptr is nullptr, so don't link its next prev to temp
		//If the node after the deleteNode exists, link it's prev pointer to temp
		//Otherwise, if it doesn't exist just link temp's next to it
		if(deleteMe->next != nullptr) 
			deleteMe->next->prev = temp; //Link node below to node above
		delete deleteMe;
		m_size--;
		return true;
	}

	return false;
}

//If parameter key matches key already in map, set parameter value to value of key+value pair and return true
//If parameter key isnt in map, don't change value parameter and return false
bool Map::get(const KeyType& key, ValueType& value) const {
	//If the list doesn't contain the item, return false
	if (!contains(key))
		return false;

	//Otherwise, call linkedlist's getvalue function to copy the value key maps into value
	Node* temp = head;
	while (temp != nullptr) {
		if (temp->m_key == key) {
			value = temp->m_value;
			return true;
		}
		temp = temp->next;
	}
	return false;
}

//If i <= 0 and < size(), copy into key and value parameters key and value of key+value pair at i position in map and return true
//Otherwise, don't change key and value parameters and return false
bool Map::get(int i, KeyType& key, ValueType& value) const {
	//i is out of bounds, return false
	if (i < 0 || i >= m_size)
		return false;

	Node* temp = head;
	for (int k = 0; k < i; k++) { //Loops until temp equals #i node in list
		if(temp != nullptr)
			temp = temp->next;
	}

	if (temp != nullptr) { //Founds node at #i position, if temp = nullptr didn't find node there
		key = temp->m_key;
		value = temp->m_value;
		return true;
	}

	return false;
}

void Map::swap(Map& other) {
	//Swap size count
	int tempSize = this->m_size;
	this->m_size = other.m_size;
	other.m_size = tempSize;

	//Swap linked lists swapping each map's head Node pointers
	Node* tempHead = this->head;
	this->head = other.head;
	other.head = tempHead;
}

//If parameter key matches key in map, update key+value pair in map so that key maps to parameter value and return true
//If parameter key isn't in map, add key+value pair to map and return true
bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
	bool mayInsert, bool mayUpdate) {

	//If can insert, insert if list doesn't contain key and increment size counter
	if (mayInsert && !contains(key)) {
		this->addToFront(key, value);
		return true;
	}

	//If can update, update if the item is in the map and return true
	if (mayUpdate && contains(key)) {
		this->updateItem(key, value);
		return true;
	}

	return false; //If could't insert or update, return false
}

//For testing, prints key+value pair for each Node in list
void Map::dump() {
	for (int i = 0; i < this->size(); i++) {
		KeyType k;
		ValueType v;
		this->get(i, k, v);
		cerr << i << " key=" << k << " value=" << v << endl;
	}

	cerr << "size = " << size() << endl;
}

//--------Aux functions

//If key is present in either m1 or m2, adds key+value pair to result
//If key is present in both and value is the same, adds key+value pair to result
//If key is present in both and value is different, doesn't add pair to result and returns false
bool combine(const Map& m1, const Map& m2, Map& result) {
	Map output;
	bool b = true;
	
	//Loops through every key+value pair/Node in m1
	for (int i = 0; i < m1.size(); i++) {
		KeyType k;
		ValueType v;
		m1.get(i, k, v); //Sets k, v equal to key+value pair in #i position
		
		//If m1 contains the key and m2 doesn't, add the key+value pair to result
		if (!m2.contains(k))
			output.insert(k, v);
		else if (m2.contains(k)) {
			ValueType v2;
			m2.get(k, v2); //Sets v2 equal to value k maps to in m2
			//If m2 contains the key also, add the pair if both keys map to the same value
			if (v2 == v)
				output.insert(k, v);
			//If m2 contains the key also but the keys map to different values, don't add the key+value pair and return false at end
			else
				b = false;
		}
	} //end of m1 loop

	//Loops through every key+value pair/Node in m2
	for (int i = 0; i < m2.size(); i++) {
		KeyType k;
		ValueType v;
		m2.get(i, k, v);

		//If output already contains this key, the key has already been evaluated so go to next key+value pair
		//Otherwise, check if the key at this position sb added to result
		if (!output.contains(k)) {
			//If the key is only in m2, add the key_value pair to result
			//If the key is also in m1, do nothing bc it should already have been eval in the previous loop
			if (!m1.contains(k))
				output.insert(k, v);
		}
	}

	result = output; //Sets result equal to new Map created, uses copy constructor/assignment operator
	return b;
}

//Reassigns every key+value pair so that each key switches its value with another key, each key only switches one value
//Don't assume result is empty, if m has only one pair result is a copy of the one pair
void reassign(const Map& m, Map& result) {
	//If m only has one pair, result is a copy of the one pair; if m is empty, result is empty too
	if (m.size() == 1 || m.size() == 0) {
		result = m; //Set result equal to m, uses assign op
		return;
	}

	Map output;

	KeyType firstK;
	ValueType firstV;
	m.get(0, firstK, firstV); //Store the first pair in Map

	//Loops through first to second-last pairs in Map
	int i;
	for (i = 0; i < m.size() - 1; i++) {
		KeyType currentK;
		KeyType nextK;
		ValueType v;
		m.get(i, currentK, v); //Stores the key of the current pair in currentK
		m.get(i + 1, nextK, v); //Stores the key and value of the pair following current pair in nextK, v
		
		output.insert(currentK, v); //Adds key to map, key now maps to orig value of the pair after it
	}

	//Last pair doesn't have a pair after it, so it maps to the orig value of the first pair
	KeyType lastK;
	ValueType lastV;
	m.get(i, lastK, lastV); //Find the key of the last pair in Map
	output.insert(lastK, firstV);

	result = output; //Set result equal to the newly-created reassigned map
}