#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_NUM_LINES 100000
#define DEFAULT_NUM_LINES 10


void print_slide(FILE *fp, char **window, int n)
{

  char *newLine;              /* new line that stores a line read from fp */
  int count = 0;              /* count of lines read */
  int start = 0;              /* starting index of N lines) */


  /* Read n lines fp file */
  while ((newLine = read_line(fp))) {

    if (count == n) {

      start %= n;
      free(window[start]);
      window[start] = newLine;
      start++;

    } else {

      window[count] = newLine;
      count++;

    }

  }
  start--;

  /* print the last (n-(1+start)) and first (start+1) lines */
  for (int i = start + 1; i <= n - 1; i++) {
    printf("%s\n", window[i]);
  }
  for (int i = 0; i <= start; i++) {
    printf("%s\n", window[i]);
  }

  /* free n_lines */
  for(int i = 0; i < n; i++){
    free(window[i]);
  }
  if(count > MAX_NUM_LINES) {
    free(window);
  }
}

void print_last_n(FILE *fp, int n) {
    // TODO: your implementation
  char *lines[MAX_NUM_LINES];
  char **window;

  if(n <= MAX_NUM_LINES){
    print_slide(fp, lines, n);
  }else{
    window = (char **)malloc((n * sizeof(char *)));
    assert(window != NULL);
    print_slide(fp, window, n);
  }
}

// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

int convert_arg(const char *str, int max) {
    char *end;
    long n = strtol(str, &end, 10);
    if (*end != '\0') {
        error(1, 0, "Invalid number '%s'", str);
    }
    if (n < 1 || n > max) {
        error(1, 0, "%s is not within the acceptable range [%d, %d]", str, 1, max);
    }
    return n;
}

int main(int argc, char *argv[]) {
    int num_lines = DEFAULT_NUM_LINES;

    if (argc > 1 && argv[1][0] == '-') {
        num_lines = convert_arg(argv[1] + 1, MAX_NUM_LINES);
        argv++;
        argc--;
    }

    FILE *fp;
    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            error(1, errno, "cannot access '%s'", argv[1]);
        }
    }
    print_last_n(fp, num_lines);
    fclose(fp);
    return 0;
}
