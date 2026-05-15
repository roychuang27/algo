/*
 * Submission ID: 16823408
 * Problem: Counting Patterns
 * Link: https://cses.fi/problemset/task/2103
 */

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <vector>
#ifdef LOCAL
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
 
constexpr int MAXN = 5e5 + 10;
 
void solution() {
        // Aho Corasick
        vector<vector<int>> ac(MAXN, vector<int> (26, -1));
        vector<int> fail(MAXN, 0);
        vector<bool> is_end(MAXN, 0);
        vector<int> str_to_id(MAXN);
        int it = 0; // point to the end of the trie
        const auto insert = [&](string &t, int str_id) -> void { // build trie
                int cur = 0;
                for (const char c : t) {
                        int j = c - 'a';
                        if (ac[cur][j] == -1) {
                                ac[cur][j] = ++it;
                        }
                        cur = ac[cur][j];
                }
                is_end[cur] = 1;
                str_to_id[str_id] = cur;
        };
        vector<vector<int>> dfs_adj(MAXN);
        const auto bfs = [&]() -> void {
                queue<int> qu;
                for (int j = 0; j < 26; j++) {
                        if (ac[0][j] != -1) {
                                qu.push(ac[0][j]);
                                dfs_adj[0].eb(ac[0][j]);
                        } else {
                                ac[0][j] = 0; // fail edge
                        }
                }
                while (not qu.empty()) {
                        int cur = qu.front(); qu.pop();
                        for (int j = 0; j < 26; j++) {
                                int &nxt = ac[cur][j];
                                if (nxt != -1) {
                                        int link_to = ac[fail[cur]][j];
                                        fail[nxt] = link_to;
                                        dfs_adj[link_to].eb(nxt);
                                        qu.push(nxt);
                                } else {
                                        nxt = ac[fail[cur]][j];
                                }
                        }
                }
        };
        vector<int> dp(MAXN, 0);
        const function<void(int)> dfs = [&](int cur) -> void {
                for (const int &nxt : dfs_adj[cur]) {
                        dfs(nxt);
                        dp[cur] += dp[nxt];
                }
        };
        const auto traverse = [&](string &t) -> void {
                int cur = 0;
                for (const char &c : t) {
                        cur = ac[cur][c-'a'];
                        dp[cur]++;
                }
        };
        // Main
        string S; cin >> S;
        int K; cin >> K;
        for (int i = 0; i < K; i++) {
                string t; cin >> t;
                insert(t, i);
        }
        bfs();
        traverse(S);
        dfs(0);
        for (int i = 0; i < K; i++) {
                cout << dp[str_to_id[i]] << '\n';
        }
}
 
int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}