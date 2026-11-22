#include <iostream>
#include <iomanip>
#include <windows.h>
#include "product.h"
#include "file_reader.h"
#include "filter.h"
#include "constants.h"

using namespace std;

void output(product* item)
{
    cout << "Товар........: " << item->name << '\n';
    cout << "Категория....: " << item->category << '\n';
    cout << "Стоимость....: " << fixed << setprecision(2) << item->price << " руб.\n";
    cout << "Количество...: " << item->quantity << " шт.\n";
    cout << "----------------------------------------\n";
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    cout << "Лабораторная работа №1. GIT\n";
    cout << "Вариант №10. Каталог товаров\n";
    cout << "Автор: Имя Фамилия\n";
    cout << "Группа: ВАША_ГРУППА\n\n";

    product* products[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", products, size);
        cout << "***** Каталог товаров *****\n\n";
        for (int i = 0; i < size; i++)
        {
            output(products[i]);
        }

        bool (*check_function)(product*) = nullptr;
        cout << "\nВыберите критерий фильтрации:\n";
        cout << "1) Вывести все товары в категории «Промтовары»\n";
        cout << "2) Вывести все товары стоимостью выше 100 рублей\n";
        cout << "Ваш выбор: ";
        int item;
        cin >> item;
        cout << '\n';

        switch (item)
        {
        case 1:
            check_function = check_product_by_category;
            cout << "***** Товары в категории «Промтовары» *****\n\n";
            break;
        case 2:
            check_function = check_product_by_price;
            cout << "***** Товары стоимостью выше 100 рублей *****\n\n";
            break;
        default:
            throw "Некорректный номер пункта меню";
        }

        if (check_function)
        {
            int new_size;
            product** filtered = filter(products, size, check_function, new_size);
            for (int i = 0; i < new_size; i++)
            {
                output(filtered[i]);
            }
            delete[] filtered;
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