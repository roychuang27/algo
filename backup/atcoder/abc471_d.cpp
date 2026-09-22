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

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);

        int Q;
        lli V;
        cin >> Q >> V;

        multiset<lli> st;
        for (int _ = 0; _ < Q; _++) {
                int type;
                cin >> type;
                if (type == 1) {
                        lli t, w;
                        cin >> t >> w;
                        st.insert(t-w);
                } else {
                        lli t;
                        cin >> t;
                        if (st.begin() != st.end()) {
                                cout << min(-*st.begin() + t, V) << '\n';
                                st.erase(st.begin());
                        } else {
                                cout << -1 << '\n';
                        }
                }
        }

        return 0;
}



