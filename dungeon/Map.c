#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Map.h"

/*
	Alex Hromada
	anhromad
	M45218886
	Program 8: Dungeon
	CS1142
	Spring 2020
	
	This program implements methods declared in Map.h
	Reads in the map data from file as well as implements method for movement
*/

/*
	Initializes map for use
*/
bool mapInit(Map* map, const char* filename)
{
	FILE* in = fopen(filename, "r");
	
	if(in == NULL)
		return false;
	
	fscanf(in, "%d %d", &map->rows, &map->cols);		// Read in rows and cols of map
	fscanf(in, "%d %d", &map->avatarRow, &map->avatarCol);	// Read in the avatar start pos
	
	// Allocation of memory for map
	map->tiles = malloc(sizeof(Tile*) * map->rows);
	for(int i = 0; i < map->rows; i++)
	{
		map->tiles[i] = malloc(sizeof(Tile) * map->cols);
		for(int j = 0; j < map->cols; j++)
		{
			map->tiles[i][j] = TileEmpty;
		}
	}
	
	// Read in map data
	int ch = '\0';
	for(int i = 0; i < map->rows; i++)
	{
		int j = 0;
		while((ch = fgetc(in)) != EOF && j < map->cols)
		{
			Tile tile = tileFromChar(ch);
			if(tile != TileInvalid)
			{
				map->tiles[i][j] = tile;
				j++;
			}
		}
	}

	fclose(in);
	in = NULL;
	
	return true;
	
}

/*
	Uninitializes map and deallocates the memory
*/
void mapUninit(Map* map)
{
	for(int i = 0; i < map->rows; i++)
	{
		free(map->tiles[i]);
		map->tiles[i] = NULL;
	}
	
	free(map->tiles);
	map->tiles = NULL;
}

/*
	Prints the map
*/
void mapDisplay(const Map* map)
{
	for(int i = 0; i < map->rows; i++)
	{
		for(int j = 0; j < map->cols; j++)
		{
			if(map->avatarRow == i && map->avatarCol == j)
				printf("@");
			else
				tileDisplay(map->tiles[i][j]);
		}
		printf("\n");
	}
}

/*
	Handles move commands from input
*/
bool mapMoveAvatar(Map* map, Avatar* avatar, Action action)
{
	
	int* currRow = &map->avatarRow;
	int* currCol = &map->avatarCol;
	
	switch(action)
	{
		case ActionNorth:
			if(*currRow - 1 < 0)  // Bounds check to prevent mem leak
				return false;
			// Checks for passable tiles
			if(tilePassable(map->tiles[*currRow - 1][*currCol]))
			{
				*currRow -= 1;
				switch(map->tiles[*currRow][*currCol])
				{
					case TileGem:
						avatarAddGem(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;
					case TileKey:
						avatarAddKey(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;
					default:
						break;
				}
				return true;
			}
			// Tile is a locked door
			else if(map->tiles[*currRow - 1][*currCol] == TileLockedDoor)
			{
				if(avatarUseKey(avatar))
				{
					map->tiles[*currRow - 1][*currCol] = TileDoor;
					*currCol -= 1;
					return true;
				}
			}
			return false;	
			
		case ActionEast:
			if(*currCol + 1 >= map->cols) // Bounds check to prevent mem leak
				return false;
			// Checks for passable tiles
			if(tilePassable(map->tiles[*currRow][*currCol + 1]))
			{
				*currCol += 1;
				switch(map->tiles[*currRow][*currCol])
				{
					case TileGem:
						avatarAddGem(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;
					case TileKey:
						avatarAddKey(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;
					default:
						break;
				}
				return true;			
			}
			// Tile is a locked door
			else if(map->tiles[*currRow][*currCol + 1] == TileLockedDoor)
			{
				if(avatarUseKey(avatar))
				{
					map->tiles[*currRow][*currCol + 1] = TileDoor;
					*currCol += 1;
					return true;
				}
			}
			return false;	

		case ActionSouth:
			if(*currRow + 1 >= map->rows)  // Bounds check to prevent mem leak
				return false;
			// Checks for passable tiles
			if(tilePassable(map->tiles[*currRow + 1][*currCol]))
			{
				*currRow += 1;
				switch(map->tiles[*currRow][*currCol])
				{
					case TileGem:
						avatarAddGem(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;
					case TileKey:
						avatarAddKey(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;

					default:
						break;
				}
				return true;
			}
			// Tile is a locked door
			else if(map->tiles[*currRow + 1][*currCol] == TileLockedDoor)
			{
				if(avatarUseKey(avatar))
				{
					map->tiles[*currRow + 1][*currCol] = TileDoor;
					*currRow += 1;
					return true;
				}
			}
			return false;
		
		case ActionWest:
			if(*currCol - 1 < 0)  // Bounds check to prevent mem leak
				return false;
			// Checks for passable tiles
			if(tilePassable(map->tiles[*currRow][*currCol - 1]))
			{
				*currCol -= 1;
				switch(map->tiles[*currRow][*currCol])
				{
					case TileGem:
						avatarAddGem(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;
					case TileKey:
						avatarAddKey(avatar);
						map->tiles[*currRow][*currCol] = TileEmpty;
						break;
					default:
						break;
				}
				return true;
			}
			// Tile is a locked door
			else if(map->tiles[*currRow][*currCol - 1] == TileLockedDoor)
			{
				if(avatarUseKey(avatar))
				{
					map->tiles[*currRow][*currCol - 1] = TileDoor;
					*currCol -= 1;
					return true;
				}
			}
			return false;

		default:
			return false;
	}
}

/*
	Keeps track of remaining gems
*/
int mapGemsRemaining(const Map* map)
{
	int gems = 0;
	for(int i = 0; i < map->rows; i++)
	{
		for(int j = 0; j < map->cols; j++)
		{
			if(map->tiles[i][j] == TileGem)
				gems++;
		}
	}
	return gems;
}


