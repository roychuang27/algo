#include <algorithm>
#include <iostream>
#include <map>
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
        int N, K, M;
        cin >> N >> K >> M;
        vector<pair<int, int>> vec(N);
        for (auto &[c, v] : vec) cin >> c >> v;
        sort(ALL(vec), [](auto &p1, auto &p2) {
                return p1.sec > p2.sec;
        });
        lli ans = 0;
        int cnt = 0;
        map<int, int> exist;
        int i = 0;
        vector<int> vec2;
        while (cnt < M) {
                auto [c, v] = vec[i++];
                if (exist[c]) {
                        vec2.emplace_back(v);
                } else {
                        exist[c] = 1;
                        ans += v;
                        cnt++;
                }
        }
        while (i < N) {
                auto [c, v] = vec[i++];
                vec2.emplace_back(v);
        }
        sort(rALL(vec2));
        for (int j = 0; j < K-M; j++) {
                ans += vec2[j];
        }
        cout << ans << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
