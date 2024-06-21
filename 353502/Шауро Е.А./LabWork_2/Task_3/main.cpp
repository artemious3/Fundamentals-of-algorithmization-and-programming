#include "BinaryOperation.h"
#include "Expression.h"
#include "Number.h"

#include <iostream>

bool check_equals(Expression const* left, Expression const* right) {
  return (*reinterpret_cast<void**>(const_cast<Expression*>(left)) ==
         *reinterpret_cast<void**>(const_cast<Expression*>(right)));
}

class Base{
public:
    virtual void func(){
        std::cout << "function";
    }
};

int main(int argc, char* argv[]) {
  Number* first = new Number(3);
  Number* second = new Number(0);
  Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
  Expression* expr = new BinaryOperation(new Number(3), '+', sube);

  std::cout << expr->evaluate() << "\n";
  std::cout << check_equals(first, second) << '\n'
            << check_equals(first, sube) << '\n';

  Base obj;
  void (Base::*func_ptr)() = &Base::func;


  delete expr;
    delete sube;
    delete first;
    delete second;
}
