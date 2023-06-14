#include <exception>
#include <iostream>
#include <vector>
template <class T>
void TransformIf(T *begin, T *end, bool (*p)(const T &), void (*f)(T &)) {
  std::size_t size = end - begin;
  std::vector<T> copy(size);
  std::vector<bool> flag(size, false);
  for (std::size_t i = 0; begin + i != end; ++i) {
    try {
      if (p(begin[i])) {
        try {
          copy[i] = begin[i];
          flag[i] = true;
        } catch (...) {
          flag[i] = false;
        }
        f(begin[i]);
      }
    } catch (...) {
      for (std::size_t j = 0; j <= i; ++j) {
        try {
          if (flag[j])
            begin[j] = copy[j];
        } catch (...) {
        }
      }
      throw;
    }
  }
}
