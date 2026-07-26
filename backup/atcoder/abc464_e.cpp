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
        int H, W, Q;
        cin >> H >> W >> Q;
        vector<vector<int>> A(H, vector<int> (W, 0));
        vector<char> xs = {'A'};

        for (int i = 1; i <= Q; i++) {
                int r, c;
                char x;
                cin >> r >> c >> x;
                A[r-1][c-1] = i;
                xs.emplace_back(x);
        }

        for (int i = H-1; i >= 0; i--) {
                for (int j = W-1; j >= 0; j--) {
                        if (i != 0) A[i-1][j] = max(A[i-1][j], A[i][j]);
                        if (j != 0) A[i][j-1] = max(A[i][j-1], A[i][j]);
                }
        }

        for (int i = 0; i < H; i++) { for (int j = 0; j < W; j++) cout << xs[A[i][j]]; cout << '\n'; }
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
