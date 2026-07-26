#include <bits/stdc++.h>
#include <atcoder/modint>
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

using mint = atcoder::modint998244353;

void solution() {
        int N;
        cin >> N;
        vector<int> A(N);
        for (auto &i : A) cin >> i;
        vector<mint> pre(N+1);
        pre[0] = 0;
        for (int i = 1; i <= N; i++) pre[i] = A[i-1] + pre[i-1];
        vector<mint> H(N+1);
        // H_i = 1 / 1 + 1 / 2 + ... + 1 / i
        H[0] = 0;
        for (int i = 1; i <= N; i++) H[i] = H[i-1] + mint(1) / i;

        mint ans = 0;
        for (int i = 1; i <= N; i++) {
                ans += pre[i] * (H[i] - H[N-i]);
        }
        cout << ans.val() << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
