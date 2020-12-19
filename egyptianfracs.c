#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long euclidean_modulo(long a, long b) {
  long m = a % b;
  if (m < 0) {
    m = (b < 0) ? m - b : m + b;
  }
  return m;
}

char * decompose(char * nrStr, char * drStr) {
  printf("Let's get Egyptian on %s/%s!\n", nrStr, drStr);

  if (strncmp(nrStr, "0", 2) == 0) {
    printf("Invalid entry!\n");
    char * result = (char * ) calloc(1, sizeof(char));
    strcpy(result, "");
    return result;
  }
  long xi = atoi(nrStr);
  long yi = atoi(drStr);
  if (xi % yi == 0) {
    char * result = (char * ) calloc(16, sizeof(char));
    sprintf(result, "%ld", xi / yi);
    printf("%s/%s = %s\n", nrStr, drStr, result);
    return result;
  }
  long a, b, c;
  double x = (double) xi;
  double y = (double) yi;
  int cursor = 0;
  char * flatfracs = (char * ) calloc(128, sizeof(char));
  char ** fracs = malloc(128 * sizeof(char * ));
  char qckstra[256], qckstrb[256];

  while (1) {
    memset(qckstra, 0, sizeof(qckstra));
    memset(qckstrb, 0, sizeof(qckstrb));
    fracs[cursor] = (char * ) malloc(128 * sizeof(char));
    fracs[cursor + 1] = (char * ) malloc(128 * sizeof(char));
    a = euclidean_modulo((long)(-y), (long) x);
    b = (long)(y * ceil(y / x));
    //if((x/y) == x)
    c = (long) ceil(y / x);
    sprintf(qckstra, (c != 1) ? "1/%ld" : "%ld", c);
    sprintf(qckstrb, "%ld/%ld", a, b);
    strcpy(fracs[cursor], qckstra);
    strcpy(fracs[cursor + 1], qckstrb);
    if (a == 0) break;
    x = (double) a;
    y = (double) b;
    cursor++;
  }
  printf("%s/%s = ", nrStr, drStr);
  long qsum = 0;
  for (int i = 0; i <= cursor; i++) {
    while (strncmp(fracs[i], "1", 3) == 0) {
      qsum += atoi(fracs[i]);
      i++;
    }
    if (qsum != 0) {
      sprintf(flatfracs, "%ld,", qsum);
      printf("%ld + ", qsum);
      qsum = 0;
    }
    strcat(flatfracs, fracs[i]);
    if (cursor != i) strcat(flatfracs, ",");
    printf("%s", fracs[i]);
    printf((cursor != i) ? " + " : "\n");
    free(fracs[i]);
    fracs[i] = NULL;
  }
  free(fracs);
  fracs = NULL;
  return flatfracs;
}
int main(int argc, char * argv) {
  // Example
  decompose("1000", "417");
}