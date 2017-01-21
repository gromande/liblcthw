#include "minuit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create() {
  list = List_create();
  mu_assert(list != NULL, "Failed to create list");
  return NULL;
}

char *test_destroy() {
  List_clear_destroy(list);
  return null;
}

char *test_push_pop() {
  mu_assert(List_count(list) == 0, "Wrong count before test.");

  List_push(list, test1);
  mu_assert(List_first(list) == test1, "Wrong first value.");
  mu_assert(List_last(list) == test1, "Wrong last value.");

  List_push(list, test2);
  mu_assert(List_first(list) == test1, "Wrong first value.");
  mu_assert(List_last(list) == test2, "Wrong last value.");

  List_push(list, test3);
  mu_assert(List_first(list) == test1, "Wrong first value.");
  mu_assert(List_last(list) == test3, "Wrong last value.");
  mu_assert(List_count(list) == 3, "Wrong count on push.");

  char *val = List_pop(list);
  mu_assert(val == test3, "Wrong value on pop");

  *val = List_pop(list);
  mu_assert(val == test2, "Wrong value on pop");

  *val = List_pop(list);
  mu_assert(val == test1, "Wrong value on pop");
  mu_assert(List_count(list) == 0, "Wrong count after pop.");

  return NULL;
}

char *test_shift_unshift() {
  mu_assert(List_count(list) == 0, "Wrong count before test.");

  List_unshift(list, test1);
  mu_assert(List_first(list) == test1, "Wrong first value.");
  mu_assert(List_last(list) == test1, "Wrong last value.");

  List_unshift(list, test2);
  mu_assert(List_first(list) == test2, "Wrong first value.");
  mu_assert(List_last(list) == test1, "Wrong last value.");

  List_unshift(list, test3);
  mu_assert(List_first(list) == test3, "Wrong first value.");
  mu_assert(List_last(list) == test1, "Wrong last value.");
  mu_assert(List_count(list) == 3, "Wrong count on unshift.");

  char *val = List_shift(list);
  mu_assert(val == test3, "Wrong value on pop");
}
