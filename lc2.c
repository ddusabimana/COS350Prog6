#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Error function
#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

int totalLines;

int main(int argc, char *argv[])
{ 
  //define variables
  pid_t pid;
  int i;
  int numRead;
  char foo[4096];

  totalLines = 0;

  for(i = 1; i < argc; i++)
    {
      int fd[2];

      //Pipe and fork and throw any errors

      if (pipe(fd)==-1)
	die("pipe");

      if ((pid = fork()) == -1)
	die("fork");

      if (pid  == 0) //Child Process
        {
	  //Redirect standard out to the writing end of the pipe
	  dup2 (fd[1], STDOUT_FILENO);
	  close(fd[0]);
	  close(fd[1]);
	  //Run child logic
	  execlp("lc1", "lc1", argv[i], (char *)0);
	  //Finish this fork
	  exit(0);
        }
      else if (pid > 0) //Parent Process
        {
	  //Close output side of pipe
	  close(fd[1]);
	  int nbytes = read(fd[0], foo, sizeof(foo));
	  //Add a terminating character where there is a newline (only print out the first line)
	  strtok(foo, "\n");
	  //Now print out foo
	  printf("%.*s\n", nbytes, foo);
	  //Now truncate the string at the first space (leave the numbers)
	  strtok(foo, " ");
	  //Now pull the number and add it to the total lines
	  totalLines += atoi(foo);
	  wait(NULL);
        }
      else
	{
	  printf("Error\n");
	}

    }
  printf("Total lines in all files = %d\n", totalLines);
  exit(0);
}

