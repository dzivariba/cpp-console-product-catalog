#ifndef FILTER_H
#define FILTER_H

#include "product.h"

product** filter(product* array[], int size, bool (*check)(product* element), int& result_size);

bool check_product_by_category(product* element);
bool check_product_by_price(product* element);

#endif
