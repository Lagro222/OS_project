#include "string.h"

int mystrcmp(const char *s1, const char *s2){
  while (*s1 && *s2 && *s1 == *s2) {
      s1++;
      s2++;
  }
  return  *s1 - *s2;
}

int mystrlen(char *str){
  int i = 0;
  while(*str != '\0'){
    i++;
  }
  return i;
}

char* rmlast(char *str){
    
  char *str2 = str;
  int len = mystrlen(str2);
  
  if(len > 0){
    str2[len - 1] = '\0';
  }

  return  str2;
}
