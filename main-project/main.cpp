#include <iostream>
#include <iomanip>
#include "product.h"
#include "file_reader.h"
#include "constants.h"
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    cout << "Лабораторная работа 8 GIT\n";
    cout << "Вариант 10 \n";
    cout << "Автор: Пашкевич Иван\n";
    cout << "Группа: 26Пинж\n";

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