#include <algorithm>
#include <atcoder/modint>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#ifndef ONLINE_JUDGE
#define test(...) do { cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((cerr << ' ' << args), ...); }(__VA_ARGS__)); cerr << endl; } while(0)
#define testv(x) do { cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) cerr << (_i++ ? ", " : "") << _e; cerr << "]" << endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define printv(x) { for (auto i : (x)) cout << i << ' '; cout << endl; }
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define rALL(x) rbegin(x), rend(x)
#define fst first
#define sec second

using namespace std;
using lli = long long int;
using mint = atcoder::modint998244353;

mint C(int n, int m) {
        mint res = 1;
        for (int i = n; i > n-m; i--) res *= i;
        for (int i = m; i > 0; i--) res /= i;
        return res;
}

void solution() {
        int N; cin >> N;
        vector<int> W(N);
        mint sum = 0;
        for (int i = 0; i < N; i++) {
                cin >> W[i];
                sum += W[i];
        }
        mint cnt_exist = 0;
        mint t = C(N-1, N/2);
        for (int j = N / 2; j <= N - 1; j++) {
                // cnt_exist += C(N-1, j);
                cnt_exist += t;
                t = t * (N-j-1) / (j+1);
        }
        cout << (sum * cnt_exist).val() << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
