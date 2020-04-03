
/*#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include <cctype>

#include "Game.h"
using namespace std;

// Manifest constants

// Type definitions

//  Auxiliary function declarations

//  Vampire implementation

//  Player implementation

//  Arena implementation

//  Game implementation

//  Auxiliary function implementation

// main()

int main()
{
	// Create a game
	// Use this instead to create a mini-game:   Game g(3, 5, 2);
	Game g(10, 12, 40);

	// Play the game
	g.play();
} */

/* //Test 1
	#include "Game.h"
	#include "Game.h"
	#include "Arena.h"
	#include "Arena.h"
	#include "History.h"
	#include "History.h"
	#include "Player.h"
	#include "Player.h"
	#include "Vampire.h"
	#include "Vampire.h"
	#include "globals.h"
	#include "globals.h"
	int main()
	{} */

/* //Test 2
	#include "History.h"
	int main()
	{
	    History h(2, 2);
	    h.record(1, 1);
	    h.display();
	}
*/

/* //Test 3
#include "Vampire.h"
	int main()
	{
		Vampire v(nullptr, 1, 1);
	}
*/ 

/* //Test 4
#include "Player.h"
	int main()
	{
		Player p(nullptr, 1, 1);
	}
*/

/* //Test 5
#include "Arena.h"
	int main()
	{
		Arena a(10, 18);
		a.addPlayer(2, 2);
	}

*/

/* //Test 6
#include "globals.h"
	#include "Player.h"
	#include "Arena.h"
	int main()
	{
		Arena a(10, 20);
		Player p(&a, 2, 3);
	}
*/

/* //Test 7
#include "Arena.h"
	#include "Player.h"
	int main()
	{
		Arena a(10, 20);
		Player p(&a, 2, 3);
	}
*/

/* //Test 8
#include "Player.h"
	#include "Arena.h"
	int main()
	{
		Arena a(10, 20);
		Player p(&a, 2, 3);
	}
*/

/* //Test 9
  #include "Arena.h"
		#include "History.h"
		#include "globals.h"
		#include <iostream>
		using namespace std;

		int main()
		{
			Arena a(1, 4);
			a.addPlayer(1, 4);
		a.addVampire(1, 1);
		a.setCellStatus(1, 2, HAS_POISON);
			while (a.getCellStatus(1, 2) == HAS_POISON)
				a.moveVampires();
		a.moveVampires();
			a.history().display();
			cout << "====" << endl;
	}
*/

/* //Test 10
#include "Vampire.h"
	#include "Arena.h"
	int main()
	{
		Arena a(10, 20);
		Player p(&a, 2, 3);
		Vampire v(&a, 1, 1);
	}
 */

/* //Test 11
	#include "Player.h"
	#include "Arena.h"
	int main()
	{
		Arena a(10, 20);
		Player p(&a, 2, 3);
		Vampire v(&a, 1, 1);
	}
*/

/* //Test 12
#include "globals.h"
		#include "Vampire.h"
		#include "Player.h"
		int main()
		{
			Arena a(10, 10);
		}
*/

/* //Test 13
#include "History.h"
	int main()
	{
		History h;
	}

*/

#include "Arena.h"
#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

int main()
{
	Arena a(1, 4);
	a.addPlayer(1, 4);
	a.addVampire(1, 1);
	a.setCellStatus(1, 2, HAS_POISON);
	while (a.getCellStatus(1, 2) == HAS_POISON)
		a.moveVampires();
	a.moveVampires();
	a.history().display();
	cout << "====" << endl;
} 