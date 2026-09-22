#include <bits/stdc++.h>
#include <atcoder/dsu>
#ifdef LOCAL
#define test(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define testv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
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

constexpr int L = 1e6;
array<vector<int>, L+1> factors;

void precompute_factors() {
        for (int i = 1; i <= L; i++) {
                for (int j = i; j <= L; j += i) {
                        factors[j].emplace_back(i);
                }
        }
}

void solution() {
        int N;
        cin >> N;

        vector<vector<int>> by_weight(L+1);

        for (int i = 0; i < N; i++) {
                int a;
                cin >> a;
                for (auto j : factors[a]) by_weight[j].emplace_back(i);
        }

        atcoder::dsu uf(L+1);

        lli ans = 0;
        for (int w = L; w >= 0; w--) {
                for (int i = 0, j = 1; j < by_weight[w].size(); i++, j++) {
                        int a = by_weight[w][i], b = by_weight[w][j];
                        if (!uf.same(a, b)) {
                                ans += w;
                                uf.merge(a, b);
                        }
                }
        }

        cout << ans << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        precompute_factors();
        solution();
        return 0;
}
