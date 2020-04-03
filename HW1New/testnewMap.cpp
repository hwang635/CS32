
#include "newMap.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.insert("Fred", 2.956));
	assert(m.insert("Ethel", 3.538));
	assert(m.size() == 2);
	ValueType v = 42;
	assert(!m.get("Lucy", v) && v == 42);
	assert(m.get("Fred", v) && v == 2.956);
	v = 42;
	KeyType x = "Lucy";
	assert(m.get(0, x, v) &&
		((x == "Fred" && v == 2.956) || (x == "Ethel" && v == 3.538)));
	KeyType x2 = "Ricky";
	assert(m.get(1, x2, v) &&
		((x2 == "Fred" && v == 2.956) || (x2 == "Ethel" && v == 3.538)) &&
		x != x2);
} 

int main()
{
	test();
	cout << "Passed all tests" << endl;
}

/*#include "newMap.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m1;  // maps strings to doubles
	assert(m1.empty());
	ValueType v = -1234.5;
	assert(!m1.get("abc", v) && v == -1234.5); // v unchanged by get failure
	m1.insert("xyz", 9876.5);
	assert(m1.size() == 1);
	KeyType k = "hello";
	assert(m1.get(0, k, v) && k == "xyz" && v == 9876.5);
	cout << "Passed all tests" << endl;

	Map m2(3);
	m2.insert("A", 10);
	m2.insert("B", 44);
	m2.insert("C", 10);
	string all;
	double total = 0;
	for (int n = 0; n < m2.size(); n++)
	{
		string k;
		double v;
		m2.get(n, k, v);
		all += k;
		total += v;
	}
	cerr << all << total << endl;

	Map gpas;
	gpas.insert("Fred", 2.956);
	gpas.insert("Ethel", 3.538);
	double v2;
	string k1;
	assert(gpas.get(1, k1, v2) && (k1 == "Fred" || k1 == "Ethel"));
	string k2;
	assert(gpas.get(1, k2, v2) && k2 == k1);
	cerr << "Passed gpas three-arg get test" << endl;

	Map m3;
	m3.insert("Fred", 2.956);
	m3.insert("", -1);
	Map m4;
	m4.insert("Ethel", 3.538);
	m4.insert("Lucy", 2.956);
	m4.insert("ETHel", 2.956);
	m4.insert("", 100);
	m3.swap(m4);
	//assert(m3.size() == 3 && m3.contains("Ethel") && m3.contains("ETHel") && m3.contains("Lucy") && m4.size()
		// == 0 && m4.empty());
	assert(m3.size() == 4 && m3.contains("Ethel") && m3.contains("ETHel") && m3.contains("Lucy") && m3.contains("") &&
		m4.size() == 2 && m4.contains("Fred") && m4.contains(""));
	cerr << "Passed swap test" << endl;

	Map m5;
	assert(!m1.empty() && !m2.empty() && !m3.empty() && !m4.empty() && m5.empty());
	cerr << "Passed empty test" << endl;

	assert(m5.insert("Bob", 123) && !m5.insert("Bob", -12.3) && m5.insert("bob", 123) && m5.insert("Cat", -0.099));
		//&& !m5.insert("full", 5.3));
	m5.dump();
	cerr << "Passed insert test?" << endl;

	assert(m5.update("Bob", 345.6) && !m5.update("BOB", 12) && !m5.update("dog", 5));
	m5.dump();
	cerr << "Passed update test?" << endl;

	assert(m5.insertOrUpdate("Robert", 0.005) && m5.insertOrUpdate("Cat", -1.2) && m5.insertOrUpdate("BOb", 5));
	m5.dump();
	cerr << "Passed insert or update test?" << endl;

	assert(!m5.erase("dog") && m5.erase("Robert") && !m5.erase(""));
	m5.dump();
	Map m6;
	assert(!m6.erase(""));
	m6.dump();
	cerr << "Passed erase test?" << endl;

	double testVal = 0;
	//m5.get("Bob", testVal);
	assert(m5.get("Bob", testVal) && testVal == 345.6);
	assert(!m5.get("dog", testVal) && testVal == 345.6);
	cerr << "testVal = " << testVal << endl;
	m5.dump();
	cerr << "Passed two-arg get test?" << endl;

	/*Map a(1000);   // a can hold at most 1000 key/value pairs
	Map b(5);      // b can hold at most 5 key/value pairs
	Map c;         // c can hold at most DEFAULT_MAX_ITEMS key/value pairs
	KeyType k[6] = {"one", "two", "three", "four", "five", "six"};
	ValueType v = 6;

	// No failures inserting pairs with 5 distinct keys into b
	for (int n = 0; n < 5; n++)
		assert(b.insert(k[n], v));

	//b.dump();

	// Failure if we try to insert a pair with a sixth distinct key into b
	assert(!b.insert(k[5], v));

	// When two Maps' contents are swapped, their capacities are swapped
	// as well:
	a.insert("cat", 50);
	a.swap(b);
	//a.insert(k[5], v);
	//b.insert(k[5], v);
	//a = b;
	//cerr << "a = b" << endl;
	a.dump();
	b.dump();
	assert(!a.insert(k[5], v) && b.insert(k[5], v));
	
	cerr << "Passed some test" << endl; 

} */

/*//mapping int to string
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Map m;  // maps ints to strings
	assert(m.empty());
	ValueType v = "Ouch";
	assert(!m.get(42, v) && v == "Ouch"); // v unchanged by get failure
	m.insert(123456789, "Wow!");
	assert(m.size() == 1);
	KeyType k = 9876543;
	assert(m.get(0, k, v) && k == 123456789 && v == "Wow!");
	cout << "Passed all tests" << endl;
} */