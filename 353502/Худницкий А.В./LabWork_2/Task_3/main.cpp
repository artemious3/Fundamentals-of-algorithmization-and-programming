#include <iostream>
#include <stdexcept>
#include <QtWidgets>

class Expression
{
public:
    virtual ~Expression() {}
    virtual double evaluate() const = 0;
};

class Number : public Expression
{
public:
    Number(double value) : value(value) {}
    virtual ~Number() {}
    virtual double evaluate() const override
    {
        return value;
    }
private:
    double value;
};

class BinaryOperation : public Expression
{
public:
    BinaryOperation(Expression* left, char operation, Expression* right) : left(left), operation(operation), right(right) {}
    virtual ~BinaryOperation() {}
    virtual double evaluate() const override
    {
        double leftValue = left->evaluate();
        double rightValue = right->evaluate();
        switch (operation) {
            case '+': return leftValue + rightValue;
            case '-': return leftValue - rightValue;
            case '*': return leftValue * rightValue;
            case '/':
                if (rightValue == 0) throw std::invalid_argument("Division by zero.");
            return leftValue / rightValue;
        default:
            throw std::invalid_argument("Bro... You have only 4 operations..");
        }
    }
private:
    Expression* left;
    Expression* right;
    char operation;
};

int main()
{
    try
    {
        Expression* ptr1 = new BinaryOperation(new Number(2.5), '*', new Number(8));
        Expression* ptr2 = new BinaryOperation(new Number(6), '+', ptr1);
        std::cout << ptr1->evaluate() << std::endl;
        std::cout << ptr2->evaluate() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }



    return 0;
}
