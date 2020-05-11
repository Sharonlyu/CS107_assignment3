#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
/* initial estimate of number of uniq lines
 * resize-as-you-go, add in increments of 100
 */
#define ESTIMATE 100


/*
 * Function - print_uniq_lines((FILE *fp)
 * -------------------------------------
 * Takes a file stream fp as an argument, and 
 * returns nothing, but prints the number of same lines.
 */

void print_uniq_lines(FILE *fp) {

  char* line = read_line(fp);

  char* currentLine = malloc(strlen(line) + 1);

  assert(currentLine);
  
  memcpy(currentLine, line, strlen(line) + 1);
  free(line);

  char* newLine = NULL;
  int count = 1;

  while ((newLine = read_line(fp))) {
    /* the current line matches the new line*/
    if (strcmp(currentLine, newLine) == 0) {
      count++;
    } else {
      printf("%7d %s\n", count, currentLine);
      memcpy(currentLine, newLine, strlen(newLine) + 1);

      /*reset the count to 1 because this current line is the start again*/
      count = 1;
    }
    free(newLine);
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
