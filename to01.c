#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h> // man 3 open asks for this
#include <fcntl.h> // man 3 open asks for this
#include <unistd.h> // man 3 read asks for this
#include "nibbles.h"

char *nibbleToBinary(int nibble) {
  assert(nibble >= 0);
  assert(nibble <= 15);
  return nibbleLookup[nibble];
}

char *toBinary(char c) {
  static char result[10]={0};
  int highNibble = (0x00f0 & c) / (2*2*2*2);
  int lowNibble = 0x000f & c;
  // printf("\n\tc='%c' highNibble=%d lowNibble=%d\n", c, highNibble, lowNibble);

  sprintf(result, "%s%s",  nibbleToBinary(highNibble), nibbleToBinary(lowNibble));
  return result;
}


void outputBinary(char *s) {
  int len = strlen(s);
  for (int i=0; i < len; i++) {
    printf("%s\n", toBinary(s[i]));
  }
}

int main(int argc, char *argv[], char *envp[]) {
  int fd = open(argv[1], O_RDONLY);
  int CHUNK_SIZE=1024;
  unsigned char chunk[CHUNK_SIZE];
  int numBytes=CHUNK_SIZE;

  while (0 != (numBytes = read(fd, chunk, CHUNK_SIZE))) {
    for (int i=0; i < numBytes; i++) {
      printf("%s\n", toBinary(chunk[i]));
    }
  }
  close(fd);
  return 0;
}


