#include "main.h"
#include "ext_cmds_list.h"
char *internalcommands[]={"cd","mkdir","exit","rmdir","pwd","jobs","fg","bg"};
short int cmd_index;
int get_command_type(char *input)
{
    char cmd[strlen(input)];
    strcpy(cmd,input);
    char *token=strtok(cmd," ");
    for(int i=0;internalcommands[i];i++)
    {
        if(strcmp(token,internalcommands[i])==0)
        {
            cmd_index=i;
            return INTERNAL;
        }
    }
    for(int j=0;ext_commands[j];j++)
    {
	if(strcmp(token,ext_commands[j])==0)
	{		
    	    return EXTERNAL;
	}
    }
    return CMD_NOT_FOUND;
}


        

