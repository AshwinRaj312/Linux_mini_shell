#include "main.h"
int pid,temp;
void convert_string(char *input,char *cmd[])
{
    int i=0;
    char *token=strtok(input," ");
    while(token!=NULL && i<9)
    {
        cmd[i++]=strdup(token);
        token=strtok(NULL," ");
    }
    cmd[i]=NULL;
}

void execute_external_commands(char *input)
{

    for(int i=0;i<9;i++)
    {
        cmd[i]=NULL;
    }

    //convert one string into multiple string
    convert_string(input,cmd);
    int status;
    pid=fork();
    if(pid==0)
    {
        //child process
        if(execvp(cmd[0],cmd)==-1)
        {
            perror("execvp");
            exit(0);
        }
    }
    else if(pid>0)
    {
        //parent process wait till child completes its process
        int ret=waitpid(pid,&status,WUNTRACED);
        printf("%s\n",input);
	temp=WIFEXITED(status);
        if(WIFEXITED(status))
        {
            printf("The child terminated normally with code %d\n",WIFEXITED(status));
        }
        else
        {
            printf("The child terminated abnormally\n");
        }
    }
}

