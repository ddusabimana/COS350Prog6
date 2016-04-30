/*=======================================================
 Project: 6 
 Name: lc3.c
 April 30, 2016
 Author: Daniel Dusabimana
 =========================================================*/
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>



#define   RUN_AS_LC1   (0)
#define   RUN_AS_LC3   (1)
#define   BUFF_SIZE    (8 * 1024 * 1204)


struct thrdData {
  int  thread_id;
  unsigned long ulLineCount;
  char strFileName[256];
} thrdBlock;



void * thrdFunction(void *);
unsigned long countLines(char *);



int main(int argc, char ** argv)
{
  int i, m;
  unsigned long j, k;
  pthread_t * pthrdArray;
  pthread_t * pthrdPointer;
  struct thrdData * pthrdbArray;
  struct thrdData * pthrdbPointer;
  
  
  
  i = j = k = 0;
  if(RUN_AS_LC1) {
    for(m = 1; m < argc; m++) {
      k = countLines(argv[m]);
      printf("\nFile %s : %ld lines", argv[m], k);
      j += k;
    }
    printf("\nTotal : %ld lines\n", j);
  }
  
  
  if(RUN_AS_LC3) {
    m = argc - 1;
    pthrdArray = (pthread_t *)malloc(m * sizeof(pthread_t));
    pthrdbArray = (struct thrdData *)malloc(m * sizeof(thrdBlock));
    memset(pthrdArray, 0x0, (m * sizeof(pthread_t)));
    memset(pthrdbArray, 0x0, (m * sizeof(thrdBlock)));
    for(i = 0; i < m; i++) {
      pthrdPointer = pthrdArray + i;
      pthrdbPointer = pthrdbArray + i;
      pthrdbPointer->thread_id = i;
      pthrdbPointer->ulLineCount = 0;
      strcpy(pthrdbPointer->strFileName, argv[i + 1]);
      pthread_create(pthrdPointer, NULL, thrdFunction, pthrdbPointer);
    }
    j = 0;
    for(i = 0; i < m; i++) {
      pthrdPointer = pthrdArray + i;
      pthrdbPointer = pthrdbArray + i;
      pthread_join(*pthrdPointer, NULL);
      printf("\nThread %d : %s - %ld lines", pthrdbPointer->thread_id, pthrdbPointer->strFileName, pthrdbPointer->ulLineCount);
      if(pthrdbPointer->ulLineCount > 0) {
	j += pthrdbPointer->ulLineCount;
      }
    }
    printf("\nTotal : %ld lines\n", j);
    if(pthrdArray != NULL) {
      free(pthrdArray);
    }
    if(pthrdbArray != NULL) {
      free(pthrdbArray);
    }
  }
 
 
 
}


void * thrdFunction(void * thrdbData)
{
  FILE * fpointer;
  char * chrBuffer;
  unsigned long lc;
  unsigned long i, n;
  struct thrdData * pthrdbPointer;
  //.
  lc = 0;
  chrBuffer = NULL;
  pthrdbPointer = (struct thrdData *)thrdbData;
  if((chrBuffer = (char *)malloc(BUFF_SIZE * sizeof(char))) != NULL) {
    if((fpointer = fopen(pthrdbPointer->strFileName, "r")) != NULL) {
      while((n = fread(chrBuffer, sizeof(char), (size_t)BUFF_SIZE, fpointer)) != 0) {
	for(i = 0; i < n; i++) {
	  if(chrBuffer[i] == '\n') {
	    lc++;
	  }
	}
      }
      fclose(fpointer);
      free(chrBuffer);
      pthrdbPointer->ulLineCount = lc;
    }
    else {
      pthrdbPointer->ulLineCount = -1;
    }
  }
  else {
    pthrdbPointer->ulLineCount = -1;
  }
  return(thrdbData);
}


unsigned long countLines(char * strFileName)
{
  FILE * fpointer;
  char * chrBuffer;
  unsigned long i, n;
  unsigned long lc;
  //.
  chrBuffer = NULL;
  i = n = lc = 0;
  if((chrBuffer = (char *)malloc(BUFF_SIZE * sizeof(char))) != NULL) {
    if((fpointer = fopen(strFileName, "r")) != NULL) {
      while((n = fread(chrBuffer, sizeof(char), (size_t)BUFF_SIZE, fpointer)) != 0) { //.Read a chunk
	for(i = 0; i < n; i++) {
	  if(chrBuffer[i] == '\n') {
	    lc++; //.Increment line count
	  }
	}
      }
      fclose(fpointer);
      free(chrBuffer);
      return(lc);
    }
  }
  return(-1);
}

