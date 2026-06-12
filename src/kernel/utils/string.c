#include "string.h"
#include <stdbool.h>

int mystrcmp(const char *s1, const char *s2){
  while (*s1 && *s2 && *s1 == *s2) {
      s1++;
      s2++;
  }
  return  *s1 - *s2;
}

int mystrncmp(const char *s1, const char *s2, int n){

   for(int i = 0 ; i < n ; i++){
      if (s1[i] != s2[i]) return 1;
      if (s1[i] == '\0') return 0;
   }
  return  0;
}

int mystrlen(const char *str){
  int i = 0;
  int count = 0;
  while(str[i] != '\0'){
    count++;
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

bool contains(const char *target ,const char *search){
  int target_len = mystrlen(target);
  int search_len = mystrlen(search);

  for (int i = 0 ; i <= target_len - search_len; i++) {
     if (mystrncmp(&target[i], search, search_len) == 0) return  true; 
  }
  return false;
}

