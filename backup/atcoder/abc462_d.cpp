#include <atcoder/fenwicktree>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
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

void solution() {
        int N, D;
        cin >> N >> D;
        vector<pair<int, int>> v;
        for (int _ = 0; _ < N; _++) {
                int s, t;
                cin >> s >> t;
                v.emplace_back(s, t);
        }
        sort(ALL(v));
        int i = 0;
        atcoder::fenwick_tree<int> fenwick(2e6 + 1);
        lli ans = 0;
        for (int s = 1; s <= 1e6; s++) {
                while (i < N and v[i].fst == s) {
                        fenwick.add(v[i].sec, 1);
                        i++;
                }
                lli k = fenwick.sum(s+D, 2e6+1);
                if (k) {
                        ans += k * (k - 1);
                }
        }
        cout << ans / 2 << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
