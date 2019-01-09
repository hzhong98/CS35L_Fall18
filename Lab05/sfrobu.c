#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int xCase = 0;


// decode the frob encoding
int frob(char c) {
  c = c ^ 42;
  if(xCase == 1 && islower(c)) {
    c = toupper((unsigned char) c);
  }
  return c;
}

// return the sign of a - b
int frobcmp(char const *a, char const *b) {
  while(*a != ' ' && *b != ' ') {
    if (*b == ' ' || frob(*a) > frob(*b)) {
      return 1;
    }
    else if (*a == ' ' || frob(*b) > frob(*a)) {
      return -1;
    }
    a++;
    b++;
  }
  return 0;
}

// create a sorting function for qsort to use
int sortCmp(const void *a, const void *b) {
  return frobcmp(*(const char**) a, *(const char**) b);
}

// check for bad input
void badIO(ssize_t in) {
  if(in == -1) {
    fprintf(stderr, "Error: Bad read");
    exit(1);
  }
}

int main(int argc, char **argv) {  
  if(argc >= 2) {
    if(!strncmp(argv[1], "-f", 2)) {
      xCase = 1;
    }
  }
  
  // introduce the current character, current word,
  // list of all words, and increment variables
  // struct stat init;
  char c = 'a';
  char *cp = &c;
  char *w = (char*)malloc(sizeof(char));
  char **ww = (char**)malloc(sizeof(char*));
  int cNum = 0;
  int wNum = 0;
  int ccNum = 0;
  int i = 0;
  int j = 0;
  int in = 1;
  // in = fstat(STDIN_FILENO,&init);
  // badIO(in);
  // size_t initN = init.st_size + 1;
  // printf("the size of file is %i",initN);
  // ww = (char**)realloc(ww, initN * sizeof(char));
  // Allocating all memory beforehand doesn't make any sense
  // because you can't get the size of STDIN...
  // Anything less and it's actually pointless because you have
  // to allocate each memory either way. I give up.

  // check bad malloc
  if(w == NULL || ww == NULL){
    fprintf(stderr, "Error: Bad memory allocation");
    exit(1);
  }
  // printf("entering loop");
  // printf("in is %i", in);
  while(in != 0) {
    // get the next character
    in = read(STDIN_FILENO, cp, 1);
    badIO(in);
    // printf("%c", c);
    // if it's the end of a word with more than one letter
    if(cNum > 0 && (c == ' ' || in == 0)) {
      // printf("add word");
      w = (char*)realloc(w, (cNum + 1) * sizeof(char));
      w[cNum] = ' ';
      ccNum++;
      // start a new word and add old to array of all words
      char *newword = (char*)malloc(sizeof(char));
      // if(ccNum < initN) {
      // printf("no more space need");
      // ww[wNum] = w;
      // wNum++;
      // w = newword;
      // cNum = 0;
      // }
      // else {
      // printf("neeed more space");
      ww = (char**)realloc(ww, (wNum + 1) * sizeof(char*));
      if(newword != NULL && ww != NULL) {
	ww[wNum] = w;
	wNum++;
	w = newword;
	cNum = 0;
      }
      else {
	fprintf(stderr, "Error: Bad memory allocation");
	free(w);
	exit(1);
      }
      // }
    }
    else {
      // if it's not the end of word, attatch the letter
      // printf("adding letter");
      w = (char*)realloc(w, (cNum + 1) * sizeof(char));
      if(w != NULL) {
	w[cNum] = c;
	cNum++;
	ccNum++;
      }
      else {
	fprintf(stderr, "Error: Bad memory allocation");
	exit(1);
      }
    }
  }
  // sort this final array
  qsort(ww, wNum, sizeof(char*), sortCmp);
  // print it all out
  for(i = 0; i < wNum; i++) {
    for(j = 0; ; j++) {
      if(ww[i][j] == '\0') {
	break;
      }
      else if(ww[i][j] == ' ') {
	in = write(STDOUT_FILENO, &ww[i][j], 1);
	badIO(in);
	// putchar(ww[i][j]);
        break;
      }
      else {
	in = write(STDOUT_FILENO, &ww[i][j], 1);
        badIO(in);
	// putchar(ww[i][j]);
      }
    }
  }
  // free your memory
  for (i = 0; i < wNum; i++) {
    free(ww[i]);
  }
  free(ww);
  free(w);
  exit(0);
}
