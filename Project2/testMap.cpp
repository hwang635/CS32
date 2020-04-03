#/*include "Map.h"
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
	cerr << "Passed all tests" << endl;

	Map m2;	
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
	gpas.dump();
	assert(gpas.get(1, k1, v2) && (k1 == "Fred" || k1 == "Ethel"));
	string k2;
	assert(gpas.get(1, k2, v2) && k2 == k1);
	cerr << "Passed gpas three-arg get test" << endl;

	Map m3; //m3 should be Fred, ""
	m3.insert("Fred", 2.956);
	m3.insert("", -1);
	Map m4; //m4 should be Ethel, Lucy, ETHel, ""
	m4.insert("Ethel", 3.538);
	m4.insert("Lucy", 2.956);
	m4.insert("ETHel", 2.956);
	m4.insert("", 100);
	m3.swap(m4); //m3 sb Ethel, Lucy, ETHel and m4 sb Fred, ""
	m3.dump();
	m4.dump();
	assert(m3.size() == 4);
	assert(m3.contains("Ethel"));
	assert(m3.contains("ETHel"));
	assert(m3.contains("Lucy"));
	assert(m3.contains(""));
	assert(m4.size() == 2);
	assert(m4.size() == 2); //is calling copy constructor??
	assert(m4.contains("Fred"));
	assert(m3.size() == 4 && m3.contains("Ethel") && m3.contains("ETHel") && m3.contains("Lucy") && m3.contains("") &&
		m4.size() == 2 && m4.contains("Fred") && m4.contains(""));
	cerr << "Passed swap test" << endl;

	Map m5;
	assert(!m1.empty() && !m2.empty() && !m3.empty() && !m4.empty() && m5.empty());
	cerr << "Passed empty test" << endl;

	assert(m5.insert("Bob", 123) && !m5.insert("Bob", -12.3) && m5.insert("bob", 123) && m5.insert("Cat", -0.099));
	//&& !m5.insert("full", 5.3));
	m5.dump(); //m5 should have Bob, bob, Cat
	assert(m5.contains("Bob") && m5.contains("bob") && m5.contains("Cat") && m5.size() == 3);
	cerr << "Passed insert test" << endl;

	assert(m5.update("Bob", 345.6) && !m5.update("BOB", 12) && !m5.update("dog", 5));
	m5.dump(); //m5 should have Bob 345.6, bob 123, Cat -0.099
	assert(!m5.contains("dog") && !m5.contains("BOB"));
	cerr << "Passed update test?" << endl;

	assert(m5.insertOrUpdate("Robert", 0.005) && m5.insertOrUpdate("Cat", -1.2) && m5.insertOrUpdate("BOb", 5));
	m5.dump(); //m5 should have Bob 345.6, bob 123, Cat -1.2, Robert 0.005, BOb 5
	assert(m5.contains("Robert") && m5.contains("BOb"));
	cerr << "Passed insert or update test?" << endl;

	assert(!m5.erase("dog") && m5.erase("Robert") && !m5.erase(""));
	m5.dump(); //m5 should have Bob, bob, Cat, BOb, 
	Map m6;
	assert(!m6.erase("")); //m6 is empty
	m6.dump();
	cerr << "Passed erase test?" << endl;

	double testVal = 0;
	//m5.get("Bob", testVal);
	assert(m5.get("Bob", testVal) && testVal == 345.6);
	assert(!m5.get("dog", testVal) && testVal == 345.6);
	cerr << "testVal = " << testVal << endl;
	m5.dump();
	cerr << "Passed two-arg get test" << endl;

	//Test combine
	Map c1;
	Map c2;
	assert(combine(c2, c1, c1));
	cerr << "Passed empty test?" << endl;
	c1.insert("Fred", 123);
	c1.insert("Ethel", 456);
	c1.insert("Lucy", 789);
	c2.insert("Lucy", 789);
	c2.insert("Ricky", 321);
	Map result;
	//Result sb: Lucy 789, Fred 123, Ethel 456, Ricky 321 + return true
	assert(combine(c2, c1, result) && result.size() == 4);
	result.dump();
	cerr << "Passed combine 1st test?" << endl;

	c2.insertOrUpdate("Lucy", 654);
	//assert(!combine(c1, c2, c1));
	assert(!combine(c2, c1, result) && !result.contains("Lucy") && result.size() == 3);
	//Result rb: Fred 123, Ethel 456, Ricky 321 + return false
	result.dump();
	cerr << "Passed combine 2nd test?" << endl;

	assert(!combine(c1, c2, c1) && c1.size() == 3);
	c1.dump();
	cerr << "Passed combine 3rd test?" << endl;

	//Test reassign
	Map r1;
	r1.insert("Fred", 123);
	r1.insert("Ethel", 456);
	r1.insert("Lucy", 789);
	r1.insert("Ricky", 321);
	r1.dump();

	Map res;
	reassign(r1, res);
	res.dump();
	assert(res.size() == 4);
	cerr << "Passed reassign test?" << endl;

	Map r2;
	reassign(r2, res);
	res.dump();
	cerr << "Passed reassign empty test?" << endl;
	r2.insert("Fred", 123);
	reassign(r2, res);
	res.dump();
	cerr << "Passed reassign one pair test?" << endl;
	r2.insert("Ethel", 456);
	r2.insert("Lucy", 456);
	r2.dump();
	reassign(r2, r2);
	r2.dump();
	cerr << "Passed reassign 2nd test?" << endl;
} */

/*#include "Map.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = static_cast<t>(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
	"Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
	"Map must be copy-constructible.");
static_assert(std::is_copy_assignable<Map>::value,
	"Map must be assignable.");

void ThisFunctionWillNeverBeCalled()
{
	CHECKTYPE(&Map::operator=, Map & (Map::*)(const Map&));
	CHECKTYPE(&Map::empty, bool (Map::*)() const);
	CHECKTYPE(&Map::size, int  (Map::*)() const);
	CHECKTYPE(&Map::insert, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::update, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::erase, bool (Map::*)(const KeyType&));
	CHECKTYPE(&Map::contains, bool (Map::*)(const KeyType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(const KeyType&, ValueType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(int, KeyType&, ValueType&) const);
	CHECKTYPE(&Map::swap, void (Map::*)(Map&));

	CHECKTYPE(combine, bool (*)(const Map&, const Map&, Map&));
	CHECKTYPE(reassign, void (*)(const Map&, Map&));
}

int main()
{} */

/*#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.insert("Fred", 123));
	assert(m.insert("Ethel", 456));
	assert(m.size() == 2);
	ValueType v = 42;
	assert(!m.get("Lucy", v) && v == 42);
	assert(m.get("Fred", v) && v == 123);
	v = 42;
	KeyType x = "Lucy";
	assert(m.get(0, x, v) &&
		((x == "Fred" && v == 123) || (x == "Ethel" && v == 456)));
	KeyType x2 = "Ricky";
	assert(m.get(1, x2, v) &&
		((x2 == "Fred" && v == 123) || (x2 == "Ethel" && v == 456)) &&
		x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
} */

/*
#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Map m;
	assert(m.insert(10, "diez"));
	assert(m.insert(20, "veinte"));
	assert(m.size() == 2);
	ValueType v = "cuarenta y dos";
	assert(!m.get(30, v) && v == "cuarenta y dos");
	assert(m.get(10, v) && v == "diez");
	v = "cuarenta y dos";
	KeyType x = 30;
	assert(m.get(0, x, v) &&
		((x == 10 && v == "diez") || (x == 20 && v == "veinte")));
	KeyType x2 = 40;
	assert(m.get(1, x2, v) &&
		((x2 == 10 && v == "diez") || (x2 == 20 && v == "veinte")) &&
		x != x2);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
} */