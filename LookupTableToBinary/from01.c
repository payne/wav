#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h> // man 3 open asks for this
#include <fcntl.h> // man 3 open asks for this
#include <unistd.h> // man 3 read asks for this

char *nibbleLookup[]={
  "0000",
  "0001", // 1
  "0010",
  "0011", // 3
  "0100",
  "0101", // 5
  "0110",
  "0111", // 7
  "1000",
  "1001",
  "1010",
  "1011",
  "1100", // 12
  "1101",
  "1110", // 14
  "1111" // 15
  };

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
  printf("highString='%s' lowString='%s' highNibble=%d lowNibble=%d\n", highString, lowString, highNibble, lowNibble);
  printf("\tline=%s\n", line);
  unsigned char uc = (unsigned char) (highNibble * 2*2*2*2 + lowNibble);
  return uc;
}

void outputBinary(char *s) {
  int len = strlen(s);
  for (int i=0; i < len; i++) {
    printf("%s\n", toBinary(s[i]));
  }
}

int mainForPrototype(void) { // not used....
  printf("Hello World\n");
  outputBinary("abcdABCD");
  return 0;
}

int main_to01(int argc, char *argv[], char *envp[]) {
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

int main(int argc, char *argv[], char *envp[]) {
  int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
  printf("fd=%d\n", fd);
  assert(fd >= 0);
  char line[88];
  while (gets(line)) { // do not care about buffer overflow in this toy program
    unsigned char uc = computeByte(line);
    write(fd, &uc, 1);
  }
  close(fd);
  return 0;
}


