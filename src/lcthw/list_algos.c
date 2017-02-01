#include <stdlib.h>
#include <lcthw/dbg.h>
#include <lcthw/list.h>
#include <lcthw/list_algos.h>

void List_swap(ListNode *node) {
  //debug("Swapping values %s %s", node->value, node->next->value);
  void *value = node->value;
  node->value = node->next->value;
  node->next->value = value;
}

int List_bubble_sort(List *list, List_compare cmp) {
  int swapped = 1;
  while (swapped) {
    swapped = 0;
    LIST_FOREACH(list, cur) {
      if (cur->next != NULL && cmp(cur->value, cur->next->value) > 0) {
        List_swap(cur);
        swapped = 1;
      }
    }
  }

  return 0;
}

List *List_merge_sort(List *list, List_compare cmp) {
  return NULL;
}
