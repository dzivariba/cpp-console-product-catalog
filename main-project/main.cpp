#include <iostream>
#include <iomanip>
#include "product.h"
#include "file_reader.h"
#include "constants.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Laboratory work #1. GIT\n";
    cout << "Variant #10. Product catalog\n";
    cout << "Author: Имя Фамилия\n\n";

    product* products[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", products, size);
        cout << "***** Каталог товаров *****\n\n";
        for (int i = 0; i < size; i++)
        {
            cout << "Товар........: " << products[i]->name << '\n';
            cout << "Категория....: " << products[i]->category << '\n';
            cout << "Стоимость....: " << fixed << setprecision(2) << products[i]->price << " руб.\n";
            cout << "Количество...: " << products[i]->quantity << " шт.\n";
            cout << "----------------------------------------\n";
        }
        for (int i = 0; i < size; i++)
        {
            delete products[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}