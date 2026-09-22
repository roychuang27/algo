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

const int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
const int dy[] = {0, 0, 1, -1, 1, 1, -1, -1};

int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        int H, W;
        cin >> H >> W;
        vector<string> g(H);
        for (auto &s : g) {
                cin >> s;
        }

        auto is_in = [&](int i, int j) -> bool {
                return -1 < i and i < H and -1 < j and j < W;
        };

        vector<string> g2 = g;
        for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
                if (g[i][j] == '#') {
                        g2[i][j] = '.';
                        continue;
                } else {
                        for (int k = 0; k < 8; k++) {
                                int ni = i + dy[k], nj = j + dx[k];
                                if (is_in(ni, nj)) {
                                        if (g[ni][nj] == '#') g2[i][j] = '#';
                                }
                        }
                }
        }
        g = std::move(g2);

        vector dis(H, vector<int> (W, -1));
        queue<tuple<int, int, int>> qu;
        for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                        if (g[i][j] == '#') {
                                qu.emplace(i, j, 0);
                        }
                }
        }

        while (!qu.empty()) {
                auto [i, j, d] = qu.front();
                qu.pop();
                if (dis[i][j] != -1) continue;
                dis[i][j] = d;
                for (int k = 0; k < 8; k++) {
                        int ni = i + dy[k], nj = j + dx[k];
                        if (is_in(ni, nj) and dis[ni][nj] == -1) {
                                qu.emplace(ni, nj, d+1);
                        }
                }
        }

        for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                        if (dis[i][j] == -1) cout << g[i][j];
                        else cout << (dis[i][j] % 2 ? '#' : '.');
                }
                cout << '\n';
        }
        return 0;
}


