#include <bits/stdc++.h>
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

void precompute() {
}

void solve() {
        int N, Q;
        cin >> N >> Q;
        vector<int> A(N, 0);
        set<int> idxs;

        int ans = 0;
        for (int _ = 0; _ < Q; _++) {
                int typ;
                cin >> typ;
                if (typ == 1) {
                        int x;
                        cin >> x;
                        x--;
                        ans ^= A[x];
                        A[x]++;
                        ans ^= A[x];
                        if (A[x] == 1) idxs.insert(x);
                } else {
                        for (auto i : idxs) {
                                ans ^= A[i];
                                A[i]--;
                                ans ^= A[i];
                        }
                        std::erase_if(idxs, [&](int x) { return A[x] == 0; });
                }
                cout << ans << '\n';
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}


