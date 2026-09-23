#include <iostream>

void process(int*& arr, int& size) {
    int negIndex = -1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] < 0) {
            negIndex = i;
            break;
        }
    }

    if (negIndex == -1) {
        std::cout << "Отрицательных элементов не найдено. Массив не изменён.\n";
        return;
    }

    int newSize = negIndex;
    int* newArr = new int[newSize]{};

    for (int i = 0; i < newSize; ++i) {
        newArr[i] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    size = newSize;

    std::cout << "Первый отрицательный элемент найден по индексу " << negIndex
              << ". Массив усечён до " << newSize << " элементов.\n";
}

int main() {
    int N;
    std::cout << "Введите размер массива N: ";
    std::cin >> N;

    if (N <= 0) {
        std::cout << "Размер должен быть положительным.\n";
        return 0;
    }

    int* arr = new int[N]{};

    std::cout << "Введите " << N << " элементов массива:\n";
    for (int i = 0; i < N; ++i) {
        std::cin >> arr[i];
    }

    std::cout << "Исходный массив: ";
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    int size = N;
    process(arr, size);

    if (size == 0) {
        std::cout << "Результат: массив пуст.\n";
    } else {
        std::cout << "Результат: ";
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }

    delete[] arr;
    arr = nullptr;

    std::cout << "\nДемонстрация безопасного поведения после delete:\n";
    if (arr == nullptr) {
        std::cout << "Указатель arr == nullptr. Разыменование пропущено "
                     "(защита от Segmentation Fault).\n";
    } else {
        std::cout << "Значение по указателю: " << *arr << "\n";
    }

    return 0;
}