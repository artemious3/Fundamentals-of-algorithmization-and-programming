#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H
#include "Expression.h"

class BinaryOperation : public Expression {
 private:
  Expression* left;
  Expression* right;
  char simbol;

 public:
  BinaryOperation(Expression* leftValue, char opSimbol,
                  Expression* rightValue) {
    this->left = leftValue;
    this->right = rightValue;
    this->simbol = opSimbol;
  };

  ~BinaryOperation() override {
    delete left;
    delete right;
  }

  double evaluate() override {
    switch (simbol) {
      case '+':
        return left->evaluate() + right->evaluate();
      case '-':
        return left->evaluate() - right->evaluate();
      case '*':
        return left->evaluate() * right->evaluate();
      case '/':
        return left->evaluate() / right->evaluate();
      default:
        return 0.0;
    };
  };
};

#endif  // BINARYOPERATION_H
