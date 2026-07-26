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
        int N;
        string S;
        cin >> N >> S;
        vector<lli> dpS(N+1, 0), dpR(N+1, 0);
        vector<lli> X(N), Y(N);
        for (auto &i : X) cin >> i;
        Y[0] = 0;
        for (int i = 1; i < N; i++) cin >> Y[i];
        for (int i = 1; i <= N; i++) {
                if (S[i-1] == 'S') {
                        dpS[i] = max(dpS[i-1], dpR[i-1] + Y[i-1]);
                        dpR[i] = max(dpS[i-1], dpR[i-1]) - X[i-1];
                } else {
                        dpS[i] = max(dpS[i-1], dpR[i-1] + Y[i-1]) - X[i-1];
                        dpR[i] = max(dpR[i-1], dpS[i-1]);
                }
        }
        cout << max(dpS[N], dpR[N]) << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--)
                solution();
        return 0;
}
