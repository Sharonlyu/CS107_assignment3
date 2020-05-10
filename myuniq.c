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
