/*
  lc1.c
  
  Authors: Megan Anderson
  Date: April 25, 2016
  
  ***************works with smaller files, not the larger ones yet....
                 the counts are off by a few....

 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int totalLines;// the total number of lines in a text file

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
  char *isGood;//boolean. if there is a value other than NULL, end loop and stop searching for '\n'
  
if((fd = open(fName, O_RDONLY)) != -1)
    {
      while(read(fd, buf, 1000) != 0)//read in a chunk of text
	{
	  	  //for testing
	  //printf("Current total = %d\n",totalLines);
	  //printf("%s", buf);
	  isGood = strchr(buf, '\n');//find the first occurance of '\n' and return
	                             //a string pointer to the first occurance of '\n'
	  do
	    {
	      if(isGood != NULL)//if we continue to find '\n'...
		{
		  totalLines++;//increment the number of total lines
		}
	      isGood = strchr(isGood + 1, '\n');//find the next occurance of '\n'...
	      
	      //for testing...
	      //printf("Current total = %d\n",totalLines);
	      //printf("%s", isGood);

	    }while(isGood != NULL);//when we cannot find anymore '\n', exit the loop
	}
      printf("\n");
      close(fd);
    }//end of if fopen
}//end of countLines
