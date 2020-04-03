
/*#include "CarMap.h"
#include <iostream>
#include <string>
using namespace std;

//Creates empty car map
CarMap::CarMap() {}


//If car w/ given license isn't already in map and map isn't full, add entry for that car w/ 0 miles and return true
//Otherwise, don't change map and return false
bool CarMap::addCar(string license) {
	//If map already has license, will return false
	//If map doesn't have license, will insert license and return true
	return m_map.insert(license, 0);
}

//If car w/ given license is in map, return how many miles that car has driven/maps to
//If car isn't in map, return -1
double CarMap::miles(string license) const {
	double mi = -1;

	//If license is in map, will change value of mi to value key = license maps to
	//If not, mi will be unchanged
	m_map.get(license, mi);

	return mi;
}

//If car w/ given license is in map, increase value car maps to by distance parameter and return true
//If car isn't in map or distance is negative, don't change anything and return false
bool CarMap::drive(string license, double distance) {
	if (distance < 0)
		return false;

	//Finds miles already driven if car is in map
	double milesDriven = this->miles(license);

	//If car is in map, finds car, updates value to set equal to miles driven + distance and return true
	//If car isn't in map, return false
	return m_map.update(license, milesDriven + distance);
}

//Return number of cars in CarMap
int CarMap::fleetSize() const {
	return m_map.size();
}


//Cout one line for every car in map: license plate, one space, number of miles car has driven
//No other text, no particular order
void CarMap::print() const {
	for (int i = 0; i < this->fleetSize(); i++) {
		string k;
		double v;
		m_map.get(i, k, v);
		cout << k << " " << v << endl;
	}

	//REMOVE LINE LATER
	//cerr << "car map size = " << this->fleetSize() << endl;
} */