#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

/* Remove the odd integers from list
// It is acceptable if the order of the remaining even integers is not
// the same as in the original list.
void removeOdds(list<int>& li)
{
	list<int>::iterator itr; //Declare iterator
	itr = li.begin(); //Set itr to pt to first item in container

	while (itr != li.end()) { //Loop through items until itr points past last item
		if (*itr % 2 == 1) //If itr points to an odd #, erase # + set itr equal to element after erased one
			itr = li.erase(itr);
		else
			itr++; //If don't erase, ++ itr b/c no memory shuffle
	}
} 

void test()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	list<int> x(a, a + 8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	vector<int> v(x.begin(), x.end());  // construct v from x
	sort(v.begin(), v.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(v[k] == expect[k]);
}

int main() {
	test();
	cout << "Passed" << endl;
} */