#include "samples/prototypes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
/* initial allocation will be for min size, if not big enough, doubles
 * to 64, then 128, then 256, etc. as needed to accommodate the entire line
 * resize-as-you-go, doubling each time.
 */
#define MINIMUM_SIZE 32


char *read_line(FILE *fp) {
    int buflen = MINIMUM_SIZE;
    
    char *buffer = malloc(buflen );

    /* If fp contains nothing */
    if (fgets(buffer, buflen, fp) == NULL) {
      free(buffer);
      return NULL;
    }

    /* while we haven't encountered the newline character */
    while (strchr(buffer, '\n') == NULL) {
     
       /* try reading the next buflen character */
       char p[buflen];
       fgets(p, buflen, fp);

       /* if failed, stop reading further */
       if (p == NULL) break;

       buffer = realloc(buffer, buflen * 2);

       /* assert that the buffer is not null */
       assert(buffer);
       /* otherwise concatenate to the buffer string and continue reading */
       buffer = strncat(buffer, p, buflen);

       buflen *= 2;
    }

    if (strchr(buffer, '\n') == NULL) {
      buffer[strlen(buffer)- 1] = '\0';
    } else {
      buffer[strchr(buffer, '\n') - buffer] = '\0';
    }
    return buffer;
}
