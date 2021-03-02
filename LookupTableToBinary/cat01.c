#include <stdio.h>
#include <string.h>
#include <assert.h>

char *nibbleLookup[]={
  "0000",
  "0001", // 1
  "0010",
  "0011", // 3
  "0100",
  "0101", // 5
  "0110",
  "0111", // 7
  "1000"
  };

char *nibbleToBinary(int nibble) {
  assert(nibble >= 0);
  assert(nibble <= 8);
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

int main(void) {
  printf("Hello World\n");
  outputBinary("abcdABCD");
  return 0;
}