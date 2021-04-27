//#include <fmt/format.h>
#include <fmt/ranges.h>

#include <array>
#include <clocale>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

static void change_locale(const std::string &loc) {
  std::locale::global(std::locale(loc));
  auto s = fmt::format("{:L}\n", 1000000);
  fmt::print(s);
}

struct car {
  int serial;
  std::string brand;
  std::string model;
};

std::ostream &operator<<(std::ostream &out, const car &obj) {
  const int width = 40;
  auto fmt_string = fmt::format(
    "+{1:-^{0}}+\n"
    "|{2:^{0}}|\n"
    "|{3:^{0}}|\n"
    "|{4:^{0}}|\n"
    "+{5:-^{0}}+\n",
    width,
    " Car Information ",
    obj.serial,
    obj.brand,
    obj.model,
    "");
  out << fmt_string;
  return out;
}

int main() {
  static constexpr std::array loc = {
    "pt_BR.UTF-8",
    "en_US.UTF-8",
  };

  for (const auto &l : loc) { change_locale(l); }

  std::vector<int> v = {1, 2, 3};
  fmt::print("{:9}\n", fmt::join(v, ", "));

  fmt::memory_buffer out;
  format_to(out, "My age is {}.\n", 42);
  auto s = fmt::to_string(out);
  fmt::print(s);

  car c{33874831, "honda", "civic"};
  std::cout << c;

  // change_locale(loc[0]);
  std::setlocale(LC_ALL, "");
  std::cout << "cout ";
  std::cout << "Acentuação\n";

  fmt::print("{} ", "fmt");
  fmt::print("{}\n", "Acentuação");

  // usinge ranges support
  auto vec = std::vector<int>{1, 2, 3, 4, 5};
  fmt::print("{}\n", vec);
  fmt::print("{}\n", fmt::join(vec, " "));

  // format_to
  auto out_vec = std::vector<char>{};
  fmt::format_to(std::back_inserter(out_vec), "this is the number, {}\n", 42);
  fmt::print("{}", fmt::join(out_vec, ""));

  fmt::print("{}\n", "•");

  std::cout << "cout: "
            << "Сумма цисел\n";

  fmt::print("fmt: {}\n", "Сумма цисел");
  return 0;
}
