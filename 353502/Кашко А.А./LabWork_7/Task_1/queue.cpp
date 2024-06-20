#include "queue.h"
#include <stdexcept>

// деструктор, освобождает память всех узлов
Queue::~Queue() {
    while (head != nullptr) {
        Node* temp = head; // берём указатель на текущий узел
        head = head->next; // переходим к следующему узлу
        delete temp; // удаление узла, на который брали указатель
    }
}

// метод для добавления нового элемента (узла) в конец очереди
void Queue::enqueue(int value) {
    Node* newNode = new Node(value); // создание нового элемента (узла) с переданным значением
    if (tail == nullptr) { // проверка на пустоту очереди
        head = tail = newNode;
    } else {
        // установка указателей на предыдущий и последующий элемент
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// метод для удаления узла из начала очереди и возвращения его значения
int Queue::dequeue() {
    if (head == nullptr) throw std::runtime_error("Очередь пустая!"); // проверка на пустоту очереди, выброс исключения, если пуста
    int value = head->data; // сохраняем значения первого элемента очереди
    Node* temp = head; // указатель на первый элемент очереди, нужен для освобождения памяти после удаления узла
    head = head->next; // обновляем указатель, это значит, что "старый" первый элемент удалён
    if (head != nullptr) head->prev = nullptr; // проверка, мало ли очередь состояла из одного элемента, обнуляем указатель на предыдущий, так как теперь это первый элемент
    else tail = nullptr; // очередь стала пустой
    delete temp; // удаляем указатель
    return value; // возвращаем значение элемента
}

// метод для проверки, пуста ли очередь
bool Queue::isEmpty() {
    return head == nullptr; // вернёт true, если head равен nullptr -> очередь пуста, в противном случае "false" - очередь имеет хотя бы один элемент
}

// метод для отображения элементов очереди
void Queue::display(QListWidget* listWidget) const {
    listWidget->clear();
    Node* temp = head;
    while (temp != nullptr) {
        listWidget->addItem(QString::number(temp->data));
        temp = temp->next;
    }
}
