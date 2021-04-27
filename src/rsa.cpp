#include <fmt/format.h>

#include <cassert>
#include <numeric>

using u64          = unsigned long long;
using i64          = long long;
constexpr auto mod = 1000000007ULL;

consteval auto compute_mod(int p, int q) -> int {
  assert(p != q);
  return p * q;
}

struct Euclid_Result {
  i64 x{};
  i64 y{};
  i64 gcd{};
};

consteval auto extended_euclid(i64 a, i64 b) {
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

consteval auto mod_inverse(i64 a, i64 M) {
  const auto euclid = extended_euclid(a, M);
  return ((euclid.x % M) + M) % M;
}

consteval auto mod_exp(u64 base, u64 exp) {
  if (exp == 0) {
    return 1ULL;
  } else if (exp % 2 == 0) {
    return mod_exp((base * base) % mod, exp / 2);
  } else {
    return base * mod_exp((base * base) % mod, (exp - 1) / 2) % mod;
  }
}

consteval auto encrypt(u64 M, u64 e, u64 n) { return mod_exp(M, e) % n; }

consteval auto decrypt(u64 C, u64 d, u64 n) { return mod_exp(C, d) % n; }

auto main() -> int {
  const auto p = 17;
  const auto q = 31;
  const auto e = 7;  // public key
  const auto M = 2;

  const auto n = compute_mod(p, q);
  const auto t = std::lcm(p - 1, q - 1);
  const auto d = mod_inverse(e, t);  // private key

  fmt::print(
    "Public key: n({0}) e({1}), Private key: n({0}) d({2})\n", n, e, d);
  fmt::print("message: {}\n", M);
  const auto encrypted = encrypt(M, e, n);
  fmt::print("encrypted {}\n", encrypted);
  const auto decrypted = decrypt(encrypted, d, n);
  fmt::print("decrypted {}\n", decrypted);

  return 0;
}
