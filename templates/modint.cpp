template <long long M> struct Modint {
        long long x;
        Modint(long long _x = 0)
                : x(_x % M) {
        }
        Modint &operator+=(Modint b) {
                x += b.x;
                if (x >= M) {
                        x -= M;
                }
                return *this;
        }
        Modint &operator-=(Modint b) {
                x -= b.x;
                if (x < 0) {
                        x += M;
                }
                return *this;
        }
        Modint &operator*=(Modint b) {
                x = 1LL * x * b.x % M;
                return *this;
        }
        Modint pow(long long n) const {
                Modint r = 1, a = *this;
                for (; n; n >>= 1, a *= a) {
                        if (n & 1) {
                                r *= a;
                        }
                }
                return r;
        }
        Modint inv() const {
                return pow(M - 2);
        }
        Modint &operator/=(Modint b) {
                return *this *= b.inv();
        }
        friend Modint operator+(Modint a, Modint b) {
                return a += b;
        }
        friend Modint operator-(Modint a, Modint b) {
                return a -= b;
        }
        friend Modint operator*(Modint a, Modint b) {
                return a *= b;
        }
        friend Modint operator/(Modint a, Modint b) {
                return a /= b;
        }
        friend std::ostream &operator<<(std::ostream &os, Modint a) {
                return os << a.x;
        }
        friend std::istream &operator>>(std::istream &is, Modint &a) {
                long long x;
                is >> x;
                a = x;
                return is;
        }
};

