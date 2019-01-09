#include <stdio.h>
#include <stdlib.h>

// decode the frob encoding
int frob(char c) {
  return c ^ 42;
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
void badIO() {
  if(ferror(stdin)) {
    fprintf(stderr, "Error: Bad read");
    exit(1);
  }
}

int main(void) {
  // introduce the current character, current word,
  // list of all words, and increment variables
  char c;
  char *w = (char*)malloc(sizeof(char));
  char **ww = (char**)malloc(sizeof(char*));
  int cNum = 0;
  int wNum = 0;
  int i = 0;
  int j = 0;

  // check bad malloc
  if(w == NULL || ww == NULL){
    fprintf(stderr, "Error: Bad memory allocation");
    exit(1);
  }

  while(!feof(stdin)) {
    // get the next character
    c = getchar();
    badIO();
    // if it's the end of a word with more than one letter
    if(cNum > 0 && (c == ' ' || feof(stdin) || c == EOF)) {
      w = (char*)realloc(w, (cNum + 1) * sizeof(char));
      w[cNum] = ' ';
      // start a new word and add old to array of all words
      char *newword = (char*)malloc(sizeof(char));
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
    }
    else {
      // if it's not the end of word, attatch the letter
      w = (char*)realloc(w, (cNum + 1) * sizeof(char));
      if(w != NULL) {
	w[cNum] = c;
	cNum++;
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
	putchar(ww[i][j]);
        break;
      }
      else {
	putchar(ww[i][j]);
      }
    }
  }
  // free your memory
  for (i = 0; i < wNum; i++) {
    free(ww[i]);
  }
  free(ww);
  exit(0);
}
