#ifndef SORT_H
#define SORT_H

#include "product.h"

int compare_by_quantity_desc(product* first, product* second);
int compare_by_category_asc_price_desc(product* first, product* second);

void selection_sort(product* array[], int size, int (*compare)(product*, product*));
void merge_sort(product* array[], int size, int (*compare)(product*, product*));

#endif
