#ifndef QUEUE_H
#define QUEUE_H

#include <QListWidget>

// класс для представления элемента в двухсвязном списке
class Node {
public:
    int data; // переменная, которая хранит значение элемента (узла)
    Node* next; // указатель на следующий элемент в списке
    Node* prev; // указатель на предыдущий элемент в списке

    Node(int value) : data(value), next(nullptr), prev(nullptr) {} // конструктор узла (для инициализации)
};

// класс для представления двухсвязной очереди
class Queue {
private:
    Node* head; // указатель на первый элемент очереди
    Node* tail; // указатель на последний элемент очереди

public:
    Queue() : head(nullptr), tail(nullptr) {} // конструктор
    ~Queue(); // деструктор

    void enqueue(int value); // метод для добавления нового элемента (узла) в конец очереди
    int dequeue(); // метод для удаления узла из начала очереди и возвращения его значения
    bool isEmpty(); // метод для проверки, пуста ли очередь
    void display(QListWidget* listWidget) const; // метод для отображения элементов очереди
};

#endif // QUEUE_H
