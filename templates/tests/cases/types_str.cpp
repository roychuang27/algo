// Types format themselves through str(); no formatter, no stream overload.
// headers: modint.hpp fraction.hpp matrix.hpp
--- code
        using mint = StaticModint<998244353>;
        mint a = 2, b = 3;
        cout << (a + b).str() << ' ' << (a * b).str() << '\n';
        Fraction<long long> f(-1, 3);
        cout << f.str() << ' ' << (f + Fraction<long long>(1, 3)).str() << '\n';
        Matrix<int, 2> m(2, 2);
        m[0, 0] = 1, m[1, 1] = 2;
        Matrix<int, 3> n(2, 2, 2);
        n[1, 1, 1] = 5;
        cout << m.str() << ' ' << n.str() << '\n';
        ITER<vector<int>> it{{1, 2, 3}};
        O(it);
--- out
5 6
-1/3 0/1
[[1, 0], [0, 2]] [[[0, 0], [0, 0]], [[0, 0], [0, 5]]]
1 2 3
