#include <exception>
#include <vector>
template <class T>
void TransformIf(T *begin, T *end, bool (*p)(const T &), void (*f)(T &)) {
  std::size_t size = end - begin;
  std::vector<T> copy(size);
  for (std::size_t i = 0; begin + i != end; ++i) {
    try {
      copy[i] = begin[i];
    } catch (...) {
    }
    try {
      if (p(begin[i])) {
        try {
          f(begin[i]);
        } catch (...) {
          begin[i] = copy[i];
          throw;
        }
      }
    } catch (...) {
      for (std::size_t j = 0; j < i; ++j) {
        begin[j] = copy[j];
      }
      throw;
    }
  }
}
