template <class T, size_t D>
        requires(D == 0 || D == 2)
Matrix<T, D> operator*(const Matrix<T, D> &a, const Matrix<T, D> &b) {
        assert(a.s.size() == 2 && b.s.size() == 2 && a.s[1] == b.s[0]);

        Matrix<T, D> c(a.s[0], b.s[1], {});

        for (size_t i = 0; i < a.s[0]; ++i) {
                for (size_t k = 0; k < a.s[1]; ++k) {
                        for (size_t j = 0; j < b.s[1]; ++j) {
                                c[i, j] += a[i, k] * b[k, j];
                        }
                }
        }

        return c;
}

template <class T, size_t D>
        requires(D == 0 || D == 2)
Matrix<T, D> &operator*=(Matrix<T, D> &a, const Matrix<T, D> &b) {
        return a = a * b;
}

template <class T, size_t D>
        requires(D == 0 || D == 2)
Matrix<T, D> mat_pow(Matrix<T, D> a, uint64_t n) {
        assert(a.s.size() == 2 && a.s[0] == a.s[1]);

        Matrix<T, D> res(a.s[0], a.s[1], {});
        for (size_t i = 0; i < a.s[0]; ++i) {
                res[i, i] = T{1};
        }

        while (n) {
                if (n & 1) {
                        res = res * a;
                }
                a = a * a;
                n >>= 1;
        }

        return res;
}
