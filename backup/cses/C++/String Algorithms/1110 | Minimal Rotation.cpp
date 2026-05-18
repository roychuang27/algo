#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
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

void solution() {
        string S; cin >> S;
        int N = SZ(S);
        string T = S + S;
        int i = 0, ans = 0;
        while (i < N) {
                ans = i;
                int j = i + 1, k = i;
                while (j < 2*N and T[k] <= T[j]) {
                        if (T[k] < T[j])
                                k = i;
                        else
                                k++;
                        j++;
                }
                while (i <= k) {
                        i += j - k;
                }
        }
        cout << T.substr(ans, N) << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
