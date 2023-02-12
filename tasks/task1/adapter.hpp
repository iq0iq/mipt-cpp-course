#include "some_library.hpp"

#include <string>
#include <string_view>

namespace MyLibrary {
struct ValueHolder {
  std::string name_;
  int value_;
};
} // namespace MyLibrary

inline void SetValue(SomeLibrary::ValueHolder &valueHolder, int value) {
  MyLibrary::ValueHolder copyValueHolder;

  char *struct_ptr = reinterpret_cast<char *>(&valueHolder);
  std::size_t shift = reinterpret_cast<char *>(&copyValueHolder.value_) -
                      reinterpret_cast<char *>(&copyValueHolder);
  struct_ptr += shift;

  int *secret_value_ptr = reinterpret_cast<int *>(struct_ptr);
  *secret_value_ptr = value;
}
