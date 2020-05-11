#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_NUM_LINES 100000
#define DEFAULT_NUM_LINES 10

/*
 * Helper function: sliding_window(FILE *fp, char **window, int n)
 * -------------------------------------------------
 * returns nothing, but prints the last n lines   
 */
void sliding_window(FILE *fp, char **window, int n) {

  char *newLine;     
  int count = 0;     
  int start = 0;

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

  free(newLine);
  /* print lines and free memories after mallocs */
  
  for (int i = start; i <= n - 1; i++) {
    printf("%s\n", window[i]);
    free(window[i]);
  }
  for (int i = 0; i < start; i++) {
    printf("%s\n", window[i]);
    free(window[i]);
  }

  if(count > MAX_NUM_LINES) {
    free(window);
  }
}

/*
 * Function: print_last_n(FILE *fp, int n)
 * --------------------------------------
 * returns nothing, but prints the last n lines
*/
void print_last_n(FILE *fp, int n) {
   
  char *lines[MAX_NUM_LINES];
  char **window;

  if(n <= MAX_NUM_LINES){
    sliding_window(fp, lines, n);
  } else {
    window = (char **)malloc((n * sizeof(char *)));

    /* assert that window is not null */
    assert(window);
    /* this window will be freed later */
    sliding_window(fp, window, n);
  }
}

// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

/*
 * Function: convert_arg(const char *str, int max)
 *---------------------------------------------
 * Returns the integer as int after converting from string
 */
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
