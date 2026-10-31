template <long long MOD>
struct StaticModint {
        static_assert(MOD > 0);
        long long v = 0;
        using mint = StaticModint;
        constexpr StaticModint() = default;
        template <class T>
        StaticModint(T x) {
                v = static_cast<long long>(x % MOD);
                if (v < 0) {
                        v += MOD;
                }
        }
        long long val() const {
                return v;
        }
        mint &operator+=(const mint &rhs) {
                if (v >= MOD - rhs.v) {
                        v -= MOD - rhs.v;
                } else {
                        v += rhs.v;
                }
                return *this;
        }
        mint &operator-=(const mint &rhs) {
                v -= rhs.v;
                if (v < 0) {
                        v += MOD;
                }
                return *this;
        }
        mint &operator*=(const mint &rhs) {
                v = v * rhs.v % MOD;
                return *this;
        }
        mint &operator/=(const mint &rhs) {
                return *this *= rhs.inv();
        }
        mint pow(long long n) const {
                assert(n >= 0);
                mint a = *this, res = 1;
                while (n > 0) {
                        if (n & 1) {
                                res *= a;
                        }
                        a *= a;
                        n >>= 1;
                }
                return res;
        }
        mint inv() const {
                assert(v != 0);
                return pow(MOD - 2);
        }
        mint operator+() const {
                return *this;
        }
        mint operator-() const {
                return mint(v == 0 ? 0 : MOD - v);
        }
        friend mint operator+(mint lhs, const mint &rhs) {
                return lhs += rhs;
        }
        friend mint operator-(mint lhs, const mint &rhs) {
                return lhs -= rhs;
        }
        friend mint operator*(mint lhs, const mint &rhs) {
                return lhs *= rhs;
        }
        friend mint operator/(mint lhs, const mint &rhs) {
                return lhs /= rhs;
        }
        friend bool operator==(const mint &lhs, const mint &rhs) {
                return lhs.v == rhs.v;
        }
        friend bool operator!=(const mint &lhs, const mint &rhs) {
                return lhs.v != rhs.v;
        }
        friend std::ostream &operator<<(std::ostream &os, mint a) {
                return os << a.val();
        }
        friend std::istream &operator>>(std::istream &is, mint &a) {
                long long x;
                is >> x;
                a = x;
                return is;
        }
};
#ifdef __cpp_lib_format
template <long long MOD>
struct std::formatter<static_modint<MOD> > : std::formatter<long long> {
        auto format(const static_modint<MOD> &x, auto &ctx) const {
                return std::formatter<long long>::format(x.val(), ctx);
        }
};
#endif

// using mint = StaticModint<1'000'000'007>;
// using mint = StaticModint<998244353>;
