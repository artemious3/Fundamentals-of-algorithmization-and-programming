#include <iostream>

//иерархия классов для вычисления арифметических выражений

//базовый абстрактный класс для выражения
class Expression
{
public:
    //виртуальная функция для ввычисления значения выражения
    virtual double evaluate() = 0;
};

//класс для хранения числа
class Number : public Expression
{
private:
    //значение числа
    double num;

public:
    //конструктор, инициализирующий значение числа
    explicit Number(double number) { this->num = number; }

    //функция для вычисления значения числа
    double evaluate() override { return num; }
};

//класс для бинарной операции
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
    //конструктор инициализирующий левое и правое выражение, а также тип операции
    BinaryOperation(Expression *left, char type, Expression *right)
    {
        this->left = left;
        this->right = right;
        this->type = type;
    }

    //деструктор для освобождения памяти
    ~BinaryOperation()
    {
        delete left;
        delete right;
    }

    //функция для ввычисления значения бинарной операции
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
                //ошибка при делении на 0
                std::cout << "Error\n";
            }
            break;
        default:
            //ошибка при некорректном вводе
            std::cout << "What u fucking doing\n";
        }
    }
};

int main()
{
    //создание выражения
    Expression *sube = new BinaryOperation(new Number(1), '*', new Number(2));
    Expression *expr = new BinaryOperation(new Number(3), '+', sube);

    //вывод результата вычисления выражения
    std::cout << expr->evaluate() << "\n";

    //освобождение памяти
    delete expr;
}
