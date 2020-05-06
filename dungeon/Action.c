#include <stdio.h>
#include "Action.h"

/*
	Alex Hromada
	anhromad
	M45218886
	Program 8: Dungeon
	CS1142
	Spring 2020
	
	This program implements methods declared in Action.h
*/

/*
	Maps a key command to an action
*/
Action actionFromChar(char ch)
{
	switch(ch)
	{
		case 'w':
			return ActionNorth;
		case 'a':
			return ActionWest;
		case 's':
			return ActionSouth;
		case 'd':
			return ActionEast;
		case 'q':
			return ActionQuit;
		default:
			return ActionInvalid;
	}
	
}