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
  return count;
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

void add_last(char *str, const char c){
  int i = 0;
  while (str[i] != '\0') {
    i++;
  }
  str[i] = c;
  str[i+1] = '\0';
}

char *reverse_string( char *str){
      int len = mystrlen(str);
      static char str_end[20];
      str_end[0] = '\0';
      for(int i = len - 1  ; i >= 0 ; i--){
        add_last(str_end, str[i]);
      }
      return str_end;
}
