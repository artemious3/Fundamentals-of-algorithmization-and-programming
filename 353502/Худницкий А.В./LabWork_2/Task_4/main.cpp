#include <iostream>

class Expression {
public:
    virtual ~Expression() {}
    virtual int getType() const = 0;
};

class Number : public Expression {
public:
    int getType() const override { return 1; }
};

class BinaryOperation : public Expression {
public:
    int getType() const override { return 2; }
};

bool check_equals(const Expression* left, const Expression* right) {
    return left->getType() == right->getType();
}

int main() {
    Expression* ptr1 = new Number();
    Expression* ptr2 = new BinaryOperation();
    Expression* ptr3 = new BinaryOperation();

    std::cout << "Equal types: " << check_equals(ptr1, ptr2) << std::endl;
    std::cout << "Equal types: " << check_equals(ptr2, ptr3) << std::endl;

    delete ptr1;
    delete ptr2;
    delete ptr3;

    return 0;
}
