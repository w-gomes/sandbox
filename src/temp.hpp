#pragma once

namespace Temp {

template <typename T>
struct foo {
  int x{42};
};

// explicit instantiation declaration
extern template struct foo<int>;
}  // namespace Temp
