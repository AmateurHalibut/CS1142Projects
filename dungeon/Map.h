// Header file for the Map data type
// DO NOT MODIFY!

#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

#include "Tile.h"
#include "Action.h"
#include "Avatar.h"

typedef struct
{
    int rows;       // Vertical size of the map
    int cols;       // Horizontal size of the map
    Tile** tiles;   // 2D array of Tile structures
    int avatarRow;  // Current row of the avatar on the map
    int avatarCol;  // Current column of the avatar on the map
} Map;

bool mapInit(Map* map, const char* filename);
void mapUninit(Map* map);
void mapDisplay(const Map* map);
bool mapMoveAvatar(Map* map, Avatar* avatar, Action action);
int mapGemsRemaining(const Map* map);

#endif
