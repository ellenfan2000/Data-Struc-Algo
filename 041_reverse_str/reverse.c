#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  //WRITE ME!
  if (str != NULL) {
    char curr;
    int size = 0;
    while (str[size] != '\0') {
      size++;
    }
    for (int i = 0; i < size / 2; i++) {
      curr = str[i];
      str[i] = str[size - 1 - i];
      str[size - 1 - i] = curr;
    }
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  //char str7[] = "1 2 3 4 4 5"" 6 7 8 8";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
