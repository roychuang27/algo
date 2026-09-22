#include <bits/stdc++.h>
#include <atcoder/lazysegtree.hpp>
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
#define SZ(x) ((int) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

namespace lazy {
        lli op(lli a, lli b) { return min(a, b); }
        lli e() { return 1e18; }
        lli mapping(lli f, lli x) { return f + x; }
        lli composition(lli f, lli g) { return f + g; }
        lli id() { return 0LL; }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);

        int N;
        string S;
        cin >> N >> S;
        
        vector<lli> pre(N);
        pre[0] = (S[0] == 'A') ? 1 : -1;
        for (int i = 1; i < N; i++) pre[i] = pre[i-1] + ( (S[i] == 'A') ? 1 : -1 );

        atcoder::lazy_segtree<lli, lazy::op, lazy::e, lli, lazy::mapping, lazy::composition, lazy::id> seg(pre);

        int Q;
        cin >> Q;
        for (int _ = 0; _ < Q; _++) {
                int type;
                cin >> type;

                if (type == 1) {
                        int i;
                        char c;
                        cin >> i >> c;
                        i--;
                        lli delta = 0;
                        if (S[i] == 'A') delta = -1;
                        else delta = 1;
                        S[i] = c;
                        if (S[i] == 'A') delta++;
                        else delta--;
                        if (delta != 0) seg.apply(i, N, delta);
                }

                if (type == 2) {
                        int l, r;
                        cin >> l >> r;
                        l--;
                        if (seg.prod(l, r) >= ( l == 0 ? 0LL : seg.get(l-1) )) {
                                cout << "Yes\n";
                        } else {
                                cout << "No\n";
                        }
                }
        }
        return 0;
}


