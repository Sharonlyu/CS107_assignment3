#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* initial estimate of number of uniq lines
 * resize-as-you-go, add in increments of 100
 */
#define ESTIMATE 100

int compare(char *current, char *new, int *count){
  if (strcmp(current, new) == 0) {

    (*count)++;
    return *count;
  }
  return 1;
}


/*
 * Function: print_uniq_lines
 * ----------------------------
 *   Returns void, prints all unique lines using:
 *
 *          fp: user input file
 *
 *   returns: void
 *            prints the count of the same lines followed by the line
 */

void print_uniq_lines(FILE *fp)
{

  char* line = read_line(fp);

  /* requests a new memory of length of the next line read from fp*/
  char* currentLine = malloc(strlen(line) + 1);

  /*copies the line to allocated memory */
  memcpy(currentLine, line, strlen(line) + 1);
  free(line);

  char* newLine = NULL;
  int count = 1;

  while ((newLine =read_line(fp))) {
    int match = compare(currentLine, newLine, &count);

    /* if current line matches the new line */
    if (match > 1) {
      free(newLine);
      continue;
    }

    /* if the new line is different from current line */
    if(match == 1) {
      printf("%7d %s\n", count, currentLine);
      memcpy(currentLine, newLine, strlen(newLine) + 1);

      count = 1;
      free(newLine);
    }
  }

  /* prints the count of the same lines followed by the line*/
  printf("%d" "%s\n",count, currentLine);

}

/*
void print_uniq_lines(FILE *fp) {
    // TODO: your implementation
  char* line = read_line(fp);
  char* current = malloc(strlen(line) + 1);
  
  memcpy(current, line, strlen(line) + 1);
  free(line);

  char* newline = NULL;
  int count = 1;

  while ((newline = read_line(fp))) {
    if (strcmp(current, newline) == 0) {
      count++;
      free(newline);
      continue;
    } else {
      printf("%d %s\n", count, current);
      memcpy(current, newline, strlen(newline) + 1);
      count = 1;
      free(newline);
    }    
  }

  printf("%d" "%s\n",count, current);
}
*/

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
