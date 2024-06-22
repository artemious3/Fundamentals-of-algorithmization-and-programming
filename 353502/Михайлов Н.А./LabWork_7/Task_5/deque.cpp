#include "deque.h"
#include <QDebug>
#include <cstdlib>
#include <stdexcept>

template<typename T>
Deque<T>::Deque()
{
    nodes = (Node<T>*)(malloc(sizeof(Node<T>) * 1));
    nodes[0].data = (T*)(malloc(sizeof(T) * 4));

    _capacity = 4;
    _size = 0;

    front = &(nodes[0].data[0]);
    back = &(nodes[0].data[0]);
}

template<typename T>
void Deque<T>::push_back(const T &Item)
{
    *back = Item;
    _size++;

    if(_size == _capacity)
    {
        _capacity += 4;

        nodes = (Node<T>*)(realloc(nodes, sizeof(Node<T>) * (_capacity / 4)));

        nodes[_capacity / 4 - 1].data = (T*)(malloc(sizeof(T) * 4));


        back = &(nodes[_capacity / 4 - 1].data[0]);


    }
    else back++;
}

template<typename T>
void Deque<T>::push_front(const T &Item)
{
    _size++;

    if(front == &nodes[0].data[0])
    {
        _capacity += 4;
        nodes = (Node<T>*)(realloc(nodes, sizeof(Node<T>) * (_capacity / 4)));

        for(int i = _capacity / 4 - 1; i > 0; i--)
        {
            nodes[i] = nodes[i - 1];
        }

        nodes[0].data = (T*)(malloc(sizeof(T) * 4));

        front = &(nodes[0].data[3]);
        *front = Item;
    }
    else
    {
        front--;
        *front = Item;
    }
}

template<typename T>
void Deque<T>::pop_back()
{
    if(_size == 0) throw std::out_of_range("Deque is empty");

    if(back == &(nodes[_capacity / 4 - 1].data[0]))
    {
        _size--;
        back = &(nodes[_size / 4 - 1].data[4]);

        _capacity -= 4;
    }
    else
    {
        T* tmp = --back;
        _size--;
    }
}

template<typename T>
void Deque<T>::pop_front()
{
    if(_size == 0) throw std::out_of_range("Deque is empty");


    _size--;
    if(front == &(nodes[0].data[3]))
    {

        for(int i = 0; i < _capacity / 4 - 1; i++)
        {
            nodes[i] = nodes[i + 1];
        }

        _capacity -= 4;

        nodes = (Node<T>*)(realloc(nodes, sizeof(Node<T>) * (_capacity / 4)));

        front = &(nodes[0].data[0]);
    }
    else
    {
        front++;
    }
}

template<typename T>
int Deque<T>::size()
{
    return _size;
}

template<typename T>
bool Deque<T>::empty()
{
    return (_size == 0);
}

template<typename T>
void Deque<T>::clear()
{
    free(nodes);

    nodes = (Node<T>*)(malloc(sizeof(Node<T>) * 1));
    nodes[0].data = (T*)(malloc(sizeof(T) * 4));

    _capacity = 4;
    _size = 0;

    front = &(nodes[0].data[0]);
    back = &(nodes[0].data[0]);
}

template<typename T>
T &Deque<T>::operator[](int index)
{
    if(index >= _size) throw std::out_of_range("Out of range!");

    int step;

    //find step for index
    for(int i = 0; i < 4; i++)
    {
        if(front == &(nodes[0].data[i]))
        {
            step = 4 - i;
            break;
        }
    }

    return nodes[(index + (4 - step))/ 4].data[(index + (4 - step)) % 4];
}
