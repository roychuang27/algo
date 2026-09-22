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
#define SZ(x) ((size_t) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        int N, M;
        cin >> N >> M;
        vector<int> A(N), B(N-1);
        for (auto &i : A) cin >> i;
        for (auto &i : B) cin >> i;
        vector<int> C(N);
        C[0] = 0;
        lli ans1 = A[0] != 0;
        for (int i = 0; i < N-1; i++) {
                C[i+1] = C[i] != B[i];
                ans1 += (A[i+1] != C[i+1]);
        }
        dbgv(C);
        C[0] = 1;
        lli ans2 = A[0] != 1;
        for (int i = 0; i < N-1; i++) {
                C[i+1] = C[i] != B[i];
                ans2 += (A[i+1] != C[i+1]);
        }
        dbgv(C);
        dbg(ans1, ans2);
        cout << min(ans1, ans2);
        return 0;
}



