
#include <iostream>
#include <cassert>
using namespace std;

/*void printArr(double a[], int n) {
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

//Switch two doubles
void exchange(double& x, double& y) {
	double t = x;
	x = y;
	y = t;
}

//Rearrange elements of array so all elements > separator come before all other elements
//All elements < seperator come after all other elements
//firstNotGreater = index of 1st element in rearranged arr that <= separator, n if so such element
//firstLess = index of 1st element that < separator, n if no such element
/* In other words, upon return from the function, the array is a
permutation of its original value such that
  * for 0 <= i < firstNotGreater, a[i] > separator
  * for firstNotGreater <= i < firstLess, a[i] == separator
  * for firstLess <= i < n, a[i] < separator
 All the elements > separator end up in no particular order.
 All the elements < separator end up in no particular order. 
void separate(double a[], int n, double separator,
	int& firstNotGreater, int& firstLess) {
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > separator
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < separator

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < separator)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > separator)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

//Rearrange elements of array so that a[0] >= a[1] >= a[2] ... 
//Array elements from greatest to least, if n <= 1 do nothing
//Using separate, order can be written in 8/less lines of code
void order(double a[], int n) {
	if (n <= 1) //If n <= 1, do nothing
		return;

	int firstNotGreater = -1; //Index of 1st element greater than/= to separator
	int firstNotLess = -1; //Index of 1st element less than/= to separator
	separate(a, n, a[(n+1)/2], firstNotGreater, firstNotLess); //Calls separator, use middle of array as separator
	
	order(a, firstNotGreater); //First half, sorted part
	order(a + firstNotLess, n-firstNotLess); //Second half, unsorted part
}


//Return # of ways that n2 elements of a2 appear in n1 elements of a1 in same order
//Empty seq appears in sequence n1 in 1 way, even if n1 = 0
//Ex: a1 7# array = 10 50 40 20 50 40 30
//Ex: returns 0 for 20 10 40	1 for 10 20 40		2 for 10 40 30		 3 for 50 40 30 = a2
int countContains(const double a1[], int n1, const double a2[], int n2) {
	if (n2 > n1) //If n2 > n1, not possible for a1 to have all n2 elements
		return 0;
	if (n1 >= 0 && n2 == 0) //If both = 0, return 1 bc found all elements or n2 was orig 0
		return 1;
	if (n1 < 0 || n2 < 0) //If n1 or n2 < 0, no more elements to check or wrong bc negative size
		return 0;

	int count = -1;

	if (a1[0] == a2[0]) //If found matching element, check rest of a2 in a1 and go into next check of a2 in smaller version of a1
		count = countContains(a1 + 1, n1 - 1, a2 + 1, n2 - 1) + countContains(a1 + 1, n1 - 1, a2, n2);
	else //If didn't find matching, cont looking w/ smaller version of a2
		count = countContains(a1 + 1, n1 - 1, a2, n2);

	return count;
} */


/*int main() {
	double cont[7] = { 10, 50, 40, 20, 50, 40, 30 };
	double c0[3] = { 20, 10, 40 };
	double c1[3] = { 10, 20, 40 };
	double c2[3] = { 10, 40, 30 };
	double c3[3] = { 50, 40, 30 };

	double arr1[8] = { 1, 2, 3, 1, 3, 3, 1, 4 };
	double arr2[4] = { 1, 3, 3, 3 };

	assert(countContains(arr1, 4, arr2, 2) == 1);
	assert(countContains(arr1, 8, arr2, 3) == 4 && countContains(arr1, 8, arr2, 4) == 1);
	assert(countContains(arr1, 7, arr2+1, 2) == 3);
	assert(countContains(arr1, 8, arr2+1, 3) == 1 && countContains(arr1+3, 4, arr2 + 1, 3) == 0);
	assert(countContains(cont, 7, c0, 3) == 0);
	assert(countContains(cont, 7, c1, 3) == 1);
	assert(countContains(cont, 7, c2, 3) == 2);
	assert(countContains(cont, 7, c3, 3) == 3);
	assert(countContains(arr1, 0, arr2, 0) == 1);
	assert(countContains(arr1, -5, arr2, 0) == 0);
	assert(countContains(c1, 1, arr2, 0) == 1);
	assert(countContains(c1, -3, c1, -2) == 0);
	cout << "Passed countContains tests" << endl;

	//Test order
	double test1[5] = { 1.5, 5, 3, 4, 2 };
	order(test1, 4);
	printArr(test1, 4); //sb 5, 4, 3, 1.5
	order(test1, 5);
	printArr(test1, 5); //sb 5, 4, 3, 2, 1.5

	double test2[6] = { 1, 2, 1, 2, 1, 2 };
	order(test2, 0);
	order(test2, -1);
	printArr(test2, 6); //sb 1, 2, 1, 2, 1, 2
	order(test2, 6);
	printArr(test2, 6); //sb 2, 2, 2, 1, 1, 1

	double test3[3] = { 30, -10, 30.0 };
	order(test3, 1);
	printArr(test3, 3); //sb 30, -10, 30.0
	order(test3, 2);
	printArr(test3, 2); //sb 30, -10
	printArr(test3, 3); //sb 30, 30, -10

	double test4[5] = { -1, -2, -52.5, 100, 200 };
	order(test4, 3);
	printArr(test4, 3); //sb -1, -2, -52.5
	order(test4 + 3, 2);
	printArr(test4 + 3, 2); //sb 200, 100

	double test5[4] = { 3, 2, 1, 55.5 };
	order(test5, 3);
	order(test5, 4);
	printArr(test5, 4); //sb 55.5, 3, 2, 1

	double test6[4] = { 3, 4, 4, 1 };
	order(test6, 4);
	printArr(test6, 4); //sb 4, 4, 3, 1
	cout << "Passed order tests?" << endl;
} */