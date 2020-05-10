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

    if (ungetc(getc(fp), fp) == EOF) return NULL;
    char *buffer = malloc(sizeof(char) * buflen);
    fgets(buffer, 4 * buflen, fp);
    buffer[strchr(buffer, '\n') - buffer] = '\0';
    return buffer;
}
