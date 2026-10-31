template <typename T = long long>
struct Fraction {
        T n, d;

        Fraction(T _n = 0, T _d = 1): n(_n), d(_d) {
        }

        template <typename U>
        Fraction(const Fraction<U> &other): n(static_cast<T>(other.n)), d(static_cast<T>(other.d)) {
        }

        static T abs_val(T x) {
                return x < 0 ? -x : x;
        }

        static T gcd_val(T a, T b) {
                a = abs_val(a);
                b = abs_val(b);
                while (b != 0) {
                        T t = a % b;
                        a = b;
                        b = t;
                }
                return a;
        }

        Fraction &reduce() {
                if (d < 0) {
                        n = -n;
                        d = -d;
                }
                if (n == 0) {
                        d = (d == 0) ? 0 : 1;
                        return *this;
                }
                T g = gcd_val(n, d);
                if (g > 1) {
                        n /= g;
                        d /= g;
                }
                return *this;
        }

        Fraction operator+() const {
                Fraction res = *this;
                return res.reduce();
        }
        Fraction operator-() const {
                Fraction res = *this;
                res.reduce();
                res.n = -res.n;
                return res.reduce();
        }

        Fraction &operator+=(const Fraction &other) {
                this->reduce();
                Fraction rhs = other;
                rhs.reduce();
                n = n * rhs.d + rhs.n * d;
                d = d * rhs.d;
                return this->reduce();
        }

        Fraction &operator-=(const Fraction &other) {
                this->reduce();
                Fraction rhs = other;
                rhs.reduce();
                n = n * rhs.d - rhs.n * d;
                d = d * rhs.d;
                return this->reduce();
        }

        Fraction &operator*=(const Fraction &other) {
                this->reduce();
                Fraction rhs = other;
                rhs.reduce();
                n = n * rhs.n;
                d = d * rhs.d;
                return this->reduce();
        }

        Fraction &operator/=(const Fraction &other) {
                this->reduce();
                Fraction rhs = other;
                rhs.reduce();
                n = n * rhs.d;
                d = d * rhs.n;
                return this->reduce();
        }

        friend Fraction operator+(Fraction lhs, const Fraction &rhs) {
                return lhs += rhs;
        }
        friend Fraction operator-(Fraction lhs, const Fraction &rhs) {
                return lhs -= rhs;
        }
        friend Fraction operator*(Fraction lhs, const Fraction &rhs) {
                return lhs *= rhs;
        }
        friend Fraction operator/(Fraction lhs, const Fraction &rhs) {
                return lhs /= rhs;
        }

        friend bool operator==(const Fraction &lhs, const Fraction &rhs) {
                return lhs.n * rhs.d == rhs.n * lhs.d;
        }

        friend std::strong_ordering operator<=>(const Fraction &lhs, const Fraction &rhs) {
                T ln = lhs.d < 0 ? -lhs.n : lhs.n;
                T ld = lhs.d < 0 ? -lhs.d : lhs.d;
                T rn = rhs.d < 0 ? -rhs.n : rhs.n;
                T rd = rhs.d < 0 ? -rhs.d : rhs.d;
                return (ln * rd) <=> (rn * ld);
        }

        friend std::istream &operator>>(std::istream &is, Fraction &f) {
                return is >> f.n >> f.d;
        }
};

#ifdef __cpp_lib_format
template <typename T>
struct std::formatter<Fraction<T>> {
        constexpr auto parse(std::format_parse_context &ctx) {
                return ctx.begin();
        }

        auto format(const Fraction<T> &f, std::format_context &ctx) const {
                return std::format_to(ctx.out(), "{}/{}", f.n, f.d);
        }
};
#endif
