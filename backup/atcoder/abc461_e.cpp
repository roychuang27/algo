#include <bits/stdc++.h>
#include <atcoder/fenwicktree>
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
        int N, Q;
        cin >> N >> Q;
        vector f(2, atcoder::fenwick_tree<int> (Q+1));
        vector last(2, vector<int> (N+1, 0));
        for (int i = 0; i <= N; i++) last[0][i] = -1;

        lli b = 0;
        for (int i = 1; i <= Q; i++) {
                int t, x;
                cin >> t >> x;
                t--;

                if (last[t][x] == -1) {
                        b += N;
                } else {
                        int cnt = f[1-t].sum(last[t][x], i);
                        if (t == 1) cnt = -cnt;
                        b += cnt;
                        f[t].add(last[t][x], -1);
                }
                f[t].add(i, 1);
                last[t][x] = i;
                cout << b << '\n';
        }
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
