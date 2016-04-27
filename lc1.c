/*
  lc1.c
  
  Authors: Megan Anderson
  Date: April 25, 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int totalLines;

void countLines(void *fileName);

main(int argc, char *argv[])
{
  if(argc != 2)
    {
      printf("Missing file name!\n");
      exit(1);
    }
  
  totalLines = 0;
  countLines(argv[1]);
  printf("Total lines = %d\n", totalLines);
}//end of main

void countLines(void *fileName)
{
  char *fName = (char *) fileName;
  int fd;//the file desciptor
  char *buf = malloc(1000 * sizeof(char*));//have a buffer to hold a chunk of text
  char *aChar;//token to hold the '\n' char
  
if((fd = open(fName, O_RDONLY)) != -1)
    {
      while(read(fd, buf, 1000) != 0)//read in a chunk of text
	{
	  //get the "\n" char...
	  aChar = strtok(buf, "\n");
	  //if we find one, increment totalLines
	  if(strcmp(aChar, "\n") == 0)
	    {
	      totalLines++;
	    }
	}
      close(fd);
    }//end of if fopen
}//end of countLines
