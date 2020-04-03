
#include "newMap.h"
#include <iostream>
using namespace std;

Map::Map() {
	m_numItems = 0;
	m_max = DEFAULT_MAX_ITEMS;
	items = new Item[m_max]; //new commands reserves memory for ptr array
}

Map::Map(int max) {
	m_numItems = 0;
	m_max = max;
	items = new Item[m_max];
}

//Copy constructor
Map::Map(const Map& src) {
	m_max = src.m_max; //How much memory to be alloc
	m_numItems = src.m_numItems; //Same # of key/value pairs
	items = new Item[m_max]; //Alloc same amount of memory in new ptr arr

	for (int i = 0; i < m_max; i++) //Copy src array contents into this array
		items[i] = src.items[i];

}

//Destructor
Map::~Map() {
	delete[] items;
}

//Assignment op
Map& Map::operator=(const Map& src) {
	delete[] items; //Free current memory
	m_max = src.m_max; //Find how much memory to be alloc, so this same as src
	m_numItems = src.m_numItems; //Same # of key/value pairs
	items = new Item[m_max]; //Alloc same amount of memory in this ptr arr
	for (int i = 0; i < m_max; i++) //Copy src array contents into this arr
		items[i] = src.items[i];

	return *this; //Return ref to target var
}

//Return true if map is empty, false if not
bool Map::empty() const {
	if (m_numItems == 0)
		return true;
	else
		return false;
}

//Return # of key/value pairs in map
int Map::size() const {
	return m_numItems;
}

//If parameter key isn't a key in the map and the key/value pair can be added to the map, add it and return true
//Otherwise, don't change map and return false (key already in map or map is full)
bool Map::insert(const KeyType& key, const ValueType& value) {
	//If key already exists in map, return false
	if (contains(key))
		return false;
	//Map is at capacity so no more room, return false
	if (m_numItems == m_max)
		return false;

	//Create new Item struct w/ key, value
	Item it;
	it.m_key = key;
	it.m_value = value;

	//Add to array and increment number of items
	items[m_numItems] = it;
	m_numItems += 1;

	return true;
}

//If parameter key already exists in map, change it so that the key maps to parameter value instead of orig value
//If key is updated return true, if key isn't in the map don't change map and return false
bool Map::update(const KeyType& key, const ValueType& value) {
	//Check if map contains the key
	if (contains(key)) {
		//Loop through each item in items array
		for (int i = 0; i < m_numItems; i++) {
			//If key matches parameter key, change value key maps to and return true
			if (items[i].m_key == key) {
				items[i].m_value = value;
				return true;
			}
		}
	}

	return false;
}

//If parameter key already exists in map, change value key maps to to parameter value and return true
//If key doesn't exist in map and key/value pair can be added to map, insert in map and return true
//If key isn't in map and map is full, return false
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	//If key can be inserted, return true
	if (insert(key, value))
		return true;
	//If it can't be inserted, check if map can be updated and return true if updated
	if (update(key, value))
		return true;

	return false;
}

//If parameter key already exists in map, remove that key/value pair from map and return true
//If doesn't already exist in map, don't change map and return false
bool Map::erase(const KeyType& key) {
	if (contains(key)) {
		//Loop through items until find item w/ matching key
		for (int i = 0; i < m_numItems; i++) {
			if (items[i].m_key == key) {
				//Move all items after matching item up by one to "remove" key
				//If item is last item, will remain in array but "hidden" bc m_numItems is decreased
				for (int j = i; j < m_numItems - 1; j++)
					items[j] = items[j + 1];
			}
		}
		//After key/value pair has been erased, decrement number of items and return true
		m_numItems--;
		return true;
	}

	return false;
}

//Returns true is parameter key is equal to key that already exists in map
//Returns false if key doesn't already exist in map
bool Map::contains(const KeyType& key) const {
	//Loop through each item in array for number of items that exist
	for (int i = 0; i < m_numItems; i++) {
		//If an item has same key name as parameter, return true
		if (items[i].m_key == key)
			return true;
	}

	return false;
}

//If parameter key matches key already in map, set parameter value to value that key in map maps to and return true
//If parameter key doens't exist in map, don't change parameter value and return false
bool Map::get(const KeyType& key, ValueType& value) const {
	//If parameter key exists in map, find the item w/ the key and set value to the key's value
	if (contains(key)) {
		for (int i = 0; i < m_numItems; i++) {
			if (items[i].m_key == key) {
				value = items[i].m_value;
				return true;
			}
		}
	}

	return false;
}

//If 0 <= i < size(), copy key and value of one of the key/value pairs in map and return true
//If i isn't btw O and size(), don't change key and value and return false
//Should return distinctive items if called w/ different i and array isn't changed
bool Map::get(int i, KeyType& key, ValueType& value) const {
	//If i is w/in bounds, set key/value = to key/value pair at i location in items array
	if (i >= 0 && i < size()) {
		key = items[i].m_key;
		value = items[i].m_value;
		return true;
	}

	return false;
}

//Swap content of this map w/ parameter map
void Map::swap(Map& other) {
	//Swap contents of map by swapping pointers of item arrays
	Item* temp = this->items;
	this->items = other.items;
	other.items = temp;

	//Swap value for max
	int tempMax = this->m_max;
	this->m_max = other.m_max;
	other.m_max = tempMax;

	//Swap counter for # of key/value pairs
	int tempNumItems = this->m_numItems;
	this->m_numItems = other.m_numItems;
	other.m_numItems = tempNumItems;
}

//Testing purposes, prints outs all items in map
void Map::dump() const {
	for (int i = 0; i < m_numItems; i++) {
		cerr << i << " key = " << items[i].m_key << " value = " << items[i].m_value << endl;
	}
	cerr << "map size = " << this->size() << endl;
}

