// headers: matrix.hpp matrix_mul.hpp
--- code
        // Automatic dimension count with {} and explicit values
        Matrix<int> mat(1, 2, 3, {});
        assert(mat.s.size() == 3);
        assert(mat.s[0] == 1 && mat.s[1] == 2 && mat.s[2] == 3);
        assert((mat[0, 1, 2] == 0));
        mat[0, 1, 2] = 7;
        cout << mat.str() << '\n';

        Matrix<int> mat_val(1, 2, 3, 5);
        assert((mat_val[0, 0, 0] == 5 && mat_val[0, 1, 2] == 5));

        Matrix<int> mat_brace{2, 2, {}};
        mat_brace[0, 1] = 3;
        cout << mat_brace.str() << '\n';

        int r0 = 2, r1 = 3;
        Matrix<int> mat_rt(r0, r1, {});
        Matrix<int> mat_rt_brace{r0, r1, {}};
        assert((mat_rt.s == vector<size_t>{2, 3}));
        assert((mat_rt_brace.s == vector<size_t>{2, 3}));

        // Nested Matrix
        Matrix<Matrix<int>> nested(2, 2, {1, 2, {}});
        assert((nested[1, 0].s == vector<size_t>{1, 2}));
        assert((nested[1, 0][0, 1] == 0));

        Matrix<int> mat1d(3, {});
        mat1d[2] = 9;
        cout << mat1d.str() << '\n';

        Matrix<int> empty_m;
        assert(empty_m.s.empty());
        cout << empty_m.str() << '\n';

        // Braced aggregate/pair/string/bool values
        Matrix<pair<int, int>> mp(2, 2, {3, 4});
        assert((mp[1, 1] == pair{3, 4}));
        Matrix<pair<int, int>> mp0(2, 2, {});
        assert((mp0[0, 1] == pair{0, 0}));

        Matrix<string> ms(1, 2, {});
        assert((ms[0, 1] == ""));
        Matrix<string> ms2(1, 2, "hi");
        assert((ms2[0, 0] == "hi"));

        Matrix<bool> mb(2, 2, {});
        mb[1, 0] = true;
        assert((!mb[0, 0] && mb[1, 0]));

        // Non-default-constructible element type
        struct NoDef {
                int x;
                NoDef(int v):
                        x(v) {
                }
        };
        Matrix<NoDef> mnd(2, 2, {42});
        assert((mnd[1, 1].x == 42));
        Matrix<NoDef, 2> mnd2(2, 2, {99});
        assert((mnd2[0, 1].x == 99));

        // Fixed D still works, including {}
        Matrix<int, 2> f2(2, 2);
        Matrix<int, 2> f2b(2, 2, {});
        Matrix<int, 2> f2v(2, 2, 4);
        assert((f2[0, 0] == 0 && f2b[1, 1] == 0 && f2v[0, 1] == 4));
        const auto &cf2v = f2v;
        assert((cf2v[0, 1] == 4 && cf2v.at(0, 1) == 4));

        // CTAD deduces T and D
        Matrix c3(1, 2, 3, 0);
        static_assert(same_as<decltype(c3), Matrix<int, 3>>);
        Matrix c2(2, 3, 5LL);
        static_assert(same_as<decltype(c2), Matrix<long long, 2>>);
        assert((c2[1, 2] == 5LL));
        Matrix c_copy(c3);
        static_assert(same_as<decltype(c_copy), Matrix<int, 3>>);
        Matrix d_copy(mat);
        static_assert(same_as<decltype(d_copy), Matrix<int>>);
        assert((d_copy[0, 1, 2] == 7));

        // Higher dimensions
        Matrix<int> m6(1, 2, 1, 2, 1, 2, {});
        assert(m6.s.size() == 6);
        m6[0, 1, 0, 1, 0, 1] = 11;
        assert((m6[0, 1, 0, 1, 0, 1] == 11));

        // matrix_mul with both Matrix<T> and Matrix<T, 2>
        Matrix<long long> fib_dyn(2, 2, {});
        fib_dyn[0, 0] = fib_dyn[0, 1] = fib_dyn[1, 0] = 1;
        auto r_dyn = mat_pow(fib_dyn, 10);
        cout << r_dyn[0, 1] << ' ';

        Matrix<long long, 2> fib_fix(2, 2);
        fib_fix[0, 0] = fib_fix[0, 1] = fib_fix[1, 0] = 1;
        auto r_fix = mat_pow(fib_fix, 10);
        cout << r_fix[0, 1] << '\n';

        static_assert(sizeof(Matrix<int>) ==
                      sizeof(vector<size_t>) + sizeof(vector<int>));
        static_assert(sizeof(Matrix<int, 2>) ==
                      sizeof(array<size_t, 2>) + sizeof(vector<int>));
--- out
[[[0, 0, 0], [0, 0, 7]]]
[[0, 3], [0, 0]]
[0, 0, 9]
[]
55 55
