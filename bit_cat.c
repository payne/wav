#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * output the bits in a message as `0` and `1`
 * 
 * Example if message is "A" then the bits will be  "0100 0001" (0x41)
 * Exmaple if message is "AB" then the bits will be "0100 0001 0100 0010"
 */


char *toBits(char *message) {
   static int position = 0; // Not thread safe
   switch (position++) {
     case 0: return "0";
     case 1: return "1";
     case 2: return "1";
     default: return NULL;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) { printf("Usage:\n\t%s <message>\n", argv[0]); }
  char *message = argv[1];

  char *bitString = NULL;
  while (NULL != (bitString = toBits(message))) {
     printf("%s\n", bitString);
  } 
  return 0; 
}
