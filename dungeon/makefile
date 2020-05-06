# makefile for the dungeon assignment

# These variables control the specifics of the compilation
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O1
LDFLAGS = -lm

# When you type "make", it will default to trying to build all the programs
default: TestAction TestTile TestAvatar TestMap Dungeon

# To build just the TestAction executable, type "make TestAction"
TestAction: TestAction.c Action.o
	${CC} ${CFLAGS} TestAction.c Action.o -o TestAction ${LDFLAGS}

# To build just the TestTile executable, type "make TestTile"
TestTile: TestTile.c Tile.o
	${CC} ${CFLAGS} TestTile.c Tile.o -o TestTile ${LDFLAGS}

# To build just the TestAvatar executable, type "make TestAvatar"
TestAvatar: TestAvatar.c Avatar.o
	${CC} ${CFLAGS} TestAvatar.c Avatar.o -o TestAvatar ${LDFLAGS}

# To build just the TestAvatar executable, type "make TestAvatar"
TestMap: TestMap.c Map.o Avatar.o Tile.o
	${CC} ${CFLAGS} TestMap.c Map.o Avatar.o Tile.o -o TestMap ${LDFLAGS}
	
# To build just the Dungeon executable, type "make Dungeon"
Dungeon: Dungeon.c Map.h Avatar.h Action.h
	${CC} ${CFLAGS} Dungeon.c Action.o Tile.o Avatar.o Map.o -o Dungeon ${LDFLAGS}

# Builds just the object file for the Action data type
Action.o: Action.c Action.h
	${CC} ${CFLAGS} -c Action.c

# Builds just the object file for the Tile data type
Tile.o: Tile.c Tile.h
	${CC} ${CFLAGS} -c Tile.c

# Builds just the object file for the Avatar data type
Avatar.o: Avatar.c Avatar.h
	${CC} ${CFLAGS} -c Avatar.c

# Builds just the object file for the Map data type
Map.o: Map.c Map.h Action.h Tile.h 
	${CC} ${CFLAGS} -c Map.c

run: Dungeon
	./Dungeon

clean: 
	rm -f TestAction TestTile TestAvatar TestMap Dungeon *.o
	