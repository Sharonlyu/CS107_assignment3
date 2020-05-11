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
      //      printf("%s", buffer);   
    }
    //buffer = realloc(buffer, sizeof(char)* buflen*2);
        
    while (strchr(buffer, '\n') == NULL) {
      //                  printf("%s", buffer);

       //       printf("%lu", strlen(buffer));
       char new[buflen];
       if (fgets(new, buflen, fp) == NULL) {
	 //	 printf("%s", buffer);
	 break;
       }
       buffer = realloc(buffer, sizeof(char)* buflen*2);
       //       char * p = buffer + buflen;
       for (int i = 0; i < buflen; i++) {
	 buffer[i + buflen] = new[i];
       }
	 //       strncpy(p, new, buflen);
       //       buffer = fgets(buffer, buflen * 2, fp); 
       //       printf("%s", buffer);
       buflen *= 2;
     }
    if (strchr(buffer, '\n') == NULL) {
      buffer[buflen - 1] = '\0';
    }
        buffer[strchr(buffer, '\n') - buffer] = '\0';
    //    printf("%s", buffer);
    return buffer;
}
