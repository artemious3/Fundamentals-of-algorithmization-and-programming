#include <iostream>

//базовый класс для выражений
class Expression
{
public:
    //виртуальный метод для вычисления значения выражения
    virtual double evaluate() = 0;
};

//класс для числовых значений
class Number : public Expression
{
private:
    double num;

public:
    explicit Number(double number) { this->num = number; }

    //метод для вычисления значения числа
    double evaluate() override { return num; }
};

//класс для бинарных операций
class BinaryOperation : public Expression
{
private:
    //левое выражение
    Expression *left;
    //правое выражение
    Expression *right;
    //тип операции
    char type;

public:
    //конструктор
    BinaryOperation(Expression *left, char type, Expression *right)
    {
        this->left = left;
        this->right = right;
        this->type = type;
    }

    //деструктор
    ~BinaryOperation()
    {
        delete left;
        delete right;
    }

    //метод для вычисления значения бинарного выражения
    double evaluate() override
    {
        switch (type) {
        case '+':
            return (left->evaluate() + right->evaluate());
        case '-':
            return (left->evaluate() - right->evaluate());
        case '*':
            return (left->evaluate() * right->evaluate());
        case '/':
            if (right->evaluate() != 0) {
                return (left->evaluate() / right->evaluate());
            } else {
                std::cout << "Error\n";
            }
            break;
        default:
            std::cout << "What u fucking doing\n";
        }
    }
};

bool check_equals(Expression const *left, Expression const *right)
{
    //сравнивем адреса памяти объектов
    return *(void **) left == *(void **) right;
}

int main()
{
    //создание объектов
    auto *n1 = new Number(1);
    auto *n2 = new Number(2);
    auto *a = new BinaryOperation(n1, '-', n2);
    auto *b = new BinaryOperation(n1, '/', n2);

    //вывод адресов объектов
    std::cout << *(double **) n1 << "\n"
              << *(double **) n2 << "\n"
              << *(double **) a << "\n"
              << *(double **) b << "\n\n";

    //проверка равенства объектов
    std::cout << (check_equals(a, b) ? "Yes\n" : "No\n");
    std::cout << (check_equals(n1, b) ? "Yes\n" : "No\n");
}
