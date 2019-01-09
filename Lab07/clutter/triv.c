#include <stdio.h>
#include <math.h>

int main () {
  double num = 3.0;
  num = sqrt(num);
  num = cos(num);
  printf("%.17g", num);
  return 0;
}
