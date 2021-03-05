#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h> // man 3 open asks for this
#include <fcntl.h> // man 3 open asks for this
#include <unistd.h> // man 3 read asks for this
#include "nibbles.h"


int findNibble(char *str) {
  assert(strlen(str) <= 10); // eight 0/1 and a newline...
  int location = 0;
  while (location < 16) {
    if (!strcmp(str, nibbleLookup[location++])) break;
  }
  return location-1;
}

unsigned char computeByte(char *line) {
  char highString[8], lowString[8];
  strncpy(highString, line, 4);
  strncpy(lowString, &line[4], 4);
  int highNibble = findNibble(highString);
  int lowNibble = findNibble(lowString);
  // printf("highString='%s' lowString='%s' highNibble=%d lowNibble=%d\n", highString, lowString, highNibble, lowNibble);
  // printf("\tline=%s\n", line);
  unsigned char uc = (unsigned char) (highNibble * 2*2*2*2 + lowNibble);
  return uc;
}

int main(int argc, char *argv[], char *envp[]) {
  int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
  assert(fd >= 0);
  char line[88];
  while (gets(line)) { // do not care about buffer overflow in this toy program
    unsigned char uc = computeByte(line);
    write(fd, &uc, 1);
  }
  close(fd);
  return 0;
}


