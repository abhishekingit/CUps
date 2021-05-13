#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_parser.h"

//the main loop for the program
int main(int argc, char *argv[])
{
    flags *activeFlags = parsecommand(argc, argv);
    //see which flags are active and call specific functions

    return 0;
}
