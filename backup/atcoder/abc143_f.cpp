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
        int N;
        cin >> N;
        vector<int> A(N);
        for (auto &i : A) cin >> i;
        vector<lli> B(N + 1, 0), C(N + 1, 0);
        map<int, int> cnt;
        for (auto i : A) cnt[i]++;
        for (auto [a, b] : cnt) {
                B[b] += b;
                C[b]++;
        }

        for (int i = N-1; i >=0; i--) {
                B[i] += B[i+1];
                C[i] += C[i+1];
        }

        for (int k = 1; k <= N; k++) {
                int ans = 0;
                for (int cand = 1; cand <= N / k; cand++) {
                        if (cand * k <= N - (B[cand] - C[cand] * cand)) {
                                ans = max(ans, cand);
                        }
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


