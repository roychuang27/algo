#include <algorithm>
#include <functional>
#include <iostream>
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

vector<int> KMP(string s) {
        int N = SZ(s);
        vector<int> pi(N);
        pi[0] = 0;
        for (int i = 1; i < N; i++) {
                int j = pi[i - 1];
                while (j > 0 and s[i] != s[j]) j = pi[j - 1];
                if (s[i] == s[j]) j++;
                pi[i] = j;
        }
        return pi;
}
void solution() {
        string S; cin >> S;
        int N = SZ(S);
        vector<int> pi = KMP(S);
        vector<int> ans;
        for (int k = pi[N-1]; k > 0; k = pi[k-1]) ans.eb(N - k);
        ans.eb(N);
        printv(ans);
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
