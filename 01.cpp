#include <iostream>
#include <cstdlib>
#include <ctime>

// Функция заполнения массива
void fillArray(int (&arr)[10]) {
    for (int i = 0; i < 10; ++i) {
        arr[i] = rand() % 100 + 1;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int myArray[10];
    
    fillArray(myArray);
    
    for (int i = 0; i < 10; ++i) {
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}