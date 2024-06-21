#include <iostream>

int64_t AkkermanFunction(int m, int n) {

  if (m == 0) {
    return n + 1;
  } else if (m > 0 && n == 0) {
    return AkkermanFunction(m - 1, 1);
  } else if (m > 0 && n > 0) {
    return AkkermanFunction(m - 1, AkkermanFunction(m, n - 1));
  }
  // Если условия не выполнились, вернем некоторое значение по умолчанию
  return -1;
}

int main(int argc, char* argv[]) {
  int n = 6, m = 2;
  std::cout << AkkermanFunction(m, n) << '\n';
  return 0;
}
