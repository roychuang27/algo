template <class T>
Matrix<T, 2> operator*(const Matrix<T, 2> &a, const Matrix<T, 2> &b) {
        assert(a.s[1] == b.s[0]);

        Matrix<T, 2> c(a.s[0], b.s[1], T{});

        for (size_t i = 0; i < a.s[0]; ++i)
                for (size_t k = 0; k < a.s[1]; ++k)
                        for (size_t j = 0; j < b.s[1]; ++j)
                                c[i, j] += a[i, k] * b[k, j];

        return c;
}

template <class T>
Matrix<T, 2> &operator*=(Matrix<T, 2> &a, const Matrix<T, 2> &b) {
        return a = a * b;
}

template <class T>
Matrix<T, 2> mat_pow(Matrix<T, 2> a, uint64_t n) {
        assert(a.s[0] == a.s[1]);

        Matrix<T, 2> res(a.s[0], a.s[1], T{});
        for (size_t i = 0; i < a.s[0]; ++i)
                res[i, i] = T{1};

        while (n) {
                if (n & 1)
                        res = res * a;
                a = a * a;
                n >>= 1;
        }

        return res;
}
