
/*#include <iostream>
#include <cassert>
using namespace std; //COMMENT OUT STUFF LATER!!

//Returns true if x is negative
bool somePredicate(double x) {
	return x < 0;
} 


//Return true if somePredicate f(x) returns false for at least one of the array elements
//Return false otherwise
bool anyFalse(const double a[], int n) {
	n--; //Decrement n first bc n = size, 1 over last access pos for array

	if (n < 0) //Went through all spots in array and didn't find one that return false
		return false;
	if (!somePredicate(a[n])) //If somePred returns false for an element, return true
		return true;

	return anyFalse(a, n);
}

//Return # of elements in array for which somePredicate returns true
int countTrue(const double a[], int n) {
	n--;

	if (n < 0)
		return 0;

	if (somePredicate(a[n])) //If true, adds 1 + calls w/ smaller array
		return 1 + countTrue(a, n);
	else //If false, doesn't add 1 and just calls w/ smaller aray
		return countTrue(a, n);
}

//Return subscript of first element in array for which somePredicate fx returns true
//If no such element, return -1
int firstTrue(const double a[], int n) {
	n--; //Decrement size

	if (n < 0) //Size < 0 and no true found, return -1
		return -1;
	if (somePredicate(a[0])) //If first element = 0, return 0
		return 0;
	
	//Call w/ smaller version of array w/ first item cut off, n is decremented at start
	//Add one every time 
	int index = firstTrue(a + 1, n); 
	if (index == -1) //If index = -1, that means firstTrue returned -1 + didn't find
		return -1;
	else //If index != -1, firstTrue found an index ==> add 1
		return 1 + index;
}


//Return subscript of smallest element in array (subscript m such that a[m] <] a[k] for k from 0 to n-1
//If function is told to examine 0 elements, return -1
int positionOfSmallest(const double a[], int n) {
	if (n < 0 || n == 0) //Examime O elements so return -1
		return -1;
	if (n == 1) //Can't be split anymore if size = 1
		return 0;

	int pos1 = positionOfSmallest(a, n / 2); //Finds index of smallest in first half of array
	int pos2 = positionOfSmallest(a + n / 2, n - n / 2); //Finds index of smallest in second half of array

	//if (pos1 == -1 && pos2 == -1) return -1; //already checks for 0 at start

	//Add indexes to pos2 to account for being split in half, +1 if n was even
	pos2 += n / 2;
	if (a[pos1] < a[pos2])
		return pos1;
	else
		return pos2;
}

//Return true if all n2 elements of arr a2 appear in n1 elements of arr a1 in same order
//Return false otherwise
//Ex: if 7 elements a1 = 10 50 40 20 50 40 30, a2 = 50 20 30 || 50 40 40 return true
//Ex: if a2 = 50 30 20 (wrong order) || 10 20 20 (extra 20) return false
bool contains(const double a1[], int n1, const double a2[], int n2) {
	if (n2 > n1) //If n2 > n1, not possible for a1 to have all n2 elements
		return false;
	if (n1 >= 0 && n2 == 0) //If both = 0, return true bc found all elements
		return true;
	if (n1 < 0 || n2 < 0) //If n2 isn't 0 but n1 is, then return false bc didn't find; if n1 or n2 is entered as neg, wrong
		return false;

	/* bool increment = false;
	int i2 = 0;
	if (a1[0] == a2[0]) {  //If first element in a1 = first element in a2, return true + check other elements
		increment = true;
		i2 = 1; //If increment, change inc to 1 otherwise = 0
		return true;
	}
	//If element was found, increment a1 and a2 to look for next element otherwise keep looking for first element
	return contains(a1 + 1, n1 - 1, a2 + i2, n2 - i2); 

	if (a1[0] == a2[0]) //If first element in a1 = first element in a2, return true + check other elements
		return true && contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else //Otherwise keep looking for first element in n2
		return contains(a1 + 1, n1 - 1, a2, n2);
} */

/*int main() {
	double a1[7] = { 10, 50, 40, 20, 50, 40, 30 };
	double correct[6] = { 50, 20, 30, 50, 40, 40 };
	double wrong[6] = { 50, 30, 20, 10, 20, 20 };

	//Contains returns true if n2 elements of a2 appear in n1 elements of a1 in order
	assert(contains(a1, 2, correct, 1) == true);
	assert(contains(a1, 7, correct + 3, 3) == true);
	assert(contains(a1, 7, wrong, 3) == false);
	assert(contains(a1, 7, wrong + 3, 3) == false);
	assert(contains(a1, 3, a1, 2) == true);
	assert(contains(correct, 4, correct, 4) == true);
	assert(contains(correct, 6, correct, 6) == true && contains(correct, 2, correct, 1) == true);
	assert(contains(wrong, 1, wrong, 2) == false);
	assert(contains(wrong, 5, wrong, -3) == false && contains(wrong, -1, wrong, -3) == false);
	assert(contains(wrong, 0, wrong, 0) == true);
	assert(contains(wrong, -1, wrong, -1) == false && contains(wrong, -3, wrong, 0) == false);
	assert(contains(a1, 6, a1, 7) == false);
	assert(contains(correct, 4, wrong, 2) == true);
	cout << "Passed contains tests" << endl;

	double test1[5] = { -100, -10, 3.5, 0, 2 };
	double test2[5] = { -2, 2, -2, 0, -2};
	double test3[5] = { 1, 2, -2, -10.2, 0 };

	//positionOfSmallest returns index of smallest element
	assert(positionOfSmallest(test1, -1) == -1 && positionOfSmallest(test2, 0) == -1);
	assert(positionOfSmallest(test1, 3) == 0);
	assert(positionOfSmallest(test1 + 1, 3) == 0);
	assert(positionOfSmallest(test3, 3) == 2);
	assert(positionOfSmallest(test3, 5) == 3);
	assert(positionOfSmallest(test2, 5) == 4 && positionOfSmallest(test2, 3) == 2);
	assert(positionOfSmallest(test1, 1) == 0);
	cout << "Passed positionOfSmallest tests " << endl;

	//firstTrue returns index of first element that < 0 (neg)
	assert(firstTrue(test1, 5) == 0);
	assert(firstTrue(test1 + 3, 2) == -1);
	assert(firstTrue(test1, 0) == -1);
	assert(firstTrue(test1, -1) == -1);
	assert(firstTrue(test2, 4) == 0);
	assert(firstTrue(test3, 3) == 2 && firstTrue(test3, 4) == 2);
	assert(firstTrue(test2 + 1, 3) == 1);
	cout << "Passed firstTrue tests" << endl;

	//countTrue returns # of elements that < 0 (neg)
	assert(countTrue(test3, 5) == 2);
	assert(countTrue(test3, -1) == 0);
	assert(countTrue(test3, 0) == 0);
	assert(countTrue(test3, 1) == 0 && countTrue(test3, 2) == 0);
	assert(countTrue(test3, 4) == 2);
	assert(countTrue(test2, 5) == 3 && countTrue(test2, 2) == 1 && countTrue(test2, 3) == 2);
	cout << "Passed countTrue test" << endl;

	//AnyFalse returns true if element > 0, false is all elements < 0
	assert(anyFalse(test1, -1) == false && anyFalse(test1, 0) == false);
	assert(anyFalse(test1, 1) == false && anyFalse(test1, 2) == false);
	assert(anyFalse(test1, 3) == true);
	test1[2] = -3.5;
	assert(anyFalse(test1, 2) == false);
	assert(anyFalse(test1, 3) == false);
	assert(anyFalse(test1, 4) == true);
	assert(anyFalse(test1, 5) == true);
	test1[4] = -2;
	test1[0] = 100;
	assert(anyFalse(test1, 5) == true);
	assert(anyFalse(test2, 1) == false);
	assert(anyFalse(test2, 3) == true);
	cout << "Passed anyFalse tests" << endl;

} */