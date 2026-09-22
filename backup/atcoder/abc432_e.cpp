#include <bits/stdc++.h>
#include <atcoder/fenwicktree.hpp>
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
#define SZ(x) ((size_t) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

constexpr int MAXV = 5e5 + 10;

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        
        int N, Q;
        cin >> N >> Q;
        atcoder::fenwick_tree<lli> fwt(MAXV), cnt(MAXV);
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
                cin >> A[i];
                fwt.add(A[i], A[i]);
                cnt.add(A[i], 1);
        }

        for (int _ = 0; _ < Q; _++) {
                int qt;
                cin >> qt;
                if (qt == 1) {
                        int x, y;
                        cin >> x >> y;
                        x--;
                        fwt.add(A[x], -A[x]);
                        cnt.add(A[x], -1);
                        A[x] = y;
                        fwt.add(A[x], A[x]);
                        cnt.add(A[x], 1);
                }
                if (qt == 2) {
                        int l, r;
                        cin >> l >> r;
                        if (l > r) {
                                cout << (lli) l * N << '\n';
                        } else {
                                cout << cnt.sum(0, l) * l + fwt.sum(l, r) + cnt.sum(r, MAXV) * r << '\n';
                        }
                }
        }
        
        return 0;
}


