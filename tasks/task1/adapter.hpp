#include "some_library.hpp"

#include <string>
#include <string_view>

inline void SetValue(SomeLibrary::ValueHolder &valueHolder, int value) {
  std::string s[2];
  char *struct_ptr = reinterpret_cast<char *>(&valueHolder);
  std::size_t shift =
      reinterpret_cast<char *>(&s[1]) - reinterpret_cast<char *>(&s[0]);
  struct_ptr += shift;

  int *secret_value_ptr = reinterpret_cast<int *>(struct_ptr);
  *secret_value_ptr = value;
}
