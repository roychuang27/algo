#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
#ifdef LOCAL
#define test(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define testv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using i64 = int64_t;
using i32 = int32_t;
using namespace std;

class PersistentSegTree {
    private:
        struct S {
                i64 sum = 0;
                int l = -1, r = -1;
        };

        vector<S> t;
        int N;
        int timer = 1;

        S op(int l, int r) { return S{t[l].sum + t[r].sum, l, r}; }

        int build(int tl, int tr, const vector<i64> &arr) {
                if (tl == tr) {
                        t[timer] = {arr[tl], -1, -1};
                        return timer++;
                }

                int mid = (tl + tr) / 2;
                t[timer] = op(build(tl, mid, arr), build(mid+1, tr, arr));

                return timer++;
        }

        int set(int id, int pos, int val, int tl, int tr) {
                assert(id != -1);
                if (tl == tr) {
                        t[timer] = {val, 0, 0};
                        return timer++;
                }

                int mid = (tl + tr) / 2;
                if (pos <= mid) {
                        t[timer] = op(set(t[id].l, pos, val, tl, mid), t[id].r);
                } else {
                        t[timer] = op(t[id].l, set(t[id].r, pos, val, mid+1, tr));
                }

                return timer++;
        }

        i64 prod(int id, int ql, int qr, int tl, int tr) {
                assert(id != -1);
                if (qr < tl or tr < ql) {
                        return 0LL;
                }

                if (ql <= tl and tr <= qr) {
                        return t[id].sum;
                }

                int mid = (tl + tr) / 2;
                return prod(t[id].l, ql, qr, tl, mid) + prod(t[id].r, ql, qr, mid+1, tr);
        }

    public:
        PersistentSegTree(int N, int MAXN) : t(MAXN), N(N) {}
        int build(const vector<i64> &arr) { return build(0, N-1, arr); }
        int set(int root, int pos, i64 val) { return set(root, pos, val, 0, N-1); }
        i64 prod(int root, int l, int r) { return prod(root, l, r, 0, N-1); }

        int add_copy(int root) {
                t[timer] = t[root];
                return timer++;
        }
};

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<i64> A(N);
        for (auto &x : A) cin >> x;

        PersistentSegTree st(N, 4*N+Q*(2+__lg(N)));
        vector<int> roots = {st.build(A)};

        for (int _ = 0; _ < Q; _++) {
                int op, k;
                cin >> op >> k;
                k--;

                if (op == 1) {
                        int pos;
                        i64 val;
                        cin >> pos >> val;
                        pos--;
                        roots[k] = st.set(roots[k], pos, val);
                }
                if (op == 2) {
                        int l, r;
                        cin >> l >> r;
                        cout << st.prod(roots[k], l-1, r-1) << '\n';
                }
                if (op == 3) {
                        roots.push_back(st.add_copy(roots[k]));
                }
        }
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
