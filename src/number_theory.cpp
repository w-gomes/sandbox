#include <fmt/ranges.h>

#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>

constexpr auto mod = 1000000007ULL;

using u64 = unsigned long long;
using i64 = long long;

struct Euclid_Result {
  i64 x{};
  i64 y{};
  i64 gcd{};
};

auto mod_exp(u64 base, u64 exp) {
  if (exp == 0) {
    return 1ULL;
  } else if (exp % 2 == 0) {
    return mod_exp((base * base) % mod, exp / 2);
  } else {
    return base * mod_exp((base * base) % mod, (exp - 1) / 2) % mod;
  }
}

auto mod_exp2(u64 base, u64 exp, u64 M) {
  if (exp == 0) {
    return 1ULL;
  } else if (exp % 2 == 0) {
    return mod_exp2((base * base) % M, exp / 2, M);
  } else {
    return base * mod_exp2((base * base) % M, (exp - 1) / 2, M) % M;
  }
}

auto euclid(u64 num_one, u64 num_two) {
  if (num_two == 0) {
    return num_one;
  } else {
    return euclid(num_two, num_one % num_two);
  }
}

auto extended_euclid(i64 a, i64 b) {
  if (b == 0) {
    return Euclid_Result{1, 0, a};
  } else {
    auto euclid = extended_euclid(b, a % b);
    auto temp   = euclid.x;
    euclid.x    = euclid.y;
    euclid.y    = temp - (a / b) * euclid.y;
    return Euclid_Result{euclid.x, euclid.y, euclid.gcd};
  }
}

auto mod_inverse(i64 a, i64 M) {
  const auto euclid = extended_euclid(a, M);
  return ((euclid.x % M) + M) % M;
}

// this can only be used if M is prime
auto mod_inverse2(u64 a, u64 M) { return mod_exp2(a, M - 2, M); }

// O(sqrt(N))
auto is_prime(u64 n) {
  for (auto i = 2ULL; i * i <= n; ++i) {
    if (n % i == 0) { return false; }
  }
  return true;
}

auto sieve(u64 N) {
  auto is_prime = std::vector<bool>(N + 1, true);
  is_prime[0]   = false;
  is_prime[1]   = false;

  // loop from 2 to sqrt of N
  for (auto i = 2ULL; i * i <= N; ++i) {
    if (is_prime[i] == true) {
      // if is prime we mark all of its multiple as composite
      // e.g. 2 is prime then 4, 8, 10, 12... so on. until <= N
      for (auto j = i * i; j <= N; j += i) { is_prime[j] = false; }
    }
  }

  auto result = std::vector<u64>{};
  for (auto i = 0ULL; i < is_prime.size(); ++i) {
    if (is_prime[i] == true) { result.push_back(i); }
  }

  return result;
}

// TODO: does not work. Infinite loop
auto sieve_sundaram(u64 N) {
  auto is_prime = std::vector<bool>(N + 1, true);
  const auto k  = (N - 2) / 2;
  for (auto i = 1ULL; i < k + 1; i++) {
    auto j = i;
    // NOLINTNEXTLINE
    while (i + j + 2 * i * j <= k) { is_prime[i + j + 2 * i * j] = false; }
  }

  auto result = std::vector<u64>{};
  for (auto i = 0ULL; i < is_prime.size(); ++i) {
    if (is_prime[i] == true) { result.push_back(i); }
  }
  return result;
}

template <auto SIZE>
auto pascal_triangle() {
  auto board = std::array<std::array<int, SIZE>, SIZE>{};
  std::ranges::fill(board, std::array<int, SIZE>{0});

  for (auto i = 0ULL; i < board.size(); ++i) { board[i][0] = board[0][i] = 1; }

  for (auto i = 1ULL; i < board.size(); ++i) {
    for (auto j = 1ULL; j < board.size(); ++j) {
      board[i][j] = board[i - 1][j] + board[i][j - 1];
    }
  }

  return board;
}

template <auto SIZE>
auto print(const std::array<std::array<int, SIZE>, SIZE>& board) -> void {
  for (const auto& outer : board) {
    for (const auto& inner : outer) { fmt::print("{} ", inner); }
    fmt::print("\n");
  }
}

struct System {
  i64 a{};
  i64 n{};
};

// Chinese remainder theorem
auto crt(const auto& sys) {
  const auto N =
    std::accumulate(begin(sys), end(sys), 1LL, [](auto init, const auto& sys) {
      return init * sys.n;
    });

  const auto X = std::transform_reduce(
    begin(sys), end(sys), 0LL, std::plus<>{}, [N](const auto& sys) {
      const auto ni = N / sys.n;

      // using mod_inverse we don't have to check if x is less than 0
      const auto si = mod_inverse(ni, sys.n);

      return sys.a * si * ni;
    });

  return std::make_pair(X % N, N);
}

auto main() -> int {
  /*
  std::cout << mod_exp(3, 10) << '\n';
  std::cout << mod_exp2(3, 10, 1000000007ULL) << '\n';
  std::cout << euclid(16, 10) << '\n';
  auto result = extended_euclid(16, 10);
  std::cout << "x: " << result.x << " y: " << result.y << " gcd: " << result.gcd
            << "\n\n";
  auto result2 = mod_inverse(5, 12);
  std::cout << "modular inverse: " << result2 << '\n';
  std::cout << mod_inverse2(5, 11) << '\n';

  // (a^b / c) % M
  auto a                  = 2ULL;
  auto b                  = 3ULL;
  [[maybe_unused]] auto c = 4ULL;
  auto M                  = 5LL;

  auto ab = mod_exp(a, b);
  auto x  = mod_inverse(static_cast<i64>(ab), M);
  std::cout << "x: " << x << '\n';


  auto is = is_prime(20201227);
  std::cout << std::boolalpha << is << '\n';

  auto pas = pascal_triangle<8>();
  print(pas);
  */

  //
  [[maybe_unused]] constexpr auto timestamp = 939;
  [[maybe_unused]] auto get_time            = [timestamp](auto id) {
    return (timestamp % id);
  };

  auto r = sieve(10'000'000);
  fmt::print("sieve:\n{}\n", r);

  auto s1 = std::vector<System>{{4, 5}, {4, 7}, {6, 11}};
  auto s2 = std::vector<System>{{2, 3}, {3, 5}, {2, 7}};
  auto s3 = std::vector<System>{{1, 4}, {2, 7}};
  auto s5 = std::vector<System>{{1, 2}, {2, 3}, {3, 5}, {4, 7}};
  auto s6 = std::vector<System>{{3, 5}, {2, 6}, {4, 7}};

  fmt::print("CRT: {}\n", crt(s1));
  fmt::print("CRT: {}\n", crt(s2));
  fmt::print("CRT: {}\n", crt(s3));
  fmt::print("CRT: {}\n", crt(s5));
  fmt::print("CRT: {}\n", crt(s6));

  auto s7 = std::vector<System>{{0, 7}, {1, 13}, {4, 59}, {6, 31}, {7, 19}};
  fmt::print("CRT: {}\n", crt(s7).second - crt(s7).first);

  /*
  auto t1 = mod_inverse(b * c, a);
  auto t2 = mod_inverse(a * c, b);
  auto t3 = mod_inverse(a * b, c);
  fmt::print("t1: {} t2: {} t3: {}\n", t1, t2, t3);

  auto X2 = t1 * (b * c) * 4 + t2 * (a * c) * 4 + t3 * (a * b) * 6;
  fmt::print("X2: {}\n", X2);

  auto result = X2 % X;
  fmt::print("result: {}\n", result);
  */

  return 0;
}
