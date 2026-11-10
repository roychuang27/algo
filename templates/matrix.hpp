template <class T, size_t D>
struct Matrix {
        static_assert(D);
        array<size_t, D> s{};
        vector<T> a;
        template <class... A>
                requires(sizeof...(A) == D || sizeof...(A) == D + 1)
        Matrix(A... x) {
                if constexpr (sizeof...(A) == D) {
                        init<0>(1, x..., T{});
                } else {
                        init<0>(1, x...);
                }
        }
        template <size_t d, class X, class... R>
        void init(size_t n, X x, R... r) {
                if constexpr (d < D) {
                        s[d] = x, init<d + 1>(n * s[d], r...);
                } else {
                        a.assign(n, x);
                }
        }
        template <class... I>
        size_t pos(I... i) const {
                static_assert(sizeof...(I) == D);
                size_t p = 0, d = 0;
                (((assert(in_range<size_t>(i) && size_t(i) < s[d]),
                   p = p * s[d++] + size_t(i))),
                 ...);
                return p;
        }
        template <class... I>
        decltype(auto) at(I... i) {
                return a[pos(i...)];
        }
        template <class... I>
        decltype(auto) at(I... i) const {
                return a[pos(i...)];
        }
        template <class... I>
        decltype(auto) operator[](I... i) {
                return a[pos(i...)];
        }
        template <class... I>
        decltype(auto) operator[](I... i) const {
                return a[pos(i...)];
        }
        string str() const {
                ostringstream oss;
                auto impl = [&](auto &self, size_t d, size_t p) -> void {
                        if (d == D) {
                                oss << a[p];
                                return;
                        }
                        oss << '[';
                        size_t stride = 1;
                        for (size_t i = d + 1; i < D; i++) {
                                stride *= s[i];
                        }
                        for (size_t i = 0; i < s[d]; i++) {
                                self(self, d + 1, p + i * stride);
                                if (i + 1 < s[d]) {
                                        oss << ", ";
                                }
                        }
                        oss << ']';
                };
                impl(impl, 0, 0);
                return oss.str();
        }
};
