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

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int myArray[10];
    
    fillArray(myArray);
    
    std::cout << "Исходный массив: ";
    printArray(myArray);
    
    return 0;
}