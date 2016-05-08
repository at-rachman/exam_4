/*
 * Group Members: Atmanjaya Rachman, Ben Wheaton, Yunjun Ma
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#include "interactionFunctions.cpp"
#include "mapFunctions.cpp"
#include "playerFunctions.cpp"
#include "screenFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * FUNCTION PROTOTYPES
 */
// none here yet

int main()
{
	doLoadGame('0');

	while (true)
	{
		clearScreen();
		printScreen();

		char input = readCharacterInput();
		doCommand(input);
	}

	return 0;
}
