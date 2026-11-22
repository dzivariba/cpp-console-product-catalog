#include "pch.h"
#include "CppUnitTest.h"
#include <cstring>
#include "../main-project/product.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
    product* build_product(double price, int quantity, const char* category, const char* name)
    {
        product* item = new product;
        item->price = price;
        item->quantity = quantity;
        strcpy_s(item->category, category);
        strcpy_s(item->name, name);
        return item;
    }

    void delete_products(product* array[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            delete array[i];
        }
    }

    TEST_CLASS(unittestproject)
    {
    public:

        // 1 ожидаем 302.0
        TEST_METHOD(TestMixedCategories)
        {
            product* products[4];
            products[0] = build_product(100.50, 2, "Промтовары", "Порошок");
            products[1] = build_product(50.00, 10, "Бакалея", "Гречка");
            products[2] = build_product(25.25, 4, "Промтовары", "Мыло");
            products[3] = build_product(300.00, 1, "Электроника", "Мышь");

            double result = process(products, 4, "Промтовары");
            delete_products(products, 4);

            Assert::AreEqual(302.0, result, 0.001);
        }

        // 2 ожидаем 136.0
        TEST_METHOD(TestAllMatchingCategory)
        {
            product* products[3];
            products[0] = build_product(10.00, 5, "Бакалея", "Сахар");
            products[1] = build_product(20.50, 2, "Бакалея", "Кофе");
            products[2] = build_product(15.00, 3, "Бакалея", "Чай");

            double result = process(products, 3, "Бакалея");
            delete_products(products, 3);

            Assert::AreEqual(136.0, result, 0.001);
        }

        // 3 ожидаем 901.5
        TEST_METHOD(TestSingleMatchingProduct)
        {
            product* products[3];
            products[0] = build_product(120.00, 3, "Молочные", "Сыр");
            products[1] = build_product(450.75, 2, "Электроника", "Клавиатура");
            products[2] = build_product(80.00, 5, "Промтовары", "Губки");

            double result = process(products, 3, "Электроника");
            delete_products(products, 3);

            Assert::AreEqual(901.5, result, 0.001);
        }
    };
}