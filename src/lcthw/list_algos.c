#include <stdlib.h>
#include <lcthw/dbg.h>
#include <lcthw/list.h>
#include <lcthw/list_algos.h>

void List_swap(ListNode *node) {
  check_mem(node);

  void *value = node->value;
  node->value = node->next->value;
  node->next->value = value;

error:
  return;
}

int List_bubble_sort(List *list, List_compare cmp) {
  check_mem(list);

  int sorted = 1;

  if (List_count(list) <= 1) return 0; //Already sorted
  do {
    sorted = 1;
    LIST_FOREACH(list, cur) {
      if (cur->next && cmp(cur->value, cur->next->value) > 0) {
        List_swap(cur);
        sorted = 0;
      }
    }
  } while (!sorted);

  return 0;

error:
  return -1;
}

List *List_merge(List *left, List *right, List_compare cmp) {
  check_mem(left);
  check_mem(right);

  List *result = List_create();
  check_mem(result);

  while (List_count(left) > 0 && List_count(right) > 0) {
    void *leftFirst = List_first(left);
    void *rightFirst = List_first(right);

    if (cmp(leftFirst, rightFirst) > 0) {
      List_push(result, rightFirst);
      List_remove(right, right->first);
    } else {
      List_push(result, leftFirst);
      List_remove(left, left->first);
    }
  }

  LIST_FOREACH(left, leftCur) {
    List_push(result, leftCur->value);
  }

  LIST_FOREACH(right, rightCur) {
    List_push(result, rightCur->value);
  }

  List_destroy(left);
  List_destroy(right);
  return result;

error:
  return result;
}

List *List_merge_sort(List *list, List_compare cmp) {
  check_mem(list);

  int size = List_count(list);

  // Base case. A list of zero or one elements is sorted, by definition.
  if (size <= 1) return list;

  // Recursive case. First, divide the list into equal-sized sublists
  // consisting of the first half and second half of the list.
  List *left = List_create();
  List *right = List_create();

  int i = 0;
  LIST_FOREACH(list, cur) {
    if (i < (size / 2)) {
      List_unshift(left, cur);
    } else {
      List_unshift(right, cur);
    }
    i++;
  }

  // Recursively sort both sublists.
  left = List_merge_sort(left, cmp);
  right = List_merge_sort(right, cmp);

  // Then merge the now-sorted sublists.
  return List_merge(left, right, cmp);

error:
  return list;
}
