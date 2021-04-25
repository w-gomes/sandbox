#include "temp.hpp"

#include <fmt/format.h>
namespace Temp {

// explicitly instantiating struct for the type int
template struct foo<int>;

}  // namespace Temp

int main() {
  Temp::foo<int> x;
  fmt::print("{}\n", x.x);
  return 0;
}
