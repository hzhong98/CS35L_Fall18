#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// check for bad input
void badIO() {
  if(ferror(stdin)) {
    fprintf(stderr, "Error: Bad read");
    exit(1);
  }
}

int main(int argc, char **argv) {
  if(argc != 3) {
    fprintf(stderr, "Error: Wrong num of args\n");
    exit(1);
  }
  
  char *from = argv[1];
  char *to = argv[2];
  int i = 0;
  int j = 0;
  // Make sure the args have same number characters
  if(strlen(from) != strlen(to)) {
    fprintf(stderr, "Error: Bad arg lengths");
    exit(1);
  }
  // Make sure there are no duplicates in the from string
  for(i = 0; i < strlen(from); i++) {
    for(j = i + 1; j < strlen(from); j++) {
      if(from[i] == from[j]) {
	fprintf(stderr, "Error: Duplicate in from");
	exit(1);
      }
    }
  }
  // Apparently it is better to get a character first
  // before using feof(stdin), also check bad input
  char c = getchar();
  badIO();
  while(!feof(stdin)) {
    for(i = 0; i < strlen(from); i++) {
      if(c == from[i]) {
	// Replace translateable characters
	c = to[i];
	break;
      }
    }
    // Output the character, get new character
    putchar(c);
    c = getchar();
    badIO();
  }
  return 0;
}
