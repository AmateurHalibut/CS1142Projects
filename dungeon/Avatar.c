#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Avatar.h"

/*
	Alex Hromada
	anhromad
	M45218886
	Program 8: Dungeon
	CS1142
	Spring 2020
	
	This program implements methods declared in Avatar.h
	Initializes an Avatar object
*/


/*
	Allocates memory and initializes the avatar
*/
void avatarInit(Avatar* avatar, const char* name)
{
	avatar->name = malloc(sizeof(char) * strlen(name) + 1);
	avatar->keys = 0;
	avatar->gems = 0;
	strcpy(avatar->name, name);
	
}

/*
	Deallocates and uninitializes the avatar
*/
void avatarUninit(Avatar* avatar)
{
	free(avatar->name);
	avatar->name = NULL;
}

/*
	Checks if the player has any keys, returns true and uses one if so
*/
bool avatarUseKey(Avatar* avatar)
{
	if(avatar->keys > 0)
	{
		avatar->keys -= 1;
		return true;
	}
	else
	{
		return false;
	}
}

/*
	Adds key to player inventory
*/
void avatarAddKey(Avatar* avatar)
{
	avatar->keys += 1;
}

/*
	Adds gem to player inventory
*/
void avatarAddGem(Avatar* avatar)
{
	avatar->gems += 1;
}

/*
	Prints avatar data
*/
void avatarDisplay(const Avatar* avatar)
{
	printf("%s's inventory: gems %d, keys %d\n", avatar->name, avatar->gems, avatar->keys);
}