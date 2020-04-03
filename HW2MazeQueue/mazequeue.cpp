
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Coord {
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

/*//Testing purposes, prints contents of maze
void printMaze(string maze[], int nRows, int nCols) {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			cerr << maze[i][j];
		}
		cerr << endl;
	}
} */

//Returns true if found path from (sr, sc) to (er, ec)
//Return false if no path found
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
	queue<Coord> coordQ; //Creates queue of Coord obj

	coordQ.push(Coord(sr, sc)); //Pushes starting coord in maze onto queue
	maze[sr][sc] = '#'; //Mark as found

	while (!coordQ.empty()) {
		Coord current = coordQ.front(); //Get current location
		coordQ.pop(); //Pop top (first-in, first-out) coord off queue

		int cr = current.r();
		int cc = current.c();

		//cerr << "cr = " << cr << " cc = " << cc << endl;
		//cerr << "size = " << coordQ.size() << endl;
		//printMaze(maze, nRows, nCols);

		if (cr == er && cc == ec) //If current = end, path has been found
			return true;

		//Look for open spot (not a wall, not discovered)
		//If find open spot, add new Coord to queue and mark spot in maze as discovered
		if (maze[cr][cc + 1] == '.') { //East
			coordQ.push(Coord(cr, cc + 1));
			maze[cr][cc + 1] = '#';
		}
		if (maze[cr + 1][cc] == '.') { //South
			coordQ.push(Coord(cr + 1, cc));
			maze[cr + 1][cc] = '#';
		}
		if (maze[cr][cc - 1] == '.') { //West
			coordQ.push(Coord(cr, cc - 1));
			maze[cr][cc - 1] = '#';
		}
		if (maze[cr - 1][cc] == '.') { //North
			coordQ.push(Coord(cr - 1, cc));
			maze[cr - 1][cc] = '#';
		}
	}

	//If no solution and queue is empty, return false
	return false;
}

int main() {
	string maze[10] = {
		"XXXXXXXXXX",
		"X...X..X.X",
		"X.XXX....X",
		"X.X.XXXX.X",
		"XXX......X",
		"X...X.XX.X",
		"X.X.X..X.X",
		"X.XXXX.X.X",
		"X..X...X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 4, 3, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}