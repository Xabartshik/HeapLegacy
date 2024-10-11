// HeapLegacy.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//Сделал Ошлаков Данил, ИВТ-22
#include <iostream>
#include "HeapLegacy.h"
using namespace std;

int main() {
    MaxHeapLegacy<int>::testMaxHeap();
    // Создаём кучу для целых чисел
    MaxHeapLegacy<int> intHeap;

    // Добавляем элементы в кучу
    intHeap.push(10);
    intHeap.push(20);
    intHeap.push(15);
    intHeap.push(12);
    intHeap.push(18);

    // Выводим максимальный элемент
    std::cout << "Максимальный элемент: " << intHeap.top() << std::endl;

    // Удаляем максимальный элемент
    intHeap.pop();

    // Выводим новый максимальный элемент
    std::cout << "Новый максимальный элемент: " << intHeap.top() << std::endl;

    // Создаём кучу для чисел с плавающей запятой
    MaxHeapLegacy<double> doubleHeap;

    // Добавляем элементы в кучу
    doubleHeap.push(10.5);
    doubleHeap.push(20.2);
    doubleHeap.push(15.8);
    doubleHeap.push(12.3);
    doubleHeap.push(18.7);

    // Выводим максимальный элемент

    std::cout << "Максимальный элемент (double): " << doubleHeap.top() << std::endl;

    std::cout << "Максимальный элемент (double): " << doubleHeap[1] << std::endl;

    doubleHeap.printTree();
    cout << endl;
    cout << doubleHeap.capacity() << "   " << doubleHeap.size() << endl;

    doubleHeap.popLast();
    doubleHeap.printTree();
    cout << endl;
    for (double value : doubleHeap) {
        std::cout << value << " ";
    }

    for (auto it = doubleHeap.begin(); it != doubleHeap.end(); ++it) {
        *it *= 10;
    }

    for (double value : doubleHeap) {
        std::cout << value << " ";
    }


    return 0;
}
