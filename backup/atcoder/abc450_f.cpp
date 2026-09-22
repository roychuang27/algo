#include <bits/stdc++.h>
#include <atcoder/modint.hpp>
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
#define SZ(x) ((size_t) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

using mint = atcoder::modint998244353;

namespace lazy {
        mint op(mint l, mint r) { return l + r; }
        mint e() { return mint(0); }
        mint mapping(mint f, mint x) { return f * x; }
        mint composition(mint f, mint g) { return f * g; }
        mint id() { return mint(1); }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        int N, M;
        cin >> N >> M;
        vector<pair<int, int>> edges(M);
        for (auto &[a, b] : edges) {
                cin >> a >> b;
                a--;
                b--;
        }
        sort(ALL(edges));

        atcoder::lazy_segtree<mint, lazy::op, lazy::e, mint, lazy::mapping, lazy::composition, lazy::id> seg(N);
        seg.set(0, 1);
        for (auto [a, b] : edges) {
                seg.apply(0, a, 2);
                seg.set(b, seg.get(b) + seg.prod(a, b+1));
                seg.apply(b+1, N, 2);
        }

        cout << seg.get(N-1).val() << '\n';
        
        return 0;
}

