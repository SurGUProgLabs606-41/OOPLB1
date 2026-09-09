#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int myArray[10];
    
    for (int i = 0; i < 10; ++i) {
        myArray[i] = rand() % 100 + 1;
        std::cout << myArray[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}