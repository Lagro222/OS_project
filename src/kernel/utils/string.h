#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

int mystrcmp(const char *s1, const char *s2);
int mystrlen(const char *str);
int mystrncmp(const char *s1 , const char *s2, int n);
char* rmlast(char *str);
bool contains(const char *target , const char* search);
void add_last( char *str , const char c);
char *reverse_string(char *str);
#endif // !STRING_H
