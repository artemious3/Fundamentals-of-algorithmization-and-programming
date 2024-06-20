#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdexcept>
#include <QLabel>
#include <utility>
#include <QDebug>

template<typename KeyT, typename ValT> class RedBlackTree
{
protected:
    enum node_colors { RED, BLACK };

    struct node {
        node *parent, *left, *right;
        enum node_colors color;
        KeyT key;
        ValT val;

        node(node *p, node *l, node *r, enum node_colors c, KeyT k, ValT v)
            : parent(p), left(l), right(r), color(c), key(std::move(k)), val(std::move(v)) {}
    };

    node *findNode(const KeyT &key) {
        node *cur = root;
        while (cur != nullptr) {
            if (key == cur->key)
                return cur;
            if (key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }

        return nullptr;
    }

    // метод для получения указателя на дедушку
    node *grandparent(struct node *n) {
        if ((n != nullptr) && (n->parent != nullptr)) // Если узел n и его родитель не равны nullptr.
            return n->parent->parent; // Возвращаем указатель на дедушку узла n.
        else
            return nullptr; // Если узел n или его родитель равны nullptr, возвращаем nullptr.
    }

    // метод для получения дяди
    node *uncle(struct node *n)
    {
        struct node *g = grandparent(n); // Получаем указатель на дедушку узла n.
        if (g == nullptr) // Если дедушка равен nullptr.
            return nullptr; // Возвращаем nullptr.
        if (n->parent == g->left) // Если родитель узла n - левый сын дедушки.
            return g->right; // Возвращаем правого сына дедушки (дядю).
        else // Если родитель узла n - правый сын дедушки.
            return g->left; // Возвращаем левого сына дедушки (дядю).
    }

    // левый поворот
    void rotateLeft(struct node *n)
    {
        struct node *pivot = n->right; // получение правого сына узла n, который будет пивотом

        // изменение указателей между пивотом, текущим узлом и его родителем
        pivot->parent = n->parent;
        if (n->parent != nullptr) {
            if (n->parent->left == n)
                n->parent->left = pivot;
            else
                n->parent->right = pivot;
        }

        // изменение указателей между пивотом, текущим узлом и их детьми
        n->right = pivot->left;
        if (pivot->left != nullptr)
            pivot->left->parent = n;

        // изменение указателей между пивотом и текущим узлом
        n->parent = pivot;
        pivot->left = n;
    }

    // правый поворот
    void rotateRight(struct node *n)
    {
        struct node *pivot = n->left; // получение левого сына узла n, который будет пивотом

        // изменение указателей между пивотом, текущим узлом и его родителем
        pivot->parent = n->parent;
        if (n->parent != nullptr) {
            if (n->parent->left == n)
                n->parent->left = pivot;
            else
                n->parent->right = pivot;
        }

        // изменение указателей между пивотом, текущим узлом и их детьми
        n->left = pivot->right;
        if (pivot->right != nullptr)
            pivot->right->parent = n;

        // изменение указателей между пивотом и текущим узлом
        n->parent = pivot;
        pivot->right = n;
    }

    // вставка (если n - новый узел - корень, перекрашиваем в чёрный, если нет то переходим к вставке №2)
    void insert_case1(struct node *n)
    {
        if (n->parent == nullptr) // Если у узла n нет родителя (n - корневой узел).
            n->color = BLACK; // Устанавливаем цвет узла n в BLACK.
        else // Если у узла n есть родитель.
            insert_case2(n); // Переходим ко второму случаю вставки.
    }

    // вставка (если родитель n узла чёрный, то ничего не делаем, если красный то вставка №3)
    void insert_case2(struct node *n)
    {
        if (n->parent->color == BLACK) // Если родитель узла n черный.
            return; // Вставка завершена, дерево остается корректным.
        else // Если родитель узла n красный.
            insert_case3(n); // Переходим к третьему случаю вставки.
    }

    // вставка (если дядя n узла существует и он красный -> родитедь и дядя черные, дед красный, вызываем вставку №1 для деда, если дядя черный или отсутствует вызываем вставку №4)
    void insert_case3(struct node *n)
    {
        struct node *u = uncle(n), *g; // Получаем указатель на дядю и объявляем указатель на дедушку.

        if ((u != nullptr) && (u->color == RED)) { // Если дядя существует и красный.
            n->parent->color = BLACK; // Меняем цвет родителя узла n на черный.
            u->color = BLACK; // Меняем цвет дяди на черный.
            g = grandparent(n); // Получаем указатель на дедушку.
            g->color = RED; // Меняем цвет дедушки на красный.
            insert_case1(g); // Рекурсивно применяем первый случай для дедушки.
        } else { // Если дядя не существует или черный.
            insert_case4(n); // Переходим к четвертому случаю вставки.
        }
    }

    // вставка (если n узел - правый ребёнок, а его родитель - левый ребёнок дедушки, выполняем левый поворот отн-но родителя, аналогично правый поворот, вызываем вставку №5)
    void insert_case4(struct node *n)
    {
        struct node *g = grandparent(n); // Получаем указатель на дедушку.

        if ((n == n->parent->right) && (n->parent == g->left)) { // Если узел n является правым сыном, а его родитель - левым сыном дедушки.
            rotateLeft(n->parent); // Выполняем левый поворот вокруг родителя узла n.
            n = n->left; // Перемещаем указатель n на левого сына.
        } else if ((n == n->parent->left) && (n->parent == g->right)) { // Если узел n является левым сыном, а его родитель - правым сыном дедушки.
            rotateRight(n->parent); // Выполняем правый поворот вокруг родителя узла n.
            n = n->right; // Перемещаем указатель n на правого сына.
        }
        insert_case5(n); // Переходим к пятому случаю вставки.
    }

    // вставка (родитель n узла становится чёрным, дед красным, если n узел и его родитель - левые дети, тогда выполняем правый поворот, иначе левый поворот)
    void insert_case5(struct node *n)
    {
        struct node *g = grandparent(n); // Получаем указатель на дедушку.

        n->parent->color = BLACK; // Меняем цвет родителя узла n на черный.
        g->color = RED; // Меняем цвет дедушки на красный.
        if ((n == n->parent->left) && (n->parent == g->left)) { // Если узел n является левым сыном, а его родитель - левым сыном дедушки.
            rotateRight(g); // Выполняем правый поворот вокруг дедушки.
        } else { // В противном случае.
            rotateLeft(g); // Выполняем левый поворот вокруг дедушки.
        }
    }

    void clear(node *node) {
        if (node == nullptr) // Если узел равен nullptr, завершаем выполнение.
            return; // Возвращаемся из функции.

        clear(node->left); // Рекурсивно очищаем левое поддерево.
        clear(node->right); // Рекурсивно очищаем правое поддерево.
        delete node; // Удаляем текущий узел.
    }

    // метод для получения размера дерева, где узел n является корнем
    int calcSize(node* n) {
        if (n == nullptr) return 0; // Если узел равен nullptr, возвращаем 0.
        return 1 + calcSize(n->left) + calcSize(n->right); // Возвращаем 1 (текущий узел) + размер левого поддерева + размер правого поддерева.
    }

public:
    RedBlackTree() : root(nullptr) {}; // Конструктор инициализирует дерево с корнем, равным nullptr.

    void printTree(QLabel* label) {
        RedBlackTree<int, int>* tree = new RedBlackTree<int, int>();

        tree->insert(55, 55);
        tree->insert(12, 12);
        tree->insert(69, 69);
        tree->insert(4, 4);
        tree->insert(29, 29);
        tree->insert(64, 64);
        tree->insert(93, 93);
        QString str = "";
        for (auto i : tree){
            str += QString::number(i->val);
            str += " ";
        }
        label->setText(str);
    }

    node* insert(KeyT key, ValT val) {
        if (root == nullptr) { // Если корень дерева равен nullptr.
            root = new node(nullptr, nullptr, nullptr, BLACK, key, val); // Создаем новый корневой узел с переданным ключом и значением, цветом BLACK.

            return root; // Возвращаем указатель на новый корень.
        }
        return insert(key, val, root); // Иначе вызываем перегруженную функцию insert для вставки начиная с корня.
    }

    node* insert(KeyT key, ValT val, node* n) {
        if (key == n->key) { // Если ключ уже существует в дереве.
            return n; // Возвращаем указатель на существующий узел.
        }

        if (key > n->key) { // Если ключ больше ключа текущего узла.
            if (n->right) return insert(key, val, n->right); // Если правый сын существует, продолжаем вставку в правом поддереве.
            else {
                n->right = new node(n, nullptr, nullptr, RED, key, val); // Иначе создаем новый правый узел с цветом RED.
                insert_case1(n->right); // Применяем первый случай вставки для нового узла.
                return n->right; // Возвращаем указатель на новый узел.
            }
        } else { // Если ключ меньше или равен ключу текущего узла.
            if (n->left) return insert(key, val, n->left); // Если левый сын существует, продолжаем вставку в левом поддереве.
            else {
                n->left = new node(n, nullptr, nullptr, RED, key, val); // Иначе создаем новый левый узел с цветом RED.
                insert_case1(n->left); // Применяем первый случай вставки для нового узла.
                return n->left; // Возвращаем указатель на новый узел.
            }
        }
    }

    // метод для проверки наличия узла
    bool contains(KeyT&& key) {
        return findNode(key) != nullptr; // Возвращаем true, если узел с таким ключом найден, иначе false.
    }

    void erase(const KeyT &key) {
        node *n = findNode(key); // Ищем узел с данным ключом.
        if (n == nullptr) // Если узел не найден.
            return; // Завершаем выполнение функции.

        if (n->left != nullptr && n->right != nullptr) { // Если у узла есть оба ребенка.
            node *toRepl = n->right; // Находим наименьший узел в правом поддереве.
            while (toRepl->left != nullptr)
                toRepl = toRepl->left;

            n->key = std::move(toRepl->key); // Перемещаем ключ и значение из toRepl в n.
            n->val = std::move(toRepl->val);

            n = toRepl; // Переключаемся на узел toRepl для дальнейшего удаления.
        }

        if (n->left == nullptr && n->right != nullptr) { // Если у узла нет левого ребенка, но есть правый.
            n->right->color = RED; // Устанавливаем цвет правого ребенка в RED.
            replaceWith(n, n->right); // Заменяем узел n на его правого ребенка.
            delete n; // Удаляем узел n.
            return; // Завершаем выполнение функции.
        }

        if (n->right == nullptr && n->left != nullptr) { // Если у узла нет правого ребенка, но есть левый.
            n->left->color = RED; // Устанавливаем цвет левого ребенка в RED.
            replaceWith(n, n->left); // Заменяем узел n на его левого ребенка.
            delete n; // Удаляем узел n.
            return; // Завершаем выполнение функции.
        }

        if (n == root) { // Если узел n является корнем.
            delete root; // Удаляем корень.
            root = nullptr; // Устанавливаем корень в nullptr.
            return; // Завершаем выполнение функции.
        }

        if (n->color == BLACK) { // Если узел n черный.
            replaceWith(n, nullptr); // Заменяем узел n на nullptr.
            delete n; // Удаляем узел n.
            return; // Завершаем выполнение функции.
        }

        node *nodeToClean = n; // Сохраняем указатель на узел для дальнейшего удаления.

        if (n->left != nullptr || n->right != nullptr) { // Если у узла есть дети (что недопустимо для данного случая).
            throw new std::logic_error("Invalid attempt to remove"); // Генерируем исключение.
        }

        while (n->parent != nullptr) { // Пока у узла есть родитель.
            {
                node *parent = n->parent; // Получаем родителя.
                bool atLeft = parent->left == n; // Проверяем, является ли узел левым ребенком.
                node *sibling = atLeft ? parent->right : parent->left; // Находим сиблинга.
                if (sibling->color == BLACK) { // Если сиблин черный.
                    parent->color = BLACK; // Устанавливаем цвет родителя в черный.
                    sibling->color = RED; // Устанавливаем цвет сиблинга в красный.

                    if (atLeft)
                        rotateLeft(parent); // Выполняем левый поворот вокруг родителя, если узел левый ребенок.
                    else
                        rotateRight(parent); // Выполняем правый поворот вокруг родителя, если узел правый ребенок.
                }
            }

            {
                node *parent = n->parent; // Получаем родителя.
                bool atLeft = parent->left == n; // Проверяем, является ли узел левым ребенком.
                node *sibling = atLeft ? parent->right : parent->left; // Находим сиблинга.

                bool blackSiblings =
                    (sibling->color == RED) &&
                    (sibling->left == nullptr || sibling->left->color == RED) &&
                    (sibling->right == nullptr || sibling->right->color == RED); // Проверяем условия черных сиблингов.

                if ((parent->color == RED) && blackSiblings) { // Если родитель красный и сиблинги черные.
                    sibling->color = BLACK; // Устанавливаем цвет сиблинга в черный.
                    n = n->parent; // Поднимаемся на уровень выше.
                    continue; // Переходим к следующей итерации.
                }

                if ((parent->color == BLACK) && blackSiblings) { // Если родитель черный и сиблинги черные.
                    sibling->color = BLACK; // Устанавливаем цвет сиблинга в черный.
                    parent->color = RED; // Устанавливаем цвет родителя в красный.
                    break; // Прерываем цикл.
                }
            }

            {
                node *parent = n->parent; // Получаем родителя.
                bool atLeft = parent->left == n; // Проверяем, является ли узел левым ребенком.
                node *sibling = atLeft ? parent->right : parent->left; // Находим сиблинга.

                if (sibling->color == RED) { // Если сиблин красный.
                    if (atLeft &&
                        (sibling->right == nullptr || sibling->right->color == RED) &&
                        (sibling->left && sibling->left->color == BLACK)) { // Проверяем условия для правого поворота.
                        sibling->color = BLACK; // Устанавливаем цвет сиблинга в черный.
                        sibling->left->color = RED; // Устанавливаем цвет левого ребенка сиблинга в красный.
                        rotateRight(sibling); // Выполняем правый поворот вокруг сиблинга.
                    } else if (!atLeft &&
                               (sibling->left == nullptr || sibling->left->color == RED) &&
                               (sibling->right && sibling->right->color == BLACK)) { // Проверяем условия для левого поворота.
                        sibling->color = BLACK; // Устанавливаем цвет сиблинга в черный.
                        sibling->right->color = RED; // Устанавливаем цвет правого ребенка сиблинга в красный.
                        rotateLeft(sibling); // Выполняем левый поворот вокруг сиблинга.
                    }
                }
            }

            {
                node *parent = n->parent; // Получаем родителя.
                bool atLeft = parent->left == n; // Проверяем, является ли узел левым ребенком.
                node *sibling = atLeft ? parent->right : parent->left; // Находим сиблинга.

                parent = n->parent; // Обновляем указатель на родителя.
                atLeft = parent->left == n; // Проверяем, является ли узел левым ребенком.
                sibling = atLeft ? parent->right : parent->left; // Находим сиблинга.
                sibling->color = parent->color; // Устанавливаем цвет сиблинга в цвет родителя.
                parent->color = RED; // Устанавливаем цвет родителя в красный.

                if (atLeft) {
                    if (sibling->right)
                        sibling->right->color = RED; // Устанавливаем цвет правого ребенка сиблинга в красный, если узел левый ребенок.
                    rotateLeft(parent); // Выполняем левый поворот вокруг родителя.
                } else {
                    if (sibling->left)
                        sibling->left->color = RED; // Устанавливаем цвет левого ребенка сиблинга в красный, если узел правый ребенок.
                    rotateRight(parent); // Выполняем правый поворот вокруг родителя.
                }
            }

            break; // Прерываем цикл.
        }

        {
            node *parent = nodeToClean->parent; // Получаем родителя узла для удаления.
            if (parent) { // Если родитель существует.
                if (parent->left == nodeToClean) {
                    parent->left = nullptr; // Удаляем ссылку на узел из левого ребенка родителя.
                } else {
                    parent->right = nullptr; // Удаляем ссылку на узел из правого ребенка родителя.
                }
            }
        }
        delete nodeToClean; // Удаляем узел.
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    node *root;

    size_t size() {
        return calcSize(root);
    }

public:
    class Iterator {
    protected:
        friend class RedBlackTree<KeyT, ValT>; // Декларация дружественного класса RedBlackTree, чтобы он имел доступ к защищенным членам Iterator

        Iterator(node *root) : cur(root) { // Конструктор итератора, инициализирующий текущий узел корнем дерева.
            if(!cur) return; // Если корень равен nullptr, просто возвращаемся.
            while (cur->left != nullptr) // Перемещаемся в самый левый узел (наименьший элемент).
                cur = cur->left;
        }

    public:
        node *operator->() { return cur; } // Оператор разыменования указателя, возвращает текущий узел.

        node &operator*() { return *cur; } // Оператор разыменования, возвращает ссылку на текущий узел.

        Iterator &operator++() { // Оператор инкремента, перемещающий итератор к следующему узлу.
            if (!cur) // Если текущий узел равен nullptr.
                return *this; // Возвращаем итератор.

            if (cur->right != nullptr) { // Если у текущего узла есть правый ребенок.
                cur = cur->right; // Переходим к правому ребенку.
                while (cur->left != nullptr) // Идем в самый левый узел в правом поддереве.
                    cur = cur->left;
            } else { // Если у текущего узла нет правого ребенка.
                while (cur->parent != nullptr && cur->parent->right == cur) { // Поднимаемся вверх по дереву, пока не найдем узел, который является левым ребенком своего родителя.
                    cur = cur->parent;
                }
                cur = cur->parent; // Переходим к родителю.
            }

            return *this; // Возвращаем итератор.
        }

        bool operator==(const Iterator &other) { // Оператор сравнения на равенство.
            return cur == other.cur; // Сравнивает текущие узлы.
        }

        bool operator!=(const Iterator &other) { return !(*this == other); } // Оператор сравнения на неравенство.

    protected:
        node *cur; // Указатель на текущий узел.
    };

    Iterator begin() { return Iterator(root); } // Возвращает итератор на первый (наименьший) элемент дерева.
    Iterator end() { return Iterator(nullptr); } // Возвращает итератор на nullptr (конец дерева).
};

#endif // REDBLACKTREE_H
