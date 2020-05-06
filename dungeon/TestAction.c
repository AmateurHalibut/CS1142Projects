// Test program for the Action data type

#include "Action.h"
#include <stdio.h>

int main(void)
{
    // Test an invalid character, all the directions, and the quit command
    char chars[] = {'t', 'w', 's', 'a', 'd', 'q'};    
    for (int i = 0; i < 6; i++)
    {
        printf("'%c' -> %d\n", chars[i], actionFromChar(chars[i]));
    }
    return 0;
}
