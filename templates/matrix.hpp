template <class T, size_t D, class Seq>
struct MatrixBase;

template <class T, size_t D>
struct MatrixBase<T, D, index_sequence<>> {
        struct Dim {
                size_t v;
                template <integral I>
                Dim(I x):
                        v(size_t(x)) {
                        if constexpr (signed_integral<I>) {
                                assert(x >= 0);
                        }
                }
        };
        conditional_t<D == 0, vector<size_t>, array<size_t, D>> s{};
        vector<T> a;
        MatrixBase() = default;
        void init(const T &v, auto... ds) {
                s = {ds.v...};
                size_t n = 1;
                for (size_t x : s) {
                        n *= x;
                }
                a.assign(n, v);
        }
};

template <class T, size_t D, size_t I, size_t... Is>
struct MatrixBase<T, D, index_sequence<I, Is...>>
        : MatrixBase<T, D, index_sequence<>> {
        using Base = MatrixBase<T, D, index_sequence<>>;
        using Base::Base;
        template <size_t>
        using dim_t = typename Base::Dim;
        MatrixBase(dim_t<I> d0, dim_t<Is>... ds, const T &v = T{}) {
                this->init(v, d0, ds...);
        }
};

template <class T, size_t I, size_t... Is>
struct MatrixBase<T, 0, index_sequence<I, Is...>>
        : MatrixBase<T, 0, index_sequence<Is...>> {
        using Base = MatrixBase<T, 0, index_sequence<Is...>>;
        using Base::Base;
        template <size_t>
        using dim_t = typename Base::Dim;
        MatrixBase(dim_t<I> d0, dim_t<Is>... ds, const T &v) {
                this->init(v, d0, ds...);
        }
};

template <class T, size_t D = 0>
struct Matrix : MatrixBase<T, D, make_index_sequence<D ? D : 16>> {
        using Base = MatrixBase<T, D, make_index_sequence<D ? D : 16>>;
        using Base::Base;
        using Base::a;
        using Base::s;
        template <class... I>
        size_t pos(I... i) const {
                if constexpr (D > 0) {
                        static_assert(sizeof...(I) == D);
                } else {
                        static_assert(sizeof...(I) > 0);
                        assert(sizeof...(I) == s.size());
                }
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
                if (s.empty()) {
                        return "[]";
                }
                ostringstream oss;
                auto impl = [&](auto &self, size_t d, size_t p) -> void {
                        if (d == s.size()) {
                                oss << a[p];
                                return;
                        }
                        oss << '[';
                        size_t stride = 1;
                        for (size_t i = d + 1; i < s.size(); i++) {
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

template <class... A>
        requires(sizeof...(A) >= 2)
Matrix(A...) -> Matrix<tuple_element_t<sizeof...(A) - 1, tuple<A...>>,
                       sizeof...(A) - 1>;
