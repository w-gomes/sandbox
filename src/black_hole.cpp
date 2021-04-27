#include <fmt/ranges.h>

#include <vector>

auto main() -> int {
  auto number                   = 1498;
  const char* stringfied_number = "1498";

  const auto div = 10;
  const auto sub = '0';
  int value      = 1498;
  auto vec       = std::vector<int>{};
  auto vec_char  = std::vector<unsigned char>{};
  while (value > 0) {
    auto new_value = value / div;
    vec.push_back(value % div);
    value = new_value;
  }

  fmt::print("{}\n", vec);

  while (!vec.empty()) {
    auto c = vec.back();
    vec.pop_back();
    vec_char.push_back(static_cast<unsigned char>(c + sub));
  }

  fmt::print("{}\n", vec_char);

  for (auto c : vec_char) { fmt::print("{}", static_cast<short>(c)); }
  fmt::print("\n");

  fmt::print("{} {}\n", number, stringfied_number);

  fmt::print("{} {}\n", 10, 4.2F);

  return 0;
}
