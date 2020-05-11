#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
/* initial estimate of number of uniq lines
 * resize-as-you-go, add in increments of 100
 */
#define ESTIMATE 100

struct st {
  char*  name;
  int   count;
};
 

/* Function: contains(char** set, char *line)
 * --------------------------------
 * returns true if set contains line.
 */

bool contains(struct st** set, char* line, int* uniq) {
  for (int i = 0; i < 100; i++) {
    struct st* st = *set + i;
    if (strcmp(st->name, line) == 0) {
      return true;
    }
  }
      //set = realloc(set, sizeof(set) + 100 * sizeof(struct st));
  struct st* new = (struct st *) malloc(sizeof(struct st));
  new->name = line;
  new->count = 1;
  (*uniq)++;
  set[(*uniq) + 1] = new;
  return false;
    
}

/*
 * Function - print_uniq_lines((FILE *fp)
 * -------------------------------------
 * Takes a file stream fp as an argument, and 
 * returns nothing, but prints the number of same lines.
 */


void print_uniq_lines(FILE *fp) {
  struct st* set;
  set = malloc(100 * sizeof(struct st));
  char* line = read_line(fp);
  int uniq = 0;
  char* currentLine = malloc(strlen(line) + 1);

  assert(currentLine);
  
  memcpy(currentLine, line, strlen(line) + 1);
  free(line);

  char* newLine = NULL;
  int count = 1;

  while ((newLine = read_line(fp))) {
    /* the current line matches the new line*/
    //  if (strcmp(currentLine, newLine) == 0) {
    if (contains(&set, newLine, &uniq)) {
      count++;
      continue;
      //free(newLine);
    } else {
      printf("%7d %s\n", count, currentLine);
      memcpy(currentLine, newLine, strlen(newLine) + 1);

      /*reset the count to 1 because this current line is the start again*/
      count = 1;
      //free(newLine);
    }
    //    free(newLine);
    }



  /*  print the number with width 7 */
  printf("%7d %s\n",count, currentLine);
}



// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            error(1, errno, "cannot access '%s'", argv[1]);
        }
    }
    print_uniq_lines(fp);
    fclose(fp);
    return 0;
}
