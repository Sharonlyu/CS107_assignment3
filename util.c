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
    if (fgets(buffer, buflen, fp) == NULL) {
      return NULL;
    }

    while (strchr(buffer, '\n') == NULL) {
       
       buffer = realloc(buffer, buflen * 2);

       char p[buflen];
       fgets(p, buflen, fp);
       if (p == NULL) break;
       buffer = strncat(buffer, p, buflen);

       buflen *= 2;
      
     }
    if (strchr(buffer, '\n') == NULL) buffer[strlen(buffer)- 1] = '\n';
        buffer[strchr(buffer, '\n') - buffer] = '\0';

    return buffer;
}
