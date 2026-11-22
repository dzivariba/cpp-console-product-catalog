#include "sort.h"
#include <cstring>

int compare_by_quantity_desc(product* first, product* second)
{
    if (first->quantity > second->quantity) return -1;
    if (first->quantity < second->quantity) return 1;
    return 0;
}

int compare_by_category_asc_price_desc(product* first, product* second)
{
    int cat_cmp = strcmp(first->category, second->category);
    if (cat_cmp != 0)
    {
        return cat_cmp;
    }
    if (first->price > second->price) return -1;
    if (first->price < second->price) return 1;
    return 0;
}

void selection_sort(product* array[], int size, int (*compare)(product*, product*))
{
    for (int i = 0; i < size - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < size; j++)
        {
            if (compare(array[j], array[min_index]) < 0)
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            product* temp = array[i];
            array[i] = array[min_index];
            array[min_index] = temp;
        }
    }
}

static void merge(product* array[], int left, int mid, int right, int (*compare)(product*, product*))
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    product** left_arr = new product * [n1];
    product** right_arr = new product * [n2];

    for (int i = 0; i < n1; i++)
    {
        left_arr[i] = array[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        right_arr[j] = array[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (compare(left_arr[i], right_arr[j]) <= 0)
        {
            array[k++] = left_arr[i++];
        }
        else
        {
            array[k++] = right_arr[j++];
        }
    }

    while (i < n1)
    {
        array[k++] = left_arr[i++];
    }
    while (j < n2)
    {
        array[k++] = right_arr[j++];
    }

    delete[] left_arr;
    delete[] right_arr;
}

static void merge_sort_recursive(product* array[], int left, int right, int (*compare)(product*, product*))
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort_recursive(array, left, mid, compare);
        merge_sort_recursive(array, mid + 1, right, compare);
        merge(array, left, mid, right, compare);
    }
}

void merge_sort(product* array[], int size, int (*compare)(product*, product*))
{
    if (size > 1)
    {
        merge_sort_recursive(array, 0, size - 1, compare);
    }
}