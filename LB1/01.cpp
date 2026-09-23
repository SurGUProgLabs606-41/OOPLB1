#include <iostream>
#include <cstdlib>
#include <ctime>

// Функция заполнения массива
void fillArray(int (&arr)[10]) {
    for (int i = 0; i < 10; ++i) {
        arr[i] = rand() % 100 + 1;
    }
}

// Функция вывода массива
void printArray(const int (&arr)[10]) {
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// Функция обмена элементов
void swapElements(int (&arr)[10], int index1, int index2) {
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

// Функция умножения на 2
void multiplyByTwo(int (&arr)[10]) {
    for (int& x : arr) {
        x *= 2;
    }
}

/**
 * @brief Точка входа в программу.
 *
 * Демонстрирует работу с массивом целых чисел:
 * инициализирует генератор случайных чисел, заполняет массив,
 * выводит его, меняет местами элементы по заданным индексам
 * и умножает все элементы на 2.
 *
 * @return 0 при успешном завершении программы.
 */

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int myArray[10];
    
    fillArray(myArray);
    std::cout << "Исходный массив: ";
    printArray(myArray);
    
    swapElements(myArray, 2, 7);
    std::cout << "После swap (индексы 2 и 7): ";
    printArray(myArray);
    
    multiplyByTwo(myArray);
    std::cout << "После умножения на 2: ";
    printArray(myArray);
    
    return 0;
}