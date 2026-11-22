#include "file_reader.h"
#include "constants.h"

#include <fstream>

void read(const char* file_name, product * array[], int& size)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        size = 0;
        while (!file.eof() && size < MAX_FILE_ROWS_COUNT)
        {
            product* item = new product;
            if (!(file >> item->price >> item->quantity >> item->category))
            {
                delete item;
                break;
            }
            file.ignore(1); 
            file.getline(item->name, MAX_STRING_SIZE);
            array[size++] = item;
        }
        file.close();
    }
    else
    {
        throw "Ошибка открытия файла";
    }
}