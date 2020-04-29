#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

void printHelper (char* str) {
  // printf(str);
}

void prints (element_t ev) {
  char* e = ev;
  printf ("%s\n", e);
}

void printi (element_t ev) {
  // int* e = ev;
  // printf ("%d\n", *e);
}

void inc (element_t* rv, element_t av) {
  int* a = av, **r = (int**) rv;
  if (*r == NULL)
    *r = malloc(sizeof(int));
  **r = *a + 1;
}

void parse_string(element_t *rv, element_t av) {
  char* a = av;
  int** r = (int**) rv;
  *r = malloc(sizeof(int));
  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(a, &endp, 10);
  if (!*endp) {
    /* String was non-empty and strtol conversion succeeded - integer */
    **r = value;
  } else {
    **r = -1;
  }
  return;
}

void stringToNull (element_t* rv, element_t av, element_t bv) {
  int *a = av;
  char *b = bv;
  char **r = (char**) rv;
  if (*r == NULL)
    *r = malloc(sizeof(int));

  if (*a == -1) {
    int len = strlen(b) + 1;
    *r = realloc(*r, len);
    strcpy(*r, b);
  } else {
    **r = 0;
  }

  return;
}

int isPos (element_t av) {
  int *a = av;
  return (*a > 0);
}

int isNotNull (element_t av) {
  char *a = av;
  return (a[0] != '\0');
}

void truncate (element_t* rv, element_t av, element_t bv) {
  int *a = av;
  char *b = bv;
  char **r = (char**) rv;
  int len = *a;
  *r = strndup(b, len);
  return;
}

void concat (element_t* rv, element_t av, element_t bv) {
  char *a = av;
  char *b = bv;
  char **r = (char**) rv;

  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(b, &endp, 10);
  if (b[0] != '\0' && endp[0] == '\0') { // no inputs
    //dab <o/
  } else {
    int len = strlen(b) + 2 + strlen(*r);
    *r = realloc(*r, len);
    *r = strcat(*r, b);
    *r = strcat(*r, " ");
  }
  return;
}

void max (element_t* rv, element_t av, element_t bv) {
  int *a = av, *b = bv, **r = (int**) rv;
  if (*a < *b) {
    **r = *b;
  } else {
    **r = *a;
  }
  //**r = (*a < *b) ? *b : *a;
}

int main(int argc, char **argv) {

  printHelper("step 1: strings from cmd line\n");
  struct list* l0 = list_create();

  for (int i = 0; i < argc - 1; i++) {
    list_append(l0, argv[i+1]);
  }

  // list_foreach (prints, l0);

  printHelper("step 2: check strings to see if they are numbers \n");
  struct list* l1 = list_create();
  list_map1(parse_string, l1, l0);
  // list_foreach (printi, l1);

  printHelper("step 3: numbers are NULLed out\n");
  struct list* l2 = list_create();
  list_map2(stringToNull, l2, l1, l0);
  // list_foreach (prints, l2);

  printHelper("step 4: number list has no negatives\n");
  struct list* l3 = list_create();
  list_filter(isPos, l3, l1);
  // list_foreach (printi, l3);

  printHelper("step 5: string list has no NULLs\n");
  struct list* l4 = list_create();
  list_filter(isNotNull, l4, l2);
  //list_foreach (prints, l4);

  printHelper("step 6: strings are truncated using numbers\n");
  struct list* l5 = list_create();
  list_map2(truncate, l5, l3, l4);

  printHelper("step 7: print truncated strings\n");
  list_foreach (prints, l5);

  printHelper("step 8: print concatenated truncated strings\n");
  char * str = malloc(sizeof(char));
  *str = '\0';
  list_foldl(concat, (element_t*) &str, l5);
  if (strlen(str) > 1) {
    str[strlen(str)-1] = '\0'; // remove last trailing white space
  }
  printf("%s\n", str);

  printHelper("step 9: print max int\n");
  int * num = malloc(sizeof(int));
  *num = 0;
  list_foldl(max, (element_t*) &num, l3);
  printf("%d\n", *num);

  free(str);
  free(num);

  list_foreach(free, l1);
  list_foreach(free, l2);
  list_foreach(free, l5);

  list_destroy(l0);
  list_destroy(l1);
  list_destroy(l2);
  list_destroy(l3);
  list_destroy(l4);
  list_destroy(l5);

}
