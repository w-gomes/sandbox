#include <fmt/format.h>

#include <algorithm>
#include <array>

template <typename Ty1, typename Ty2>
struct My_Pair {
  Ty1 ty1{};
  Ty2 ty2{};

  constexpr My_Pair() = default;
  constexpr My_Pair(Ty1 t1, Ty2 t2)
    : ty1(std::move(t1))
    , ty2(std::move(t2)) {}

  [[nodiscard]] constexpr auto get_type1() const noexcept { return this->ty1; }
  [[nodiscard]] constexpr auto get_type2() const noexcept { return this->ty2; }
};

template <std::size_t N>
consteval auto get_min_max(const std::array<int, N> &arr) {
  const auto [min, max] = std::ranges::minmax_element(arr);
  return My_Pair(*min, *max);
}

// CNTTP. With CTAD the type of the CNTTP can be deduced. Pretty cool!
template <My_Pair Ty>
consteval auto total() {
  return Ty.get_type1() + Ty.get_type2();
}

template <My_Pair Ty>
constexpr auto format_pair() {
  // TODO: can't be consteval. constexpr may not even be needed here.
  const auto num1 = Ty.get_type1();
  const auto num2 = Ty.get_type2();
  return fmt::format("{} + {} = {}\n", num1, num2, num1 + num2);
}

int main() {
  constexpr auto a = std::array<int, 10>{2, 40, 10, 26, 7, 3, 9, 11, 12, 6};
  const auto t     = total<get_min_max(a)>();
  fmt::print("{}\n", t);

  const auto str = format_pair<get_min_max(a)>();
  fmt::print("{}\n", str);

  return 0;
}
