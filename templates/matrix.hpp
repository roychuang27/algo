template <class T, size_t D>
struct Matrix {
        static_assert(D);
        std::array<size_t, D> s{};
        std::vector<T> a;
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
                (((assert(std::in_range<size_t>(i) && size_t(i) < s[d]),
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
};

#ifdef __cpp_lib_format
template <class T, size_t D, class CharT>
struct std::formatter<Matrix<T, D>, CharT>
        : std::formatter<std::basic_string_view<CharT>, CharT> {
        template <class FormatContext>
        auto format(const Matrix<T, D> &mat, FormatContext &ctx) const {
                return std::formatter<std::basic_string_view<CharT>, CharT>::format(
                        mat.format_to_string(), ctx);
        }
};
#endif
