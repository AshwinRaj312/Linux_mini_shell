/*
NAME 	: ASHWIN RAJ K
DATE 	: 02/12/23
DESCRIPTION : CREATE MINI LINUX SHELL AS A PART OF LINUX INTERNAL MODULE
*/
#include "main.h"
extern int pid,temp;
Slist *head=NULL;

void signal_handler(int signum)
{
    switch(signum)
    {
        case SIGINT:
        {    
            if(pid>0)
            {
                //child exists               
                kill(pid,SIGINT);                
            }
            break;
        }
        case SIGTSTP:
        {    
            if(pid>0)            
            {   
                printf("Stopped %d\n",pid);                    
		if(insert_at_first(&head,pid) == -1 )
	        {
		    printf("INFO : Insertion failure\n");
		}
                kill(pid,SIGTSTP);
		pid=0;
            }
            break;
        }
    }
}

int main()
{

    char prompt[50],input[50];
    int cmd_type;
    char buf[50];
    strcpy(prompt,"minishell$");

    signal(SIGINT,signal_handler);
    signal(SIGTSTP,signal_handler);

    while(1)
    {
        printf("%s ",prompt);
        scanf("%[^\n]",input);
        __fpurge(stdin);
   
        if(input[0]=='\0')
        {
            continue;
        }
        else if( strncmp(input,"PS1=",4) == 0 )
        {
            strcpy(prompt, input+4);
        }
      
        else if(strcmp(input,"echo $$")==0)
        {
            printf("%d\n",getpid());
        }
        else if(strcmp(input,"echo $?")==0)
        {
           //display exit sts of prev cmd 
            printf("%d\n",temp);
        }

        else if( (cmd_type=get_command_type(input)) ==INTERNAL )
        {
            execute_internal_commands(input);
        }

        else if(cmd_type==EXTERNAL)
        {
            execute_external_commands(input);
        }
    
        else
        {
            printf("Commands not found\n");
        }
        input[0]='\0';          //making the string empty to avoid recurring previous commands' output while pressing enter key without anything typed in minishell by user
    }
}





// jobs

int insert_at_first(Slist **head1,int data)
{
    Slist *new = malloc(sizeof(Slist));
    
    if(new ==NULL)
    {
	    return -1;
    }	
    new->data = data;
    new->link = NULL;

    if(head1 == NULL)
    {
        *head1=new;
    }
    else
    {
        new->link=*head1;
        *head1=new;
        return 1;
    }
}

