
#include <iostream>
#include "History.h"
using namespace std;

//Init History obj that corresponds to Arena w/ nRows, nCols (assume valid # of rows and col)
History::History(int nRows, int nCols) {
	m_rows = nRows;
	m_cols = nCols;
}

//Called to notify History obj that a vamp has started its turn poisoned but alive at a grid point (r, c)
//Returns false if r, c is out of bounds, otherwise returns true after recording info
//Same coord system as Arena (1, 1, is upper left corner)
bool History::record(int r, int c) {
	//If out of bounds, return false
	if (r < 1 || c < 1 || r > m_rows || c > m_cols) 
		return false;

	arena[r][c] += 1;
	return true;
}

//Clears screen and displays history grid, writes empty line after grid
//Doesn't print "Press enter to continue"
//dot means 0 vampires poisoned, A-Y mean 1-25, Z means 26 or more
void History::display() const {
	clearScreen();

	for (int i = 1; i <= m_rows; i++) {
		for (int j = 1; j<= m_cols; j++) {
			if (arena[i][j] == 0)
				cout << ".";
			else if (arena[i][j] < 26) {
				//ASCII: A = 65
				cout << char(arena[i][j] + 64);
			}
			else
				cout << 'Z';
		}
		cout << endl;
	}

	cout << endl; //Empty line after grid
}
