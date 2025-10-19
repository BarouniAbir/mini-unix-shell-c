#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define CMD_LENGTH 150
#define HISTORY_SIZE 50

char history[10][HISTORY_SIZE];
int count = 0;
int QUIT = 0;

void displayHistory()
{
    
    printf("Shell command history:\n");
    
    int i;
    int j = 0;
    int histCount = count;
    for (i = 0; i<10;i++)
    {
        printf("%d.  ", histCount);
        while (history[i][j] != '\n' && history[i][j] != '\0')
        {	
            printf("%c", history[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        histCount--;
        if (histCount ==  0)
        break;
    }
} 

char **splitLine(char *line)
{
	char **tokens = (char **)malloc(sizeof(char *) * 64);
	char *token;
	char delim[10] = " \t\n\r\a";
	int pos = 0, bufsize = 64;
	if (!tokens)
	{
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[pos] = token;
		pos ++;
		if (pos >= bufsize)
		{
			bufsize += 64;
			line = realloc(line, bufsize * sizeof(char *));
			if (!line)
			{
			printf("Error\n");
			exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[pos] = NULL;
	return tokens;
}

int ourShell_exit();


char *builtin_cmd[] = {"quit"};
int (*builtin_func[]) (char **) = {&ourShell_exit}; 

int numBuiltin()
{
	return sizeof(builtin_cmd)/sizeof(char *);
}


int ourShell_exit()
{
	QUIT = 1;
	return 0;
}


int ourShellLaunch(char **args)
{
	pid_t pid, wpid;
	int status;
	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
    printf("[~%s] %% ", getenv("PWD"));
		}
	exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		printf("[~%s] %% ", getenv("PWD"));
	}
	else
	{
	do 
	{
    wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int execShell(char **args)
{
	int ret;
	if (args[0] == NULL)
	{
		return 1;
	}
	for (int i=0; i< numBuiltin(); i++) 
	{
		if(strcmp(args[0], builtin_cmd[i])==0) 
			return (*builtin_func[i])(args);
	}
	ret = ourShellLaunch(args);
	return ret;
}


int ourShellScript(char filename[100])
{
	printf("Current batch mode processing %s", filename);
	FILE *fptr;
	char line[200];
	char **args;
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("Unable to open file.\n");
		return 1;
	}
	else
	{
		printf("File Opened.\n");
		while(fgets(line, sizeof(line), fptr)!= NULL)
		{
			printf("\n%s", line);
			args=splitLine(line);
			execShell(args);
		}
	}
	free(args);
	fclose(fptr);
	return 1;
}


int main(int argc, char *argv[])
{

if (argc == 2){
ourShellScript(argv[1]);
}

else {
    char command[CMD_LENGTH];
    int hist, i;
while (1)
{
    printf("[~%s] %% ", getenv("PWD"));
    fgets(command, CMD_LENGTH, stdin);
    command[strlen(command) - 1] = '\0';

    if (strcmp("quit",command)==0)
        {
            exit(0);
        }
        
    else if(strcmp(command,"history")==0)
    {		
            if(count>0)
		{

                displayHistory();
		}
		else
		{
		printf("No Commands in the history\n");
		}
		exit(0);
        }


    for (i = 9;i>0; i--)
	strcpy(history[i], history[i-1]);
    
    strcpy(history[0],command);
    count++;
	if(count>10)
	{ count=10;
	}

    pid_t n = fork();
    if (n == 0)
    {
      int status = execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        if (status == -1)
        {
        printf("%s\n",strerror(errno));
        }
        exit(0);
    }
    else
    {
        wait(&n); 
    } 
}
}
}
