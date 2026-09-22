#include <bits/stdc++.h>

#include <cassert>
using namespace std;

using lli = long long int;

template <class T, size_t D>
struct IL {
        using type = initializer_list<typename IL<T, D - 1>::type>;
};

template <class T>
struct IL<T, 1> {
        using type = initializer_list<T>;
};

template <class T, size_t D>
struct Matrix {
        static_assert(D > 0);

        array<size_t, D> s{};
        vector<T> a;

        Matrix(typename IL<T, D>::type l) { load<0>(l); }

        template <class... A>
                requires(sizeof...(A) == D || sizeof...(A) == D + 1)
        Matrix(A... x) {
                if constexpr (sizeof...(A) == D)
                        init<0>(1, x..., T{});
                else
                        init<0>(1, x...);
        }

       private:
        array<bool, D> seen{};

        template <size_t d, class X, class... R>
        void init(size_t n, X x, R... r) {
                if constexpr (d < D) {
                        s[d] = x;
                        init<d + 1>(n * s[d], r...);
                } else {
                        a.assign(n, x);
                }
        }

        template <size_t d, class X>
        void load(const X& x) {
                if constexpr (d == D) {
                        a.push_back(x);
                } else {
                        if (!seen[d]) {
                                s[d] = x.size();
                                seen[d] = true;
                        } else {
                                assert(s[d] == x.size());
                        }

                        for (auto& y : x) load<d + 1>(y);
                }
        }

        template <class... I>
        size_t pos(I... i) const {
                static_assert(sizeof...(I) == D);

                size_t p = 0, d = 0;
                (((assert(i >= 0 && size_t(i) < s[d]),
                   p = p * s[d++] + size_t(i))),
                 ...);

                return p;
        }

       public:
        template <class... I>
        T& operator[](I... i) {
                return a[pos(i...)];
        }

        template <class... I>
        const T& operator[](I... i) const {
                return a[pos(i...)];
        }
};

template <class T, size_t D>
istream& operator>>(istream& is, Matrix<T, D>& m)
        requires(D == 1 || D == 2)
{
        for (auto& x : m.a) is >> x;
        return is;
}

template <class T, size_t D>
ostream& operator<<(ostream& os, const Matrix<T, D>& m)
        requires(D == 1 || D == 2)
{
        for (size_t i = 0; i < m.s[0]; ++i) {
                if (i) os << '\n';

                for (size_t j = 0; j < (D == 1 ? 1 : m.s[1]); ++j) {
                        if (j) os << ' ';
                        os << m.a[i * (D == 1 ? 1 : m.s[1]) + j];
                }
        }
        return os;
}

template <class T, size_t D>
Matrix<T, D> operator+(const Matrix<T, D>& a, const Matrix<T, D>& b)
        requires(D == 2)
{
        assert(a.s == b.s);

        Matrix<T, D> c(a.s[0], a.s[1], T{});

        for (size_t i = 0; i < a.a.size(); ++i) c.a[i] = a.a[i] + b.a[i];

        return c;
}

template <class T, size_t D>
Matrix<T, D> operator-(const Matrix<T, D>& a, const Matrix<T, D>& b)
        requires(D == 2)
{
        assert(a.s == b.s);

        Matrix<T, D> c(a.s[0], a.s[1], T{});

        for (size_t i = 0; i < a.a.size(); ++i) c.a[i] = a.a[i] - b.a[i];

        return c;
}

template <class T>
Matrix<T, 2> naive_mul(const Matrix<T, 2>& a, const Matrix<T, 2>& b) {
        assert(a.s[1] == b.s[0]);

        Matrix<T, 2> c(a.s[0], b.s[1], T{});

        for (size_t i = 0; i < a.s[0]; ++i)
                for (size_t k = 0; k < a.s[1]; ++k)
                        for (size_t j = 0; j < b.s[1]; ++j)
                                c.a[i * b.s[1] + j] +=
                                    a.a[i * a.s[1] + k] * b.a[k * b.s[1] + j];

        return c;
}

template <class T>
Matrix<T, 2> strassen(const Matrix<T, 2>& a, const Matrix<T, 2>& b) {
        size_t n = a.s[0];

        if (n <= 64) return naive_mul(a, b);

        size_t h = n / 2;

        auto block = [&](const Matrix<T, 2>& x, size_t r, size_t c) {
                Matrix<T, 2> y(h, h, T{});

                for (size_t i = 0; i < h; ++i)
                        for (size_t j = 0; j < h; ++j)
                                y.a[i * h + j] = x.a[(i + r) * n + j + c];

                return y;
        };

        auto A11 = block(a, 0, 0);
        auto A12 = block(a, 0, h);
        auto A21 = block(a, h, 0);
        auto A22 = block(a, h, h);

        auto B11 = block(b, 0, 0);
        auto B12 = block(b, 0, h);
        auto B21 = block(b, h, 0);
        auto B22 = block(b, h, h);

        auto M1 = strassen(A11 + A22, B11 + B22);
        auto M2 = strassen(A21 + A22, B11);
        auto M3 = strassen(A11, B12 - B22);
        auto M4 = strassen(A22, B21 - B11);
        auto M5 = strassen(A11 + A12, B22);
        auto M6 = strassen(A21 - A11, B11 + B12);
        auto M7 = strassen(A12 - A22, B21 + B22);

        auto C11 = M1 + M4 - M5 + M7;
        auto C12 = M3 + M5;
        auto C21 = M2 + M4;
        auto C22 = M1 - M2 + M3 + M6;

        Matrix<T, 2> c(n, n, T{});

        for (size_t i = 0; i < h; ++i)
                for (size_t j = 0; j < h; ++j) {
                        c.a[i * n + j] = C11.a[i * h + j];
                        c.a[i * n + j + h] = C12.a[i * h + j];
                        c.a[(i + h) * n + j] = C21.a[i * h + j];
                        c.a[(i + h) * n + j + h] = C22.a[i * h + j];
                }

        return c;
}

template <class T>
Matrix<T, 2> operator*(const Matrix<T, 2>& a, const Matrix<T, 2>& b) {
        assert(a.s[1] == b.s[0]);

        size_t n = a.s[0];

        if (n == a.s[1] && n == b.s[0] && n == b.s[1] && n >= 64) {
                size_t p = 1;
                while (p < n) p <<= 1;

                if (p == n) return strassen(a, b);

                Matrix<T, 2> aa(p, p, T{});
                Matrix<T, 2> bb(p, p, T{});

                for (size_t i = 0; i < n; ++i)
                        for (size_t j = 0; j < n; ++j) {
                                aa.a[i * p + j] = a.a[i * n + j];
                                bb.a[i * p + j] = b.a[i * n + j];
                        }

                auto cc = strassen(aa, bb);

                Matrix<T, 2> c(n, n, T{});

                for (size_t i = 0; i < n; ++i)
                        for (size_t j = 0; j < n; ++j)
                                c.a[i * n + j] = cc.a[i * p + j];

                return c;
        }

        return naive_mul(a, b);
}

template <class T>
Matrix<T, 2> operator^(Matrix<T, 2> a, uint64_t n) {
        assert(a.s[0] == a.s[1]);

        Matrix<T, 2> r(a.s[0], a.s[1], T{});

        for (size_t i = 0; i < a.s[0]; ++i) r[i, i] = T{1};

        while (n) {
                if (n & 1) r = r * a;

                n >>= 1;
                if (n) a = a * a;
        }

        return r;
}

template <long long M>
struct Mint {
        long long x;

        Mint(long long x = 0) : x((x % M + M) % M) {}

        Mint& operator+=(Mint b) {
                x += b.x;
                if (x >= M) x -= M;
                return *this;
        }

        Mint& operator-=(Mint b) {
                x -= b.x;
                if (x < 0) x += M;
                return *this;
        }

        Mint& operator*=(Mint b) {
                x = 1LL * x * b.x % M;
                return *this;
        }

        Mint pow(long long n) const {
                Mint r = 1, a = *this;

                for (; n; n >>= 1, a *= a)
                        if (n & 1) r *= a;

                return r;
        }

        Mint inv() const { return pow(M - 2); }

        Mint& operator/=(Mint b) { return *this *= b.inv(); }

        friend Mint operator+(Mint a, Mint b) { return a += b; }

        friend Mint operator-(Mint a, Mint b) { return a -= b; }

        friend Mint operator*(Mint a, Mint b) { return a *= b; }

        friend Mint operator/(Mint a, Mint b) { return a /= b; }

        friend ostream& operator<<(ostream& os, Mint a) { return os << a.x; }

        friend istream& operator>>(istream& is, Mint& a) {
                long long x;
                is >> x;
                a = x;
                return is;
        }
};

using mint = Mint<1000000007>;

void precompute() {}

void solve() {
        lli N;
        cin >> N;

        if (N == 0) {
                cout << 0 << '\n';
                return;
        }

        Matrix<mint, 2> mat{{1, 1}, {1, 0}};
        mat = mat ^ (N - 1);
        cout << mat[0, 0] << '\n';
}

int main() {
#ifndef LOCAL
        cin.tie(nullptr)->sync_with_stdio(false);
#endif
        precompute();
        solve();
        return 0;
}
