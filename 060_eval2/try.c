#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char * str = malloc(13 * sizeof(*str));
  for (int i = 0; i < 10; i++) {
    str[i] = 'a';
  }
  str[3] = '\0';
  str = realloc(str, 15 * sizeof(*str));
  for (int i = 0; i < 15; i++) {
    printf("%c ", str[i]);
  }
  printf("%s\n", str);
  free(str);
  return 0;
}
