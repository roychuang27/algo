template <class T, size_t D> struct Matrix {
        static_assert(D);
        std::array<size_t, D> s{};
        std::vector<T> a;
        template <class... A>
        requires(sizeof...(A) == D || sizeof...(A) == D + 1) Matrix(A... x) {
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
        template <class... I> size_t pos(I... i) const {
                static_assert(sizeof...(I) == D);
                size_t p = 0, d = 0;
                (((assert(std::in_range<size_t>(i) && size_t(i) < s[d]),
                   p = p * s[d++] + size_t(i))),
                 ...);
                return p;
        }
        template <class... I> T &at(I... i) {
                return a[pos(i...)];
        }
        template <class... I> const T &at(I... i) const {
                return a[pos(i...)];
        }
        std::string format_to_string() const {
                std::ostringstream oss;
                auto print_impl = [&](auto &self, size_t dim,
                                      size_t offset) -> void {
                        if (dim == D) {
                                oss << a[offset];
                                return;
                        }
                        oss << "[";
                        size_t stride = 1;
                        for (size_t i = dim + 1; i < D; ++i) {
                                stride *= s[i];
                        }
                        for (size_t i = 0; i < s[dim]; ++i) {
                                self(self, dim + 1, offset + i * stride);
                                if (i + 1 < s[dim]) {
                                        oss << ", ";
                                }
                        }
                        oss << "]";
                };
                print_impl(print_impl, 0, 0);
                return oss.str();
        }
};
