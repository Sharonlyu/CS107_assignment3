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
    
    char *buffer = malloc(sizeof(char) * buflen );
    if (fgets(buffer, buflen, fp) == NULL) {
      return NULL;
    }


    while (strchr(buffer, '\n') == NULL) {
       char new[buflen];

       if (fgets(new, buflen, fp) == NULL) {
	 buffer[buflen - 1 ] = '\0';
	 printf("%s", buffer);
	 return buffer;
       }
       buffer = realloc(buffer, sizeof(char)* buflen*2);

       for (int i = 0; i < buflen; i++) {
	 buffer[i + buflen] = new[i];
	 //	 if (new[i] == '\n') {
	 // buffer[i + buflen] = '\0';

	 //	   return buffer;
	 // }
       }

       buflen *= 2;
     }

        buffer[strchr(buffer, '\n') - buffer] = '\0';
    //    printf("%s", buffer);
    return buffer;
}
