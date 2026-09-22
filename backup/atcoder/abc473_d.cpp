#include <bits/stdc++.h>
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

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int N, K;
        cin >> N >> K;

        vector<int> seq;
        vector<vector<int>> vec;

        auto f = [&](this auto &&self, int i, int k) -> void {
                // testv(seq);
                if (k < 0) {
                        return;
                }
                if (i == N) {
                        if (k % i) {
                                return;
                        } else {
                                seq.emplace_back(k / i);
                                vec.emplace_back(seq);
                                seq.pop_back();
                                return;
                        }
                }
                for (int m = 0; m <= k / i; m++) {
                        seq.emplace_back(m);
                        self(i+1, k-m*i);
                        seq.pop_back();
                }
        };

        f(1, K);
        // for (auto v : vec) testv(v);

        for (auto v : vec) {
                for (auto i : v) cout << i << ' ';
                cout << '\n';
        }
        
        return 0;
}

