#include "main.h"
extern short int cmd_index;
extern Slist *head;
void execute_internal_commands(char *input)
{
    char buf[50];
    int stopPID,Gstatus;
    convert_string(input,cmd);
    switch(cmd_index)
    {
        case 0:
        {   //cd
            if(cmd[1] != NULL)
	        {
		        if(chdir(cmd[1]) == -1)
		        {
		            perror("chdir");
		        }
	        }
	        else
	        {
		        fprintf(stderr,"cd : missing argument\n");
	        }
            break;
     	}
        case 1:
        {    //mkdir
	        if(cmd[1] != NULL)
    	    {
	            if(mkdir(cmd[1],0777) == -1)
		        {
                perror("mkdir"); 
                }
            }
            else
	        {
	            fprintf(stderr,"mkdir : missing argument"); 
	        }        
	        break;
	    }
        case 2:
            exit(0);
            break;
        case 3:
	    {
            //rmdir
     	    if(cmd[1] != NULL)
	        {
	            if(rmdir(cmd[1]) == -1)
	            { 
 		            perror("rmdir"); 
	            }
	        }
	        else
	        {   
	            fprintf(stderr,"rmdir : missing argument"); 
	        }
	        break;
	    }        
    	case 4:
            //pwd
            printf("%s\n",getcwd(buf,50));
            break;
        case 5:
	    print_list(head);
            break;
        case 6:  //fg
        {
            if (head == NULL) 
	    {
        	printf("No stopped processes to continue.\n");
        	break;
    	    }

	    stopPID = head->data;
            head = head->link; // Remove the most recently stopped process from the list

	    // Put the process in the foreground
            tcsetpgrp(STDIN_FILENO, stopPID);

            if (kill(stopPID, SIGCONT) < 0) 
            {
                perror("kill (SIGCONT)");
            }

            if (waitpid(stopPID, &Gstatus, WUNTRACED) == -1) 
            {
            	perror("waitpid");
            }

            // Put the shell back in the foreground
            tcsetpgrp(STDIN_FILENO, getpid());
            
	    break;
        }
        case 7:   //bg
        {
            if (head == NULL) 
	    {
        	printf("No stopped processes to continue.\n");
        	break;
    	    }

	    stopPID = head->data;
            head = head->link; // Remove the most recently stopped process from the list

	    if (kill(stopPID, SIGCONT) < 0) 
            {
                perror("kill (SIGCONT)");
            } 
            else 
            {
                printf("Continued process with PID %d in the background\n", stopPID);
            }

	    break;
	}
    }
}


//print_list

void print_list(Slist *head1)
{
    Slist *temp=head1;
    if(head1==NULL)
	printf("INFO : List is empty\n");
    else
    {
        while(temp)
        {
            printf("%d -> ",temp->data);
            temp=temp->link;
        }
    printf("NULL\n");
    }
} 

