#include <iostream>
struct SafeArray {
    int* data;
    int size;
};

SafeArray createArray(int size) {
    SafeArray arr;
    arr.size = size;
    if (size > 0) {
        arr.data = new int[size]{};
    } else {
        arr.data = nullptr;
    }
    return arr;
}

int& getElement(SafeArray& arr, int index) {
    static int dummy = 0;

    if (index < 0 || index >= arr.size) {
        std::cerr << "Ошибка: индекс " << index
                  << " вне диапазона [0, " << arr.size - 1 << "].\n";
        return dummy;
    }
    return arr.data[index];
}

void printSafe(const SafeArray& arr) {
    std::cout << "Массив (size = " << arr.size << "): ";
    if (arr.size == 0 || arr.data == nullptr) {
        std::cout << "(пусто)\n";
        return;
    }
    for (int i = 0; i < arr.size; ++i) {
        std::cout << arr.data[i] << " ";
    }
    std::cout << "\n";
}

void reSizeArray(SafeArray& arr, int M) {
    int oldSize = arr.size;

    if (M < oldSize) {
        std::cout << "Удалённые элементы: ";
        for (int i = M; i < oldSize; ++i) {
            std::cout << arr.data[i] << " ";
        }
        std::cout << "\n";
    }

    int* newData = nullptr;
    if (M > 0) {
        newData = new int[M]{};
    }

    int copyCount = (M < oldSize) ? M : oldSize;
    for (int i = 0; i < copyCount; ++i) {
        newData[i] = arr.data[i];
    }

    if (M > oldSize) {
        std::cout << "Добавлено " << (M - oldSize)
                  << " новых элементов, инициализированных нулями.\n";
    }


    delete[] arr.data;
    arr.data = newData;
    arr.size = M;
}

int main() {
    SafeArray myArr = createArray(5);

    for (int i = 0; i < myArr.size; ++i) {
        getElement(myArr, i) = (i + 1) * 10;
    }

    std::cout << "Исходный ";
    printSafe(myArr);

    getElement(myArr, 2) = 999;
    std::cout << "После getElement(myArr, 2) = 999: ";
    printSafe(myArr);

    std::cout << "\nПопытка доступа по некорректному индексу:\n";
    getElement(myArr, 100) = 12345;
    std::cout << "После некорректного доступа: ";
    printSafe(myArr);

    getElement(myArr, -1) = -777;
    std::cout << "После отрицательного индекса: ";
    printSafe(myArr);

    std::cout << "\n--- Уменьшение размера с 5 до 3 ---\n";
    reSizeArray(myArr, 3);
    printSafe(myArr);

    std::cout << "\n--- Увеличение размера с 3 до 6 ---\n";
    reSizeArray(myArr, 6);
    printSafe(myArr);

    delete[] myArr.data;
    myArr.data = nullptr;
    myArr.size = 0;

    return 0;
}