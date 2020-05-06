// Header file for the Avatar data type
// DO NOT MODIFY!

#ifndef AVATAR_H
#define AVATAR_H

#include <stdbool.h>

typedef struct
{
    char* name;   // Name of the avatar
    int gems;     // Number of gems collected
    int keys;     // Number of keys currently held
} Avatar;

void avatarInit(Avatar* avatar, const char* name);
void avatarUninit(Avatar* avatar);
bool avatarUseKey(Avatar* avatar);
void avatarAddKey(Avatar* avatar);
void avatarAddGem(Avatar* avatar);
void avatarDisplay(const Avatar* avatar);

#endif

