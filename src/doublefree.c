#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char* s1 = malloc(sizeof(char) * 7);
  strcpy(s1, "hello");
  
  char* s2 = s1;

  printf("%s\n", s1);
  free(s1);
  free(s2);
}
