#include "processing.h"
#include <cstring>

double process(product* array[], int size, const char* category)
{
    double total_cost = 0.0;
    for (int i = 0; i < size; i++)
    {
        if (strcmp(array[i]->category, category) == 0)
        {
            total_cost += array[i]->price * array[i]->quantity;
        }
    }
    return total_cost;
}