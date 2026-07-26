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
        int H, W;
        cin >> H >> W;
        vector<string> v(H);
        for (auto &i : v) cin >> i;
        int a = 0, b = H, c = 0, d = W;
        for (int i = 0; i < H; i++) {
                bool flag = 1;
                for (int j = 0; j < W; j++) {
                        if (v[i][j] == '#') {
                                flag = 0;
                                break;
                        }
                }
                if (!flag) break;
                a++;
        }
        for (int i = H-1; i >= 0; i--) {
                bool flag = 1;
                for (int j = 0; j < W; j++) {
                        if (v[i][j] == '#') {
                                flag = 0;
                                break;
                        }
                }
                if (!flag) break;
                b--;
        }
        for (int i = 0; i < W; i++) {
                bool flag = 1;
                for (int j = 0; j < H; j++) {
                        if (v[j][i] == '#') {
                                flag = 0;
                                break;
                        }
                }
                if (!flag) break;
                c++;
        }
        for (int i = W-1; i >= 0; i--) {
                bool flag = 1;
                for (int j = 0; j < H; j++) {
                        if (v[j][i] == '#') {
                                flag = 0;
                                break;
                        }
                }
                if (!flag) break;
                d--;
        }
        for (int i = a; i < b; i++) {
                for (int j = c; j < d; j++) {
                        cout << v[i][j];
                }
                cout << '\n';
        }
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
