
/*#include <iostream>
#include <string>
#include <cassert>
using namespace std;

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
} */

/*int main() {
	string maze1[10] = {
	  "XXXXXXXXXX",
	  "X.X..X...X",
	  "X.XX.X.XXX",
	  "X....X.X.X",
	  "XX.X.X...X",
	  "XXX..X.X.X",
	  "X...X...XX",
	  "X.XX..X.XX",
	  "X....X...X",
	  "XXXXXXXXXX",
	};

	string maze2[10] = {
	  "XXXXXXXXXX",
	  "X.X..X...X",
	  "XXXX.X.XXX",
	  "X....X.X.X",
	  "XX.X.X...X",
	  "XXX..X.X.X",
	  "X...X...XX",
	  "X.XX..X.XX",
	  "X....X...X",
	  "XXXXXXXXXX",
	};

	string maze3[10] = {
	  "XXXXXXXXXX",
	  "XX.....XXX",
	  "X..XX....X",
	  "X...X...XX",
	  "X.X.XXX..X",
	  "XXXX..X..X",
	  "XX....X..X",
	  "X.......XX",
	  "X..XXXXXXX",
	  "XXXXXXXXXX",
	};

	string maze4[10] = {
	  "XXXXXXXXXX",
	  "XX.....XXX",
	  "X..XX....X",
	  "X...X...XX",
	  "X.X.XXX..X",
	  "XXXX..X..X",
	  "XX....X..X",
	  "X.X.....XX",
	  "X..XXXXXXX",
	  "XXXXXXXXXX",
	};

	assert(pathExists(maze1, 10, 10, 8, 6, 1, 1));
	assert(!pathExists(maze2, 10, 10, 8, 6, 1, 1));
	assert(pathExists(maze3, 10, 10, 4, 3, 7, 1));
	assert(!pathExists(maze4, 10, 10, 4, 3, 7, 1));
	cout << "Passed maze tests" << endl;
} */