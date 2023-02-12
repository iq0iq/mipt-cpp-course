#include <exception>
template <class T>
void TransformIf(T *begin, T *end, bool (*p)(const T &), void (*f)(T &)) {
  std::size_t size = end - begin;
  T *copy = new T[size];
  for (std::size_t i = 0; begin + i != end; ++i) {
    try {
      if (p(begin[i])) {
        try {
          copy[i] = begin[i];
        } catch (...) {
        }
        try {
          f(begin[i]);
        } catch (...) {
          throw;
        }
      }
    } catch (...) {
      try {
        for (std::size_t j = 0; j <= i; ++j) {
          begin[j] = copy[j];
        }
      } catch (...) {
        delete[] copy;
        throw;
      }
      delete[] copy;
      throw;
    }
  }
}
