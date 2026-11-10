// Segtree and LazySegtree: both constructors, 2000 random operations checked
// against brute force, then a few deterministic queries.
// headers: zkw.hpp zkw_lazy.hpp
--- code
        auto op = [](long long a, long long b) { return a + b; };
        auto e = [] { return 0LL; };
        int n = 8;
        Segtree<long long, op, e> seg(n);
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
        Segtree<long long, op, e> fresh(n);
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
        LazySegtree<S, sop, se, long long, mapping, composition, id> lseg(
                vector<S>(n, S{0, 1}));
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
        LazySegtree<S, sop, se, long long, mapping, composition, id> zeros(
                vector<S>(n, S{0, 1}));
        zeros.apply(0, 4, 2);
        cout << "lazy " << zeros.get(0).first << ' ' << zeros.prod(0, n).first << ' '
             << zeros.all_prod().first << '\n';
--- out
seg random 1
seg 3 7 7
lazy random 1
lazy 2 8 8
