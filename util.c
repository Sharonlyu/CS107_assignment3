#include "samples/prototypes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
/* initial allocation will be for min size, if not big enough, doubles
 * to 64, then 128, then 256, etc. as needed to accommodate the entire line
 * resize-as-you-go, doubling each time.
 */
#define MINIMUM_SIZE 32


char *read_line(FILE *fp) {
    int buflen = MINIMUM_SIZE;
    
    char *buffer = malloc(sizeof(char) * buflen );
    if (fgets(buffer, buflen, fp) == NULL) {
      return NULL;
    }
    
    while (strchr(buffer, '\n') == NULL) {
      buffer = realloc(buffer, sizeof(char) * buflen*2);
      char new[buflen];
      printf("%s",new);
      if (fgets(new, buflen , fp) == NULL) {
	//	strncpy(buffer + buflen, new, buflen);
	printf("%s", buffer);
	
	buffer[strlen(buffer) - 1] = '\0';
	return buffer;
      }
      strncpy(buffer + buflen, new, buflen);
      printf("%s", buffer);
      
      buflen *= 2;
    }

    buffer[strchr(buffer, '\n') - buffer] = '\0';

    return buffer;
}
