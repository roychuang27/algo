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
        string S;
        cin >> S;
        lli cnt = 0;
        int N = S.size();
        for (int i = 0; i < N; i++) {
                int c = 0;
                int l = i, r = i;
                while (l >= 0 and r < N) {
                        if (S[l] != S[r]) {
                                if (c) break;
                                else c = 1;
                        }
                        cnt++;
                        l--;
                        r++;
                }
                l = i, r = i+1;
                c = 0;
                while (l >= 0 and r < N) {
                        if (S[l] != S[r]) {
                                if (c) break;
                                else c = 1;
                        }
                        cnt++;
                        l--;
                        r++;
                }
        }
        cout << cnt << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
