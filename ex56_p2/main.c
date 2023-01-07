#include <stdio.h>

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t);

int main() {
    char s[] = "programming in c";
    char t[] = "gram";
    printf("index: %d\n", strindex(s, t));
    return 0;
}

int strindex(char *s, char *t) {
   char *b = s;
   char *p, *r;
   while(*s) {
       for (p=s, r=t; *r != '\0' && *p == *r; p++, r++)
           ;
       if (r > t && *r == '\0') return s - b;
       s++;
   }
    return -1;
}