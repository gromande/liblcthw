#include <lcthw/darray.h>
#include <stdlib.h>
#include <lcthw/dbg.h>

DArray *DArray_create(size_t element_size, int initial_max){
  DArray *array = calloc(1, sizeof(DArray));
  check_mem(array);
  array->element_size = element_size;
  array->max = initial_max;
  check(array->max > 0, "You must set an initial max > 0.");
  array->expand_rate = DEFAULT_EXPAND_RATE;
  array->end = 0;
  array->contents = calloc(initial_max, element_size);
  check_mem(array->contents);
  return array;

error:
  if (array) free(array);
  return NULL;
}

void DArray_destroy(DArray *array) {
  if (array) {
    if (array->contents) free(array->contents);
    free(array);
  }
}

void DArray_clear(DArray *array) {
  check_mem(array);
  int i = 0;
  for (i = 0; i < DArray_count(array); i++) {
    DArray_free(DArray_get(array, i));
  }
  error:
    return;
}

void DArray_clear_destroy(DArray *array) {
  DArray_clear(array);
  DArray_destroy(array);
}

static inline int DArray_resize(DArray *array, int new_size) {
  check(new_size > 0, "New size must be > 0.");
  array->max = new_size;

  void *contents = realloc(array->contents, new_size * array->element_size);
  check_mem(contents);

  array->contents = contents;
  return 0;
error:
  return -1;
}

void DArray_expand(DArray *array) {
  check_mem(array);
  int old_size = array->max;
  check(DArray_resize(array, array->max + array->expand_rate) != -1, "Unable to expand array.");
  memset(array->contents + old_size, 0, array->expand_rate);
error:
  return;
}

void DArray_contract(DArray *array) {
  check_mem(array);
  int new_size = array->end < array->expand_rate ? (int) array->expand_rate : array->end + 1;
  check(DArray_resize(array, new_size) != -1, "Unable to contract array.");
error:
  return;
}

void DArray_push(DArray *array, void *element) {
  check_mem(array);
  if (DArray_count(array) == DArray_max(array)) {
    DArray_expand(array);
  }
  DArray_set(array, DArray_end(array) + 1, element);
error:
  return;
}

void *DArray_pop(DArray *array) {
  check_mem(array);
  check(DArray_count(array) > 0, "darray attempt to pop form empty array.");
  void *element = DArray_remove(array, array->end);
  array->end--;
  return element;
error:
  return NULL;
}
