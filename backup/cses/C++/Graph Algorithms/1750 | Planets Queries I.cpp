#include <bits/stdc++.h>
#include <cassert>
using namespace std;


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

        array<size_t, D> s{}, st{};
        vector<T> a;

        void init() {
                st[D - 1] = 1;
                for (size_t i = D - 1; i--;) st[i] = st[i + 1] * s[i + 1];

                size_t n = 1;
                for (auto x : s) n *= x;
                a.resize(n);
        }

        size_t pos(const array<size_t, D>& x) const {
                size_t p = 0;
                for (size_t i = 0; i < D; ++i) {
                        assert(x[i] < s[i]);
                        p += x[i] * st[i];
                }
                return p;
        }

        template <size_t d, class X>
        void shape(const X& x) {
                s[d] = x.size();
                if constexpr (d + 1 < D) shape<d + 1>(*x.begin());
        }

        template <size_t d, class X>
        void load(const X& x, size_t& p) {
                if constexpr (d + 1 == D) {
                        for (auto&& v : x) a[p++] = v;
                } else {
                        for (auto&& v : x) load<d + 1>(v, p);
                }
        }

        template <class... Args>
        Matrix(Args... x)
                requires(sizeof...(x) == D + 1)
        {
                auto t = tuple{x...};

                [&]<size_t... I>(index_sequence<I...>) {
                        s = {size_t(get<I>(t))...};
                }(make_index_sequence<D>{});

                init();
                fill(a.begin(), a.end(), T(get<D>(t)));
        }

        Matrix(typename IL<T, D>::type x) {
                shape<0>(x);
                init();

                size_t p = 0;
                load<0>(x, p);

                assert(p == a.size());
        }

        template <class... I>
        T& at(I... i) {
                static_assert(sizeof...(I) == D);
                return a[pos({size_t(i)...})];
        }
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, Q;
	cin >> N >> Q;
	Matrix<int, 2> jump(N+1, 32, 0);
	for (int i = 1; i <= N; i++) {
		cin >> jump.at(i, 0);
	}
	for (int k = 1; k <= 31; k++) {
		for (int i = 1; i <= N; i++) {
			jump.at(i, k) = jump.at( jump.at(i, k-1), k-1);
		}
	}
	while (Q--) {
		int k, x;
		cin >> x >> k;
		int i = 0;
		while ((1 << i) <= k) {
			if (k & (1 << i)) {
				x = jump.at(x, i);
			}
			i++;
		}
		cout << x << '\n';
	}
	return 0;
}
