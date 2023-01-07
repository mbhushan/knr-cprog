#include <stdio.h>

/* Exercise 1-19. Write a function "reverse(s)" that reverses the character
 * string "s". Use it to write a program that reverses its input a line at a
 * time.
 */

#define MAXLEN 81 /* max length of the string */

void reverse(char str[]);

int main() {
//    char s[] = "mani bhushan";
//    printf("orginal: %s\n", s);
//    reverse(s);
//    printf("reversed: %s\n", s);

      int ch, i;
      char line[MAXLEN];

      i=0;

      while ((ch = getchar()) != '\n') {
          line[i++] = ch;
      }
      if (i >= (MAXLEN-1)) {
          line[MAXLEN-1] = '\0';
      } else {
          line[i] = '\0';
      }
    printf("original: %s\n", line);
    reverse(line);
    printf("%s\n", line);

    return 0;
}

void reverse(char str[]) {
    int i, j;
    j = 0;

    printf("ref fn: %s\n", str);

    while (str[j++] != '\0');

    j = j - 1; /* length of the string */
    i = 0;
    --j; /* last index of the string. */
    while (i < j) {
        char ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        ++i;
        --j;
    }
}

