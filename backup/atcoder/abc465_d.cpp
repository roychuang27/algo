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
        lli X, Y, K;
        cin >> X >> Y >> K;
        map<lli, int> mp;
        int cnt = 0;
        while (Y >= 1) {
                mp[Y] = cnt++;
                test(Y, mp[Y]);
                Y /= K;
        }
        mp[0] = cnt;
        int cnt2 = 0;
        while (mp.find(X) == mp.end()) {
                X /= K;
                cnt2++;
                test(X);
        }
        cout << mp[X] + cnt2 << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        int T;
        cin >> T;
        while(T--)
                solution();
        return 0;
}
