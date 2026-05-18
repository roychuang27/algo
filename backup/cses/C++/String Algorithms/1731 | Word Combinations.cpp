#include <algorithm>
#include <cstring>
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
 
const int MOD = 1e9 + 7;
 
void solution() {
        // TRIE
        struct TRIE_NODE {
                int idx_of_nxt[26];
                bool is_end;
                TRIE_NODE() {
                        memset(idx_of_nxt, -1, sizeof(idx_of_nxt));
                        is_end = 0;
                }
                int& operator[] (int c) {
                        return idx_of_nxt[c];
                }
        };
        vector<TRIE_NODE> trie;
        int it = 0; // inclusive
        trie.eb(TRIE_NODE());
        const function<void(string&)> insert = [&](string &t) -> void {
                int cur = 0;
                for (const char c : t) {
                        int j = c - 'a';
                        if (trie[cur][j] == -1) {
                                trie[cur][j] = ++it;
                                trie.eb(TRIE_NODE());
                        }
                        cur = trie[cur][j];
                }
                trie[cur].is_end = 1;
        };
        // Input
        string S; cin >> S;
        int K; cin >> K;
        while (K-->0) {
                string t; cin >> t;
                insert(t);
        }
        int N = SZ(S);
        vector<lli> dp(N+1, 0);
        dp[0] = 1;
        // origin is 0-based
        // origin + depth convert it to 1-based
        const function<void(int, int, int)> dfs = [&](int origin, int depth, int cur) {
                if (cur == -1) {
                        return;
                }
                if (trie[cur].is_end) {
                        dp[origin + depth] = (dp[origin] + dp[origin + depth]) % MOD;
                }
                if (origin + depth < N) {
                        dfs(origin, depth+1, trie[cur][ S[origin+depth]-'a' ]);
                }
        };
        for (int i = 0; i < N; i++) dfs(i, 0, 0);
        cout << dp[N] << '\n'; // 1-based
}
 
int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
