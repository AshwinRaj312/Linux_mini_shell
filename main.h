#ifndef MAIN_H
#define MAIN_H
#define EXTERNAL 1
#define INTERNAL 2
#define CMD_NOT_FOUND 3

#include<stdio.h>
#include<stdio_ext.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<unistd.h>

typedef struct node
{
    int data;
    struct node *link;
}Slist;

char *(cmd)[10];
int get_command_type(char *);
void execute_internal_commands(char *);
void convert_string(char *input, char *cmd[10]);
void execute_external_commands(char *);
int insert_at_first(Slist **,int);
void print_list(Slist *);

#endif


