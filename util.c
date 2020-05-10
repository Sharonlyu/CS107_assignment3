#include "samples/prototypes.h"
#include <stdlib.h>
#include <string.h>

/* initial allocation will be for min size, if not big enough, doubles
 * to 64, then 128, then 256, etc. as needed to accommodate the entire line
 * resize-as-you-go, doubling each time.
 */
#define MINIMUM_SIZE 32


char *read_line(FILE *fp) {

    int buflen = MINIMUM_SIZE;

    int ch = ungetc(getc(fp), fp);
    if (ch == EOF) return NULL;
    char *buffer = malloc(sizeof(char)*buflen);
    fgets(buffer,4* buflen, fp);
    char *s = strchr(buffer, '\n');
    int i = s - buffer;
    buffer[i] = '\0';
    return buffer;
}
