#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

typedef struct flags
{
    int selEf;
    int selUs;
    char *uid;
    int selPr;
    char *pid;
    int fail;

} flags;

flags *parsecommand(int, char **);
#endif