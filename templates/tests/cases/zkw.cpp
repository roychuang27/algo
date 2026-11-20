// Segtree and LazySegtree: constructor-argument lambdas (stateless & capturing),
// explicit type-argument default construction, 2000 random operations checked
// against brute force, plus deterministic max_right/min_left queries.
// headers: zkw.hpp zkw_lazy.hpp
--- code
        auto op = [](long long a, long long b) { return a + b; };
        auto e = [] { return 0LL; };
        int n = 8;
        Segtree seg(n, op, e);
        mt19937 rng(777);
        vector<long long> brute(n, 0);
        bool ok = true;
        for (int step = 0; step < 2000; step++) {
                int i = rng() % n;
                if (rng() % 2) {
                        long long v = rng() % 20;
                        seg.set(i, v), brute[i] = v;
                } else {
                        int l = rng() % (n + 1), r = rng() % (n + 1);
                        if (l > r) {
                                swap(l, r);
                        }
                        long long want =
                                accumulate(brute.begin() + l, brute.begin() + r, 0LL);
                        ok = ok && want == seg.prod(l, r);
                }
        }
        cout << "seg random " << ok << '\n';
        Segtree<long long, decltype(op), decltype(e)> fresh(n);
        fresh.set(0, 3), fresh.set(3, 4);
        cout << "seg " << fresh.get(0) << ' ' << fresh.prod(0, 5) << ' '
             << fresh.all_prod() << '\n';

        using S = pair<long long, int>;
        auto sop = [](S a, S b) { return S{a.first + b.first, a.second + b.second}; };
        auto se = [] { return S{0, 0}; };
        auto mapping = [](long long f, S x) {
                return S{x.first + f * x.second, x.second};
        };
        auto composition = [](long long f, long long g) { return f + g; };
        auto id = [] { return 0LL; };
        LazySegtree lseg(vector<S>(n, S{0, 1}), sop, se, mapping, composition, id);
        vector<long long> lazy_brute(n, 0);
        ok = true;
        for (int step = 0; step < 2000; step++) {
                int l = rng() % (n + 1), r = rng() % (n + 1);
                if (l > r) {
                        swap(l, r);
                }
                if (rng() % 2) {
                        long long v = rng() % 20;
                        lseg.apply(l, r, v);
                        for (int i = l; i < r; i++) {
                                lazy_brute[i] += v;
                        }
                } else {
                        long long want =
                                accumulate(lazy_brute.begin() + l, lazy_brute.begin() + r, 0LL);
                        ok = ok && want == lseg.prod(l, r).first;
                }
        }
        cout << "lazy random " << ok << '\n';
        LazySegtree<S, decltype(sop), decltype(se), long long, decltype(mapping),
                    decltype(composition), decltype(id)>
                zeros(vector<S>(n, S{0, 1}));
        zeros.apply(0, 4, 2);
        cout << "lazy " << zeros.get(0).first << ' ' << zeros.prod(0, n).first << ' '
             << zeros.all_prod().first << '\n';

        long long mod = 10;
        long long cap = 10;
        vector<long long> init_holder{0LL};
        Segtree cap_mod(
                vector<long long>{3, 0, 0, 4, 5},
                [mod](const long long &a, const long long &b) { return (a + b) % mod; },
                [init_holder] { return init_holder[0]; });
        Segtree cap_seg(
                vector<long long>{3, 0, 0, 4, 5},
                [cap](const long long &a, const long long &b) {
                        return min(a + b, cap);
                },
                [init_holder] { return init_holder[0]; });
        long long limit = 5;
        cout << "seg cap " << cap_mod.prod(0, 5) << ' ' << cap_seg.prod(0, 5) << ' '
             << cap_seg.max_right<[](const long long &x) { return x <= 5; }>(0) << ' '
             << cap_seg.min_left(4, [&](const auto &x) { return x < limit; }) << '\n';

        long long lmod = 100;
        LazySegtree cap_lazy(
                vector<S>(n, S{0, 1}),
                [&](const S &a, const S &b) {
                        return S{(a.first + b.first) % lmod, a.second + b.second};
                },
                [init_holder] { return S{init_holder[0], 0}; },
                [&](long long f, const S &x) {
                        return S{(x.first + f * x.second) % lmod, x.second};
                },
                [&](long long f, long long g) { return (f + g) % lmod; },
                [init_holder] { return init_holder[0]; });
        cap_lazy.apply(0, 4, 3);
        int mr = cap_lazy.max_right<[](const S &x) { return x.first <= 6; }>(0);
        int ml = cap_lazy.min_left(n, [&](const S &x) { return x.first < 6; });
        cap_lazy.apply(0, 4, 25);
        cout << "lazy cap " << cap_lazy.prod(0, n).first << ' ' << mr << ' ' << ml
             << '\n';
--- out
seg random 1
seg 3 7 7
lazy random 1
lazy 2 8 8
seg cap 2 10 3 1
lazy cap 12 2 3
