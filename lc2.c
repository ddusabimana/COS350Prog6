#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//Line count version 2

void countLines(void *fileName);

main(int argc, char *argv[])
{ 
  //go through each of the given files...
  pid_t child;
  int i;
  for(i = 1; i < argc; i++)
    {
      int fd[2];

      if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
      }

      child = fork();
      if(child)
        {
	  printf("Error\n");
          continue;
        }
      //Child breaks off two processes, this consumes the second one
      else if (child == 0)
        {
	  printf("Duplicate\n");
	  //Run child logic
	  countLines(argv[i]);

	  //Close input side of pipe
	  close(fd[0]);
	  exit(0);

          break;
        }
      else
        {
	  //Close output side of pipe
	  close(fd[1]);
          printf("Error\n");
        }

    }//end of for

  printf("Finished Main Loop\n");
  exit(0);
}//end of main

void countLines(void *fileName)
{
  printf("Counting lines for %s\n", (char *)fileName);
  execlp("lc1", "lc1", (char *)fileName, (char *)0);
}
