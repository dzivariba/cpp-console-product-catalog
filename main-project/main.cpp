#include <iostream>
#include <iomanip>
#include <windows.h>
#include "product.h"
#include "file_reader.h"
#include "filter.h"
#include "sort.h"
#include "constants.h"
#include "processing.h"

using namespace std;

typedef int (*compare_func)(product*, product*);
typedef void (*sort_func)(product* [], int, compare_func);

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

        cout << "\nВыберите действие:\n";
        cout << "1) Вывести все товары в категории «Промтовары»\n";
        cout << "2) Вывести все товары стоимостью выше 100 рублей\n";
        cout << "3) Отсортировать товары\n";
        cout << "4) Найти общую стоимость всех товаров в указанной категории\n";
        cout << "Ваш выбор: ";
        int item;
        cin >> item;
        cout << '\n';

        if (item == 1 || item == 2)
        {
            bool (*check_functions[])(product*) = {
                check_product_by_category,
                check_product_by_price
            };

            int new_size;
            product** filtered = filter(products, size, check_functions[item - 1], new_size);
            cout << "***** Результат фильтрации *****\n\n";
            for (int i = 0; i < new_size; i++)
            {
                output(filtered[i]);
            }
            delete[] filtered;
        }
        else if (item == 3)
        {
            sort_func sort_methods[] = {
                selection_sort,
                merge_sort
            };
            compare_func compare_criteria[] = {
                compare_by_quantity_desc,
                compare_by_category_asc_price_desc
            };

            cout << "Выберите метод сортировки:\n";
            cout << "1) Сортировка выбором (Selection sort)\n";
            cout << "2) Сортировка слиянием (Merge sort)\n";
            cout << "Ваш выбор: ";
            int sort_choice;
            cin >> sort_choice;

            cout << "\nВыберите критерий сортировки:\n";
            cout << "1) По убыванию количества товара на складе\n";
            cout << "2) По возрастанию категории, а внутри категории — по убыванию стоимости\n";
            cout << "Ваш выбор: ";
            int criteria_choice;
            cin >> criteria_choice;
            cout << '\n';

            if (sort_choice < 1 || sort_choice > 2 || criteria_choice < 1 || criteria_choice > 2)
            {
                throw "Некорректный выбор метода или критерия сортировки";
            }

            sort_func selected_sort = sort_methods[sort_choice - 1];
            compare_func selected_compare = compare_criteria[criteria_choice - 1];

            selected_sort(products, size, selected_compare);

            cout << "***** Отсортированный каталог товаров *****\n\n";
            for (int i = 0; i < size; i++)
            {
                output(products[i]);
            }
        }
        else if (item == 4)
        {
            char target_category[MAX_STRING_SIZE];
            cout << "Введите категорию товара: ";
            cin >> target_category;
            double total = process(products, size, target_category);
            cout << "\nОбщая стоимость товаров в категории «" << target_category << "»: "
                << fixed << setprecision(2) << total << " руб.\n";
        }
        else
        {
            throw "Некорректный номер пункта меню";
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