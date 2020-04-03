
/*#include "CarMap.h"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
	CarMap cm;
	cm.print();
	cerr << "Test constructor" << endl;

	assert(cm.addCar("license1") && cm.addCar("LICense1") && !cm.addCar("license1")
		&& cm.addCar("lic2") && cm.addCar("license3"));
	cm.print();
	cerr << "Test addCar" << endl;

	assert(cm.miles("license1") == 0 && cm.miles("LICENSE1") == -1 && cm.miles("lic2") == 0);
	cerr << "Test miles" << endl;

	assert(cm.drive("license1", 25) && !cm.drive("license4", 10) && !cm.drive("license1", -1)
		&& !cm.drive("lic2", -100) && cm.drive("lic2", 0) && cm.drive("license3", 10.5));
	cm.print();
	cerr << "Test drive" << endl;

	assert(cm.miles("license1") == 25);
	cerr << "Test miles again" << endl;
} */