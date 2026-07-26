#include <iostream>
#include <map>
#include <string>
#include <vector>
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
        int H, W, K;
        cin >> H >> W >> K;

        vector<vector<int>> row_sum(H+1, vector<int> (W+1, 0));
        for (int i = 1; i <= H; i++) {
                string s;
                cin >> s;
                for (int j = 0; j < W; j++) {
                        row_sum[i][j+1] = (s[j] == '1');
                }
        }
        for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) row_sum[i][j] += row_sum[i][j-1];

        lli ans = 0;
        for (int i = 1; i <= W; i++) {
                for (int j = i; j <= W; j++) {
                        if ((j - i + 1) * H < K) continue;
                        vector<int> mp((j-i+1)*H+1, 0);
                        int rect_sum = 0;
                        mp[0]++;
                        for (int l = 1; l <= H; l++) {
                                if (rect_sum + (j-i+1)*(H-l+1) < K) break;
                                rect_sum += row_sum[l][j] - row_sum[l][i-1];
                                if (rect_sum - K >= 0) ans += mp[rect_sum - K];
                                mp[rect_sum]++;
                        }
                }
        }

        cout << ans << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
