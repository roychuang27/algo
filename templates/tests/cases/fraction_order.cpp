// Fractions compare, reduce, and format through str().
// headers: fraction.hpp
--- code
        array<Fraction<long long>, 4> a{
                Fraction<long long>(1, 2),
                Fraction<long long>(1, 3),
                Fraction<long long>(-1, 4),
                Fraction<long long>(2, 3),
        };
        sort(all(a));
        for (auto &x : a) {
                cout << x.str() << ' ';
        }
        cout << '\n';
        Fraction<long long> g(6, 8);
        cout << g.str() << ' ' << g.reduce().str() << '\n';
--- out
-1/4 1/3 1/2 2/3
6/8 3/4
