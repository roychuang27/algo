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

void solution() {
        int N, K;
        cin >> N >> K;
        string S;
        cin >> S;
        vector<int> P(N+1);
        P[0] = 0;
        for (int i = 0; i < N; i++) { P[i+1] = P[i] + (S[i] == 'o'); }

        auto f = [&](double x) -> bool {
                vector<double> mn(N);
                double pre = 0;

                int i = 0;
                for (; P[i+1] < K; i++) {
                        if (S[i] == 'o') pre += (1 - x);
                        else pre -= x;
                        if (i == 0) mn[0] = pre;
                        else mn[i] = min(mn[i-1], pre);
                }
                int j = -1;
                for (; i < N; i++) {
                        if (S[i] == 'o') pre += (1 - x);
                        else pre -= x;
                        mn[i] = min(mn[i-1], pre);
                        while (P[i+1] - P[j+1] >= K) j++;
                        if (j == 0) {
                                if (pre >= 0) return true;
                        } else {
                                if (pre - mn[j-1] >= 0) return true;
                        }
                }
                return false;
        };

        double l = 0, r = 1;
        for (int _ = 0; _ < 100; _++) {
                double m = (l + r) / 2;
                // test(m, f(m));

                if (f(m)) l = m;
                else r = m;
        }

        cout << l << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        cout << fixed << setprecision(7);
        solution();
        return 0;
}
