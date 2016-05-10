/*
 * Group Members: Atmanjaya Rachman, Ben Wheaton, Yunjun Ma
 */
// This is a test
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
  //doLoadGame(); /* Atmanjaya updated 5/8 */
  doLoadDefaultGame();

  while (true)
  {
    clearScreen();
    printScreen();

    char input = readCharacterInput();
    doCommand(input);
  }

  return 0;
}
