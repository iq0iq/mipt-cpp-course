#include "some_library.hpp"

#include <string>
#include <string_view>

inline void SetValue(SomeLibrary::ValueHolder &valueHolder, int value) {
#pragma pack(push, 1)
  auto name_copy = valueHolder.GetName();
  SomeLibrary::ValueHolder copyValueHolder = valueHolder;
#pragma pack(pop)
  char *struct_ptr = reinterpret_cast<char *>(&valueHolder);
  std::size_t shift = reinterpret_cast<char *>(&copyValueHolder) -
                      reinterpret_cast<char *>(&name_copy);
  struct_ptr += shift;

  int *secret_value_ptr = reinterpret_cast<int *>(struct_ptr);
  *secret_value_ptr = value;
}
