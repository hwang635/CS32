#include <iostream>
#include <streambuf>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <cassert>

using namespace std;

bool somePredicate(double x)
{
	return x < -9;
}

//MAZE
//Return true if path from (sr, sc) to (er, ec) exists, false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	//If start loc = end loc, found path so return true
	if (sr == er && sc == ec)
		return true;

	maze[sr][sc] = '#'; //Mark location as visited

	//For each loc, if loc one step from that loc is open call pathExists from there and return true if true
	if (maze[sr][sc + 1] == '.') { //East
		if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
			return true;
	}
	if (maze[sr + 1][sc] == '.') { //South
		if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
			return true;
	}
	if (maze[sr][sc - 1] == '.') { //West
		if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
			return true;
	}
	if (maze[sr - 1][sc] == '.') { //North
		if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
			return true;
	}

	return false;
}

//LINEAR
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
	return contains(a1 + 1, n1 - 1, a2 + i2, n2 - i2); */

	if (a1[0] == a2[0]) //If first element in a1 = first element in a2, return true + check other elements
		return true && contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else //Otherwise keep looking for first element in n2
		return contains(a1 + 1, n1 - 1, a2, n2);
}

//TREE
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
 All the elements < separator end up in no particular order. */
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
	separate(a, n, a[(n + 1) / 2], firstNotGreater, firstNotLess); //Calls separator, use middle of array as separator

	order(a, firstNotGreater); //First half, sorted part
	order(a + firstNotLess, n - firstNotLess); //Second half, unsorted part
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
}

void testone(int n)
{
	static string maze1[10] = {
	  "XXXXXXXXXX",
	  "X...X....X",
	  "XX.X..XX.X",
	  "XX...X...X",
	  "X.X.X..XXX",
	  "X...X.X.XX",
	  "X.X.X....X",
	  "XXX.X.XX.X",
	  "X...X..X.X",
	  "XXXXXXXXXX",
	};

	static string maze2[10] = {
	  "XXXXXXXXXX",
	  "X...X....X",
	  "XX.X..XX.X",
	  "XX...X...X",
	  "X.X.X..XXX",
	  "X...X.X.XX",
	  "X.X.X....X",
	  "XXX.X.XXXX",
	  "X...X..X.X",
	  "XXXXXXXXXX",
	};

	static string maze3[10] = {
	  "XXXXXXXXXX",
	  "XXXXXXX..X",
	  "XX.......X",
	  "X..X....XX",
	  "X..X..XXXX",
	  "X..XXX.X.X",
	  "XX...X...X",
	  "X....XX..X",
	  "XXX.....XX",
	  "XXXXXXXXXX",
	};

	static string maze4[10] = {
	  "XXXXXXXXXX",
	  "XXXXXXX..X",
	  "XX.....X.X",
	  "X..X....XX",
	  "X..X..XXXX",
	  "X..XXX.X.X",
	  "XX...X...X",
	  "X....XX..X",
	  "XXX.....XX",
	  "XXXXXXXXXX",
	};

	double a[10] = { 5, -5, -10, 6, -10, -6, -10, -10, -7, 7 };
	double an[10] = { -10, -15, 10, -16, 10, -16, 10, 10, -17, -17 };
	double x[10] = { 2, 7, 4, 8, -10, 0, -10, -10, 9, 6 };
	double y[10] = { 8, 10, 0, 9, 4, 5, -10, 2, 12, 6 };
	double b[4] = { 10, 0, 4, 2 };
	double c[8] = { 1, 9, 7, 3, 9, 7, 5 };
	double d[12] = { 1, 3, 7, 1, 7, 5, 3, 1, 7, 9, 7, 5 };
	double f[16] = { 4, 7, 0, 15, 2, 4, 5, 14, 10, 1, 0, 6, 12, 14, 4, 8 };
	double g[16] = { 15, 14, 14, 12, 10, 8, 7, 6, 5, 4, 4, 4, 2, 1, 0, 0 };

	switch (n)
	{
	default: {
		assert(false);
	} break; case  1: {
		assert(anyFalse(an, 10));
	} break; case  2: {
		assert(anyFalse(an, 8));
	} break; case  3: {
		assert(anyFalse(an + 2, 8));
	} break; case  4: {
		assert(!anyFalse(an + 8, 2) && anyFalse(an + 6, 2));
	} break; case  5: {
		assert(!anyFalse(an, 1));
	} break; case  6: {
		assert(anyFalse(an + 2, 1));
	} break; case  7: {
		assert(!anyFalse(an, 0) && !anyFalse(an + 2, 0));
	} break; case  8: {
		assert(countTrue(a, 10) == 4);
	} break; case  9: {
		assert(countTrue(a, 8) == 4);
	} break; case 10: {
		assert(countTrue(a + 2, 8) == 4);
	} break; case 11: {
		assert(countTrue(a + 8, 2) == 0 && countTrue(a + 6, 2) == 2);
	} break; case 12: {
		assert(countTrue(a, 1) == 0);
	} break; case 13: {
		assert(countTrue(a + 2, 1) == 1);
	} break; case 14: {
		assert(countTrue(a, 0) == 0 && countTrue(a + 2, 0) == 0);
	} break; case 15: {
		assert(firstTrue(a, 10) == 2);
	} break; case 16: {
		assert(firstTrue(a, 8) == 2);
	} break; case 17: {
		assert(firstTrue(a + 2, 8) == 0);
	} break; case 18: {
		assert(firstTrue(a + 8, 2) == -1 && firstTrue(a + 6, 2) == 0);
	} break; case 19: {
		assert(firstTrue(a, 1) == -1);
	} break; case 20: {
		assert(firstTrue(a + 2, 1) == 0);
	} break; case 21: {
		assert(firstTrue(a, 0) == -1 && firstTrue(a + 2, 0) == -1);
	} break; case 22: {
		assert(positionOfSmallest(x, 6) == 4);
	} break; case 23: {
		assert(positionOfSmallest(x, 5) == 4);
	} break; case 24: {
		assert(positionOfSmallest(x + 7, 3) == 0);
	} break; case 25: {
		assert(positionOfSmallest(x + 8, 2) == 1);
	} break; case 26: {
		assert(positionOfSmallest(x + 2, 2) == 0);
	} break; case 27: {
		assert(positionOfSmallest(x, 1) == 0);
	} break; case 28: {
		assert(positionOfSmallest(x + 4, 1) == 0);
	} break; case 29: {
		assert(positionOfSmallest(x, 10) == 4);
	} break; case 30: {
		assert(positionOfSmallest(x, 0) == -1 && positionOfSmallest(x + 2, 0) == -1);
	} break; case 31: {
		assert(contains(y, 10, b, 4));
	} break; case 32: {
		assert(contains(y + 1, 9, b, 4));
	} break; case 33: {
		assert(!contains(y + 2, 8, b, 4));
	} break; case 34: {
		assert(!contains(y + 1, 6, b, 4));
	} break; case 35: {
		assert(contains(y + 1, 7, b, 4));
	} break; case 36: {
		assert(contains(y, 10, b + 2, 1));
	} break; case 37: {
		assert(contains(y + 1, 9, b, 1));
	} break; case 38: {
		assert(!contains(y + 2, 8, b, 1));
	} break; case 39: {
		assert(contains(y, 10, b, 0));
	} break; case 40: {
		assert(contains(y, 0, b, 0));
	} break; case 41: {
		assert(contains(y + 1, 2, b, 2));
	} break; case 42: {
		assert(!contains(y + 2, 2, b + 1, 2));
	} break; case 43: {
		assert(!contains(y + 2, 2, b + 1, 3));
	} break; case 44: {
		assert(!contains(y + 1, 1, b, 2));
	} break; case 45: {
		assert(!contains(y + 1, 0, b, 1));
	} break; case 46: {
		assert(contains(c, 7, d + 3, 3));
	} break; case 47: {
		assert(!contains(c, 7, d + 6, 3));
	} break; case 48: {
		assert(contains(c, 7, d + 9, 3));
	} break; case 49: {
		assert(countContains(c, 0, d, 0) == 1);
	} break; case 50: {
		assert(countContains(c, 7, d, 0) == 1);
	} break; case 51: {
		assert(countContains(c, 2, d + 2, 1) == 0);
	} break; case 52: {
		assert(countContains(c, 7, d, 3) == 1);
	} break; case 53: {
		assert(countContains(c, 7, d + 3, 3) == 2);
	} break; case 54: {
		assert(countContains(c, 7, d + 6, 3) == 0);
	} break; case 55: {
		assert(countContains(c, 7, d + 9, 3) == 3);
	} break; case 56: {
		assert(countContains(c, 7, d + 2, 1) == 2);
	} break; case 57: {
		auto i = f[0];
		order(f, 1);
		assert(f[0] == i);
	} break; case 58: {
		auto i = f[0];
		order(f, 0);
		assert(f[0] == i);
	} break; case 59: {
		order(f, 16);
		assert(equal(f, f + 16, g));
	} break; case 60: {
		assert(pathExists(maze1, 10, 10, 1, 3, 8, 8));
	} break; case 61: {
		assert(!pathExists(maze2, 10, 10, 1, 3, 8, 8));
	} break; case 62: {
		assert(pathExists(maze3, 10, 10, 5, 6, 2, 8));
	} break; case 63: {
		assert(!pathExists(maze4, 10, 10, 5, 6, 2, 8));
	}
	}
}

int main()
{
	cout << "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout << "Passed" << endl;
}