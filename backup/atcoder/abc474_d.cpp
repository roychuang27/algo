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
        int N;
        cin >> N;
        vector<int> A(N), B(N);
        for (auto &i : A) cin >> i;
        for (auto &i : B) cin >> i;
        vector<int> diff(N);
        bool f = 0;
        for (int i = 0; i < N; i++) {
                diff[i] = A[i] - B[i];
                if (diff[i] > 0) f = 1;
        }
        if (!f) {
                cout << "No\n";
                return 0;
        }
        cout << "Yes\n";
        for (int i = 0; i < N; i++) {
                if (diff[i] > 0) cout << (lli) 1e18 << ' ';
                else cout << 1 << ' ';
        }
        cout << '\n';
        return 0;
}



