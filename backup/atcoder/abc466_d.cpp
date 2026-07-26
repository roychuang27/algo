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
        int N, M;
        cin >> N >> M;
        vector<int> row(N, -1), col(N, -1);

        int cnt = 0;
        auto f = [&](int r, int c) -> bool {
                if (r == -1 or c == -1) return 0;
                if (row[r] == -1 or col[c] == -1) return 0;
                // test(r, row[r], col[row[r]], c, col[c], row[col[c]])
                return (row[r] == c and col[row[r]] == r) and (col[c] == r and row[col[c]] == c);
        };
        for (int _ = 0; _ < M; _++) {
                int r, c;
                cin >> r >> c;
                r--;
                c--;
                if (!f(r, c)) {
                        if (f(r, row[r])) cnt--;
                        if (f(col[c], c)) cnt--;
                        test(f(r, row[r]));
                        test(f(col[c], c));
                        row[r] = c;
                        col[c] = r;
                        cnt++;
                }
                test(cnt);
        }
        cout << cnt << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
