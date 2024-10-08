#pragma once
#include "VectorLegacy.h"
#include <vector>
#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;
template <typename T>
class MaxHeapLegacy {
public:
    // Конструктор по умолчанию
    MaxHeapLegacy() {}


    // Конструктор, принимающий вектор элементов
    MaxHeapLegacy(const VectorLegacy<T>& elements) : data(elements) {
        buildMaxHeap();
    }
    // Оператор присваивания
    MaxHeapLegacy& operator=(const MaxHeapLegacy& other) {
        if (this != &other) {
            data = other.data;
            buildMaxHeap();
        }
        return *this;
    }

    // Добавление элемента в кучу
    void push(const T& value) {
        // Добавляем элемент в конец вектора
        data.push_back(value);

        // Восстанавливаем свойства кучи (max-heap)
        heapifyUp(data.size() - 1);
    }
    //Доступ по индексу
    const T& operator[](size_t index) const {
        if (index > data.size())
        {
            throw out_of_range("Tried to access to index out of array size");
        }
        else
        {
            return data[index];
        }
    }

    //Доступ по индексу
    T& operator[](size_t index) {
        if (index > data.size())
        {
            throw out_of_range("Tried to access empty heap");
        }
        else
        {
            return data[index];
        }
    }
    // Извлечение максимального элемента
    const T& top() {
        // Если куча пуста, возвращаем первый элемент (не определён)
        if (data.empty()) {
            throw out_of_range("Tried to access empty heap");
        }

        // Возвращаем максимальный элемент (корень кучи)
        return data[0];
    }

    // Удаление максимального элемента
    T pop() {
        // Если куча пуста, ничего не делаем
        if (data.empty()) {
            throw out_of_range("Tried to access empty heap");
        }

        // Меняем местами корень и последний элемент
        swap(data[0], data[data.size() - 1]);

        // Удаляем последний элемент
        T result = data.pop_back();

        // Восстанавливаем свойства кучи (max-heap)
        heapifyDown(0);

        return result;
    }

    // Проверка, пуста ли куча
    bool empty() {
        return data.empty();
    }

    // Удаление последнего элемента из кучи
    T popLast() {
        if (data.empty()) {
            throw out_of_range("Tried to access empty heap");
        }

        return data.pop_back(); // Удаляем последний элемент
    }

    //Печать кучи в виде дерева
    void printTree() const {
        printHeap(0, 0);
    }
    //Памяти выделено на кучу
    size_t capacity() const
    {
        return data.capacity();
    }
    //Размер кучи
    size_t size() const
    {
        return data.size();
    }

    bool empty() const
    {
        return data.empty();
    }

    // Поиск элемента в куче. Возврашает размер кучи, если элемент не найден
    size_t search(const T& value) const {
        //return data.seek_sequentional(value);
        return findHelper(value, 0);
    }

    // Удаление элемента по индексу
    void remove(size_t index) {
        if (empty())             
            throw out_of_range("Tried to access empty heap");
        if (index >= data.size())
            throw out_of_range("Index out of range"); // Проверяем, что индекс в пределах кучи

        // Если удаляется последний элемент, просто удаляем его
        if (index == data.size() - 1) {
            data.pop_back();
            return;
        }

        // Заменяем удаляемый элемент последним элементом кучи
        swap(data[index], data[data.size() - 1]);
        data.pop_back();

        // Восстанавливаем свойство максимальной кучи
        size_t parentIndex = (index - 1) / 2;
        if (data[index] > data[parentIndex]) {
            heapifyUp(index);
        }
        else {
            heapifyDown(index);
        }
    }


    class Iterator {
    private:
        size_t current_index;
        const MaxHeapLegacy& heap; // Ссылка на кучу
    public:
        // Конструктор итератора
        Iterator(const MaxHeapLegacy& heap_n, size_t index = 0)
            : heap(heap_n), current_index(index) {}
        //Есть ли следующий элемент
        bool hasNext() const {
            return current_index != data.size();
        }
        //Возвращает значение текущее итератора
        T& operator*() {
            return heap.data[current_index];
        }

        const T& operator*() const {
            return heap.data[current_index];
        }

        //Возвращает значение текущее итератора
        T& data() const {
            return heap.data[current_index];
        }
        // Оператор инкремента
        Iterator& operator++() {
            ++current_index;
            return *this;
        }

        // Оператор постинкремента
        Iterator operator++(int) {
            Iterator temp(*this);
            ++current_index;
            return temp;
        }
        //Переходит к следующему элементу. Если нет следующего элемента, бросает исклоючение
        Iterator& next() {
            if (!hasNext()) {
                throw std::out_of_range("No more elements in the iterator");
            }
            ++current_index;
            return *this;
        }

        // Оператор сравнения на равенство
        bool operator==(const Iterator& other) const {
            return &heap == &other.heap && current_index == other.current_index;
        }

        // Оператор сравнения на неравенство
        bool operator!=(const Iterator& other) const {
            return  &heap != &other.heap || current_index != other.current_index;
        }

        // Сбрасывает итератор
        void reset() {
            current_index = 0;
        }

    };
    //Начальный итератор кучи
    Iterator begin() {
        return Iterator(*this, 0);
    }
    //Конечный итератор кучи
    Iterator end() {
        return Iterator(*this, data.size());
    }


    // Функция тестирования
    static void testMaxHeap() {
        MaxHeapLegacy<int> heap;

        // Тест вставки элементов
        assert(heap.empty());
        heap.push(10);
        heap.push(20);
        heap.push(15);
        assert(heap.size() == 3);
        assert(heap.top() == 20);

        // Тест извлечения максимального элемента
        assert(heap.pop() == 20);
        assert(heap.size() == 2);
        assert(heap.top() == 15);

        // Тест построения кучи из массива
        VectorLegacy<int> arr = { 5, 3, 17, 10, 12, 8, 22 };
        MaxHeapLegacy<int> heapFromArray(arr);
        assert(heapFromArray.top() == 22);

        // Тест перегруженного оператора присваивания
        MaxHeapLegacy<int> heapCopy = heapFromArray;
        assert(heapCopy.top() == 22);



        VectorLegacy<int> initialElements = { 5, 3, 8, 2, 1, 4, 7 };
        MaxHeapLegacy<int> Heap(initialElements);

        assert(Heap.size() == initialElements.size());
        assert(Heap.top() == 8);

        // Тестирование push
        Heap.push(9);
        assert(Heap.top() == 9);
        assert(Heap.size() == initialElements.size() + 1);

        // Тестирование pop
        Heap.pop();
        assert(Heap.top() == 8);
        assert(Heap.size() == initialElements.size());


        // Тестирование remove
        Heap.remove(2);
        assert(Heap[2] == 5);
        assert(Heap.size() == initialElements.size() - 1);

        // Тестирование find
        assert(Heap.search(3) == 1);
        assert(Heap.search(10) == Heap.size());

        // Тестирование empty
        Heap.pop();
        Heap.pop();
        Heap.pop();
        Heap.pop();
        Heap.pop();
        Heap.pop();
        assert(Heap.empty());
        //Пустая куча
        MaxHeapLegacy<int> emptyHeap;
        assert(emptyHeap.empty());
        assert(emptyHeap.size() == 0);
        assert(emptyHeap.search(5) == Heap.size());
        try {

            emptyHeap.top();
        }
        catch (const std::out_of_range& e) {
            // Перехват исключения out_of_range
            std::cerr << "Ошибка перехвачена" << e.what() << endl;
        }
        try {

            emptyHeap.pop();
        }
        catch (const std::out_of_range& e) {
            // Перехват исключения out_of_range
            std::cerr << "Ошибка перехвачена" << e.what() << std::endl;
        }
        try {

            emptyHeap.remove(0);
        }
        catch (const std::out_of_range& e) {
            // Перехват исключения out_of_range
            std::cerr << "Ошибка перехвачена" << e.what() << std::endl;
        }


        std::cout << "All tests passed!" << std::endl;
    }

private:
    // Вектор для хранения элементов кучи
    VectorLegacy<T> data;

    // Восстановление свойств кучи (max-heap) снизу-вверх
    void heapifyUp(int index) {
        // Пока индекс элемента не равен 0 (корень)
        // и значение элемента больше значения родителя
        while (index > 0 && data[(index - 1) / 2] < data[index]) {
            // Меняем местами элемент и его родителя
            swap(data[index], data[(index - 1) / 2]);

            // Переходим к родителю
            index = (index - 1) / 2;
        }
    }

    // Восстановление свойств кучи (max-heap) сверху-вниз
    void heapifyDown(int index) {
        int size = data.size();

        // Пока есть левый ребёнок
        while (2 * index + 1 < size) {
            int largestIndex = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;

            // Находим индекс наибольшего из трёх элементов: текущего, левого и правого ребёнка
            if (data[leftChild] > data[largestIndex]) {
                largestIndex = leftChild;
            }
            if (rightChild < size && data[rightChild] > data[largestIndex]) {
                largestIndex = rightChild;
            }

            // Если текущий элемент уже наибольший, то выходим из цикла
            if (largestIndex == index) {
                break;
            }

            // Меняем местами текущий элемент и наибольший из его детей
            swap(data[index], data[largestIndex]);

            // Переходим к наибольшему ребёнку
            index = largestIndex;
        }
    }
    //Вспомогательные функции для определения потомков:
    size_t parent(size_t i) const {
        return (i - 1) / 2;
    }

    size_t left(size_t i) const {
        return 2 * i + 1;
    }

    size_t right(size_t i) const {
        return 2 * i + 2;
    }

    //Печать элемента кучи по его индексу и уровню
    void printHeap(size_t index, size_t level) const {
        if (index >= data.size()) {
            return;
        }

        printHeap(right(index), level + 1);

        for (int i = 0; i < level; i++) {
            std::cout << "    ";
        }
        std::cout << data[index] << std::endl;

        printHeap(left(index), level + 1);
    }
    //Построить кучу из вектора
    void buildMaxHeap() {
        for (int i = data.size() / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }

    // Вспомогательная функция для поиска элемента
    size_t findHelper(const T& value, size_t index) const {
        // Проверяем, что индекс находится в пределах кучи
        if (index >= data.size()) {
            return data.size(); // Возвращаем размер кучи, чтобы обозначить, что элемент не найден
        }

        // Если элемент найден, возвращаем его индекс
        if (data[index] == value) {
            return index;
        }

        // Рекурсивно ищем элемент в левом и правом поддеревьях
        size_t leftIndex = 2 * index + 1;
        size_t rightIndex = 2 * index + 2;
        size_t leftResult = findHelper(value, leftIndex);
        size_t rightResult = findHelper(value, rightIndex);

        // Возвращаем наименьший найденный индекс
        if (leftResult < data.size()) {
            return leftResult;
        }
        else if (rightResult < data.size()) {
            return rightResult;
        }
        else {
            return data.size(); // Элемент не найден
        }
    }




};
