template <uint32_t mod>
struct MontgomeryModint {
        using mint = MontgomeryModint;
        using u32 = uint32_t;
        using u64 = uint64_t;
        using i64 = int64_t;
        static_assert(mod > 2 && mod % 2 == 1 && mod < (1U << 31),
                      "mod must be an odd prime < 2^31.");
        static_assert(
                [] { // Miller-Rabin, bases {2,7,61} are deterministic for n < 4759123141
                        u64 d = mod - 1;
                        int s = 0;
                        while (d % 2 == 0) {
                                d /= 2, s++;
                        }
                        for (u64 a : {2, 7, 61}) {
                                if (a % mod == 0) {
                                        continue;
                                }
                                u64 y = 1, b = a;
                                for (u64 t = d; t; t >>= 1, b = b * b % mod) {
                                        if (t & 1) {
                                                y = y * b % mod;
                                        }
                                }
                                bool ok = y == 1 || y == mod - 1;
                                for (int i = 1; i < s && !ok; i++) {
                                        ok = (y = y * y % mod) == mod - 1;
                                }
                                if (!ok) {
                                        return false;
                                }
                        }
                        return true;
                }(),
                "mod must be a prime number.");
        static constexpr u32 n2 = -u64(mod) % mod; // 2^64 mod p
        static constexpr u32 inv = [] {            // mod^{-1} mod 2^32 (Newton iteration)
                u32 x = mod;
                for (int i = 0; i < 4; i++) {
                        x *= 2 - mod * x;
                }
                return x;
        }();
        static constexpr u32 get_mod() {
                return mod;
        }
        u32 a; // strictly kept in [0, mod)
        static u32 reduce(u64 b) {
                // b < mod * 2^32 -> (b / 2^32) mod p, result in [0, mod)
                u32 t = b >> 32, m = (u64(u32(b) * inv) * mod) >> 32;
                return t >= m ? t - m : t + (mod - m);
        }
        MontgomeryModint():
                a(0) {
        }
        MontgomeryModint(i64 b):
                a(reduce(u64((b % mod + mod) % mod) * n2)) {
        }
        mint pow(u64 k) const {
                mint res(1), base(*this);
                for (; k; k >>= 1, base *= base) {
                        if (k & 1) {
                                res *= base;
                        }
                }
                return res;
        }
        mint inverse() const {
                return pow(mod - 2);
        }
        u32 get() const {
                return reduce(a);
        }
        mint &operator+=(const mint &b) {
                a = a >= mod - b.a ? a - (mod - b.a) : a + b.a;
                return *this;
        }
        mint &operator-=(const mint &b) {
                a = a >= b.a ? a - b.a : a + (mod - b.a);
                return *this;
        }
        mint &operator*=(const mint &b) {
                a = reduce(u64(a) * b.a);
                return *this;
        }
        mint &operator/=(const mint &b) {
                return *this *= b.inverse();
        }
        mint operator-() const {
                return mint() - *this;
        }
        bool operator==(const mint &b) const {
                return a == b.a;
        }
        friend mint operator+(mint c, const mint &d) {
                return c += d;
        }
        friend mint operator-(mint c, const mint &d) {
                return c -= d;
        }
        friend mint operator*(mint c, const mint &d) {
                return c *= d;
        }
        friend mint operator/(mint c, const mint &d) {
                return c /= d;
        }
        friend ostream &operator<<(ostream &os, const mint &b) {
                return os << b.get();
        }
        friend istream &operator>>(istream &is, mint &b) {
                i64 v;
                is >> v;
                b = mint(v);
                return is;
        }
};

// using mint = MontgomeryModint<1'000'000'007>;
// using mint = MontgomeryModint<998244353>;
