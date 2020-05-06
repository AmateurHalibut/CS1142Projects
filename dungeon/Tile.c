#include <stdio.h>
#include "Tile.h"

/*
	Alex Hromada
	anhromad
	M45218886
	Program 8: Dungeon
	CS1142
	Spring 2020
	
	This program implements methods declared in Tile.h
*/


/*
	Maps tile type to characters
*/
Tile tileFromChar(char ch)
{
	switch(ch)
	{
		case '.':
			return TileEmpty;
		case '#':
			return TileWall;
		case 'S':
			return TileSecretPassage;
		case '*':
			return TileGem;
		case '+':
			return TileKey;
		case '-':
			return TileDoor;
		case '=':
			return TileLockedDoor;
		default:
			return TileInvalid;
		
	}
	
}

/*
	Prints character mapped to tile
*/
void tileDisplay(Tile tile)
{
	switch(tile)
	{
		case TileEmpty:
			printf(" ");
			break;
		case TileWall:
			printf("#");
			break;
		case TileSecretPassage:
			printf("#");
			break;
		case TileGem:
			printf("*");
			break;
		case TileKey:
			printf("+");
			break;
		case TileDoor:
			printf("-");
			break;
		case TileLockedDoor:
			printf("=");
			break;	
		case TileInvalid:
			break;	
	}
}

/*
	Maps a true false value to tile based on whether they should be passable or not
*/
bool tilePassable(Tile tile)
{
	switch(tile)
	{
		case TileEmpty:
			return true;
		case TileWall:
			return false;
		case TileSecretPassage:
			return true;
		case TileGem:
			return true;
		case TileKey:
			return true;
		case TileDoor:
			return true;
		case TileLockedDoor:
			return false;
		case TileInvalid:
			return false;
		default:
			return false;
	}
}