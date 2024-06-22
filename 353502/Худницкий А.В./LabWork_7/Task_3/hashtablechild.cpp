#include "hashtablechild.h"

template <typename T>
HashTableChild<T>::HashTableChild(int size) : HashTable<T>(size){}

template<typename T>
void HashTableChild<T>::print(QListWidget *listWidget) {
    listWidget->clear();


    QStack<Item<T>> tempStack;
    QString oneStack;

    for(int i = 0; i < this->size; i++) {
        oneStack = QString::number(i) + ". ";

        while (!this->table[i].isEmpty()) {
            Item stackItem = this->table[i].pop();
            tempStack.push(stackItem);
            oneStack += QString::number(stackItem.key) + "(" + stackItem.value + ") ";
        }

        while (!tempStack.isEmpty()) {
            this->table[i].push(tempStack.pop());
        }

        listWidget->addItem(oneStack);
    }
}

template<typename T>
Item<T> HashTable<T>::findMaxKeyItem() const {
    Item<T> maxItem(INT_MIN, T());

    for (int i = 0; i < size; ++i) {
        QStack<Item<T>> tempStack = table[i];
        while (!tempStack.isEmpty()) {
            Item<T> stackItem = tempStack.pop();
            if (stackItem.key > maxItem.key) {
                maxItem = stackItem;
            }
        }
    }

    return maxItem;
}

template<typename T>
void HashTableChild<T>::clear() {
    for(int i = 0; i < this->size; i++) {
        while (!this->table[i].isEmpty()) {
            this->table[i].pop();
        }
    }
}
