// Header file for the Tile data type
// DO NOT MODIFY!

#ifndef TILE_H
#define TILE_H

#include <stdbool.h>

typedef enum {TileInvalid, TileEmpty, TileWall, TileDoor, TileLockedDoor, TileSecretPassage, TileGem, TileKey} Tile;

Tile tileFromChar(char ch);
void tileDisplay(Tile tile);
bool tilePassable(Tile tile);

#endif
