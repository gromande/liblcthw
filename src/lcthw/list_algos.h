#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <stdlib.h>
#include <lcthw/list.h>

int List_bubble_sort(List *words, List_compare cmp);
List *List_merge_sort(List *words, List_compare cmp);

#endif
