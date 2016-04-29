/*
  lc1.c
  
  Authors: Megan Anderson
  Date: April 25, 2016
  Completed: April 28, 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int grandtotalLines = 0;// the total number of lines in all text files

void countLines(void *fileName);

main(int argc, char *argv[])
{ 
  int numOfFiles = 0;
  //go through each of the given files...
  int i;
  for(i = 1; i < argc; i++)
    {
      ++numOfFiles;
      countLines(argv[i]);
    }//end of for

  printf("Total lines in all files = %d\n", grandtotalLines);
}//end of main

void countLines(void *fileName)
{
  char *fName = (char *) fileName;
  int fd;//the file desciptor
  FILE *fpointer;//the file pointer
  char *buf = malloc(1000 * sizeof(char*));//have a buffer to hold a chunk of text
  char *isGood;//boolean. if there is a value other than NULL, end loop and stop searching for '\n'
  
if((fd = open(fName, O_RDONLY)) != -1)
    {
      int n, totalLines = 0;
      while((n = read(fd, buf, 1000)) != 0)//read in a chunk of text
	{
	  char aChar = ' ';
	  int i = 0;
	  for (i = 0; i < n; i++)
	    {
	      aChar = buf[i];//get a character from the buffer...
	      if(aChar == '\n')
		{
		  totalLines++;//increase the number of lines...
		}//end of if
	    }//end of while	  
	}
      close(fd);
      printf("%d lines in %s\n", totalLines, fName);//print out the total number of lines...
      grandtotalLines += totalLines;
    }//end of if ...open
}//end of countLines
