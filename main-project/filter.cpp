#include "filter.h"
#include <cstring>

product** filter(product* array[], int size, bool (*check)(product* element), int& result_size)
{
    product** result = new product * [size];
    result_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (check(array[i]))
        {
            result[result_size++] = array[i];
        }
    }
    return result;
}

bool check_product_by_category(product* element)
{
    return strcmp(element->category, "Промтовары") == 0;
}

bool check_product_by_price(product* element)
{
    return element->price > 100.0;
}