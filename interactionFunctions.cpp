/*
 * Group Members: Atmanjaya Rachman, Ben Wheaton, Yunjun Ma
 */

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_INTERACTION_FUNCTIONS_CPP__
#define __DEFINE_INTERACTION_FUNCTIONS_CPP__

#include <cctype>
#include <string>
#include <iostream>
using namespace std;

#include "playerFunctions.cpp"
#include "mapFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * KEYBOARD CONSTANTS
 */
const char KEYBOARD_UP    = 'w';
const char KEYBOARD_DOWN  = 's';
const char KEYBOARD_LEFT  = 'a';
const char KEYBOARD_RIGHT = 'd';
const char KEYBOARD_LOOK  = 'l';
const char KEYBOARD_TAKE  = 't';
const char KEYBOARD_USE   = 'u';
const char KEYBOARD_QUIT  = 'Q';
const char KEYBOARD_LOAD_GAME = 'L';
const char KEYBOARD_SAVE_GAME = 'S';

/*
 * FUNCTION PROTOTYPES
 */
char readCharacterInput();
void doCommand(const char);
void doLook(const int, const int, const char);
void doTake(const int, const int, const char);
void doUse(const int, const int, const char);
void doLoadGame();
void doLoadGame(const char);
void doLoadDefaultGame();
void doUpdateAfterLoadGame();
void doSaveGame();

string lastMessage = "";

char readCharacterInput()
{
  char input;
  bool inputIsValid = false;

  do
  {
    cin >> input;
    cin.ignore(1024, '\n');

    switch(input)
    {
      case KEYBOARD_UP:
      case KEYBOARD_DOWN:
      case KEYBOARD_LEFT:
      case KEYBOARD_RIGHT:
      case KEYBOARD_LOOK:
      case KEYBOARD_TAKE:
      case KEYBOARD_USE:
      case KEYBOARD_QUIT:
      case KEYBOARD_LOAD_GAME:
      case KEYBOARD_SAVE_GAME:
        inputIsValid = true;
        break;
    }
    if (inputIsValid)
    {
      break;
    }

    cout << "Bad input. Try again." << endl;
  } while (!inputIsValid);

  return input;
}

void doCommand(const char command)
{
  switch(command)
  {
    case KEYBOARD_UP:
      playerSymbol = LOOKING_UP;
      if (isOpenSpace(playerX, playerY - 1))
      {
        playerY -= 1;
      }
      break;
    case KEYBOARD_DOWN:
      playerSymbol = LOOKING_DOWN;
      if (isOpenSpace(playerX, playerY + 1))
      {
        playerY += 1;
      }
      break;
    case KEYBOARD_LEFT:
      playerSymbol = LOOKING_LEFT;
      if (isOpenSpace(playerX - 1, playerY))
      {
        playerX -= 1;
      }				 /* -- Atmanjaya Updated 5/7 -- */
      break;
    case KEYBOARD_RIGHT:
      playerSymbol = LOOKING_RIGHT;
      if (isOpenSpace(playerX + 1, playerY))
      {
        playerX += 1;
      }				/* -- Atmanjaya Updated 5/7 -- */
      break;
    case KEYBOARD_LOOK:
      doLook(playerX, playerY, playerSymbol);
      break;
    case KEYBOARD_TAKE:
      doTake(playerX, playerY, playerSymbol); /* -- Atmanjaya Updated 5/7 -- */
      break;
    case KEYBOARD_USE:
      doUse(playerX, playerY, playerSymbol); /* -- Atmnajaya Updated 5/7 -- */
      break;
    case KEYBOARD_LOAD_GAME:
      doLoadGame(); /* -- Atmanjaya Updated 5/8 -- */
      break;
    case KEYBOARD_SAVE_GAME:
      doSaveGame();/* -- Atmanjaya Updated 5/8 -- */
        break;
  }
}

void doLook(const int x, const int y, const char lookingDirection)
{
  char mapSquare = getMapSquare(getLookingAtX(x, lookingDirection), getLookingAtY(y, lookingDirection));
  switch(mapSquare)
  {
    case MAP_SQUARE_CHASM:
      lastMessage = "The chasm in front of you is too wide to jump across. Perhaps there's another way across?";
      break;
    case MAP_SQUARE_EMPTY:
      lastMessage = "You see nothing of interest.";
      break;
    case MAP_SQUARE_KEY:
      lastMessage = "There is a shiny key on the ground. But what is it for?";
      break;
    case MAP_SQUARE_LOCK:
      lastMessage = "The door in front of you is locked.";
      break;
    case MAP_SQUARE_PEBBLE:
      lastMessage = "You see a large pebble on the ground. Stepping on it would hurt.";
      break;
    case MAP_SQUARE_PEBBLES:
      lastMessage = "You see two large pebbles on the ground. Stepping on them would hurt.";
      break;
    case MAP_SQUARE_PLANK:
      lastMessage = "There is a long plank of wood on the ground. You wonder how it got there.";
      break;
    case MAP_SQUARE_PLANK_SET:
      lastMessage = "The two sides of the chasm are bridged by a long plank of wood.";
      break;
    case MAP_SQUARE_ROPE:
      lastMessage = "Someone left a long stretch of rope just lying around. How irresponsible.";
      break;
    case MAP_SQUARE_ROPE_TIED:
      lastMessage = "A rope dangles above the chasm in front of you. You can just barely reach it.";
      break;
    case MAP_SQUARE_ROCK:
      lastMessage = "The rock wall in front of you is dusty with age. Try not to sneeze.";
      break;
    default:
      lastMessage = "You're not sure what it is. You've never seen anything like it before.";
  }
}

void doTake(const int x, const int y, const char lookingDirection)
{
  bool success = false;
  lastMessage = "There is nothing to take.";

  int itemX = getLookingAtX(x, lookingDirection);
  int itemY = getLookingAtY(y, lookingDirection);
  char mapSquare = getMapSquare(itemX, itemY);
  switch(mapSquare)
  {
    case MAP_SQUARE_KEY:
      lastMessage = "You pick up the key.";
      success = true;
      break;
    case MAP_SQUARE_PEBBLE:
      lastMessage = "You pick up a pebble.";
      success = true;
      break;
    case MAP_SQUARE_PEBBLES:
      lastMessage = "You pick up a couple pebbles.";
      success = true;
      break;
    case MAP_SQUARE_PLANK:
      lastMessage = "You pick up a plank of wood.";
      success = true;
      break;
    case MAP_SQUARE_ROPE:
      lastMessage = "You pick up a long rope.";
      success = true;
      break;
    case MAP_SQUARE_SLINGSHOT:
      lastMessage = "You pick up a slingshot.";
      success = true;
      break;
  }
  if (success)
  {
    inventoryAdd(mapSquare);
    clearMapSquare(itemX, itemY, mapSquare);
  }
}

void doUse(const int x, const int y, const char lookingDirection)
{
  char itemToUse;
  cout << endl << "What would you like to use? ";
  cin >> itemToUse;
  cin.ignore(1024, '\n');
  if (!inventoryHas(itemToUse)) // Atmanjaya Updated 5/8
  {
    lastMessage = "You don't have any.";
    return;
  }

  int itemX = getLookingAtX(x, lookingDirection);
  int itemY = getLookingAtY(y, lookingDirection);
  char mapSquare = getMapSquare(itemX, itemY); // Atmanjaya Updated 5/8

  if (mapSquare == MAP_SQUARE_CHASM && itemToUse == MAP_SQUARE_PLANK)
  {
    inventoryUse(itemToUse);
    setMapSquare(itemX, itemY, mapSquare, MAP_SQUARE_PLANK_SET);
    lastMessage = "You lay the plank of wood over the chasm. It just barely touches both sides.";
  }
  else if (mapSquare == MAP_SQUARE_CHASM && itemToUse == MAP_SQUARE_ROPE)
  {
    inventoryUse(itemToUse);
    setMapSquare(itemX, itemY, mapSquare, MAP_SQUARE_ROPE_TIED);
    lastMessage = "Standing on the tips of your toes, you reach up and tie the rope to a beam above you.";
  }
  else if (mapSquare == MAP_SQUARE_CHASM && itemToUse == MAP_SQUARE_PEBBLE)
  {
    inventoryUse(itemToUse);
    setMapSquare(itemX, itemY, mapSquare, MAP_SQUARE_CHASM);
    lastMessage = "You drop a pebble into the chasm, counting the seconds until it hits the bottom. You hear nothing.";
  }
  else if (mapSquare == MAP_SQUARE_PLANK && itemToUse == MAP_SQUARE_PEBBLE && inventoryHas(MAP_SQUARE_SLINGSHOT))
  {
    inventoryUse(itemToUse);
    setMapSquare(itemX, itemY, mapSquare, MAP_SQUARE_PEBBLE);
    lastMessage = "You shoot the plank of wood with your slingshot. No more plank.";
  }
  else if (mapSquare == MAP_SQUARE_LOCK && itemToUse == MAP_SQUARE_KEY)
  {
    inventoryUse(itemToUse);
    setMapSquare(itemX, itemY, mapSquare, MAP_SQUARE_EMPTY);
    lastMessage = "You turn the key. Hard. Just as the lock opens you feel the key snap in half.";
  }
  else
  {
    lastMessage = "You can't use that here.";
  }
}

void doLoadGame()
{
  cout << endl << "Enter 0-9 to load a saved game. Enter any other visible character to cancel. Input: ";
  char slot;
  cin >> slot;
  doLoadGame(slot);
}

void doLoadGame(const char slot)
{
  if (!isdigit(slot)/* -- MISSING CODE -- REPLACE true AT RIGHT -- true */)
  {
    lastMessage = "Must enter 0-9 to load a saved game.";
    return;
  }

  string fileName = "gameSlotN.txt";
  fileName[8] = slot; // #14 Updated 5/13 
  if (!loadGame(fileName))
  {
    lastMessage = "Could not load 'fileName'. File is corrupt or does not exist.";
    lastMessage.replace(16, 8, fileName);
    return;
  }

  doUpdateAfterLoadGame();

  lastMessage = "Loaded game ";
  lastMessage += slot;
  lastMessage += ".";
}

void doLoadDefaultGame()
{
  loadDefaultMap();
  doUpdateAfterLoadGame(); /* -- Atmanjaya Updated 5/10 -- */

  lastMessage = "Loaded default game.";
}

void doUpdateAfterLoadGame()
{
  playerX = FILE_START_LOCATION_AS_INDEX % MAP_WIDTH;
  playerY = FILE_START_LOCATION_AS_INDEX / MAP_WIDTH;
  playerSymbol = ((FILE_START_LOOKING_DIRECTION == LOOKING_UP ||
        FILE_START_LOOKING_DIRECTION == LOOKING_DOWN ||
        FILE_START_LOOKING_DIRECTION == LOOKING_LEFT ||
        FILE_START_LOOKING_DIRECTION == LOOKING_RIGHT) ? FILE_START_LOOKING_DIRECTION : LOOKING_UP);

  inventorySet(FILE_INVENTORY_ITEMS, FILE_INVENTORY_VALUES, FILE_INVENTORY_LENGTH);
}

void doSaveGame()
{
  cout << endl << "Enter 0-9 to save the game in that slot. Enter any other visible character to cancel. Input: ";
  char slot;
  cin >> slot;
  if (!isdigit(slot)/* -- MISSING CODE -- REPLACE true AT RIGHT -- true */ )
  {
    lastMessage = "Must enter 0-9 to load a saved game.";
    return;
  }

  string fileName = "gameSlot";
  fileName += slot;
  fileName += ".txt";

  int numberOfItems = 0;
  char inventoryItems[INVENTORY_LENGTH];
  int inventoryValues[INVENTORY_LENGTH];
  for (int i = 0; i < INVENTORY_LENGTH; i++)
  {
    int itemCount = INVENTORY_ARRAY[i];
    if (itemCount > 0)
    {
      inventoryItems[numberOfItems] = convertInventoryIndexToItemChar(i);
      inventoryValues[numberOfItems] = itemCount;
      numberOfItems++;
    }
  }

  if (!saveGame(fileName, playerX, playerY, playerSymbol, inventoryItems, inventoryValues, numberOfItems))
  {
    lastMessage = "Could not save '";
    lastMessage += fileName;
    lastMessage += "'. Data is corrupt or writing files is not allowed.";
    return;
  }

  lastMessage = "Saved game to slot ";
  lastMessage += slot;
  lastMessage += ".";
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE
