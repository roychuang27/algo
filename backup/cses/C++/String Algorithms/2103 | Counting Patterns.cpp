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
 
struct Aho_Corasick {
        vector<vector<int>> trie;
        vector<int> fail;
        vector<bool> is_end;
        vector<int> str_to_id;
        vector<vector<int>> dfs_adj;
        vector<int> dp;
        int it; // point to the end of the trie

        Aho_Corasick(int MAXN) :
                trie(MAXN, vector<int> (26, -1)),
                fail(MAXN, 0),
                is_end(MAXN, 0),
                str_to_id(MAXN),
                dfs_adj(MAXN),
                dp(MAXN, 0),
                it(0)
        {}

        void insert(string &t, int str_id) { // build trie
                int cur = 0;
                for (const char c : t) {
                        int j = c - 'a';
                        if (trie[cur][j] == -1) {
                                trie[cur][j] = ++it;
                        }
                        cur = trie[cur][j];
                }
                is_end[cur] = 1;
                str_to_id[str_id] = cur;
        }

        void bfs() {
                queue<int> qu;
                for (int j = 0; j < 26; j++) {
                        if (trie[0][j] != -1) {
                                qu.push(trie[0][j]);
                                dfs_adj[0].eb(trie[0][j]);
                        } else {
                                trie[0][j] = 0; // fail edge
                        }
                }
                while (not qu.empty()) {
                        int cur = qu.front(); qu.pop();
                        for (int j = 0; j < 26; j++) {
                                int &nxt = trie[cur][j];
                                if (nxt != -1) {
                                        int link_to = trie[fail[cur]][j];
                                        fail[nxt] = link_to;
                                        dfs_adj[link_to].eb(nxt);
                                        qu.push(nxt);
                                } else {
                                        nxt = trie[fail[cur]][j];
                                }
                        }
                }
        }

        void dfs(int cur) {
                for (const int &nxt : dfs_adj[cur]) {
                        dfs(nxt);
                        dp[cur] += dp[nxt];
                }
        }

        void traverse(string &t) {
                int cur = 0;
                for (const char &c : t) {
                        cur = trie[cur][c-'a'];
                        dp[cur]++;
                }
        }
};
 
void solution() {
        Aho_Corasick ac(5e5 + 10);
        string S; cin >> S;
        int K; cin >> K;
        for (int i = 0; i < K; i++) {
                string t; cin >> t;
                ac.insert(t, i);
        }
        ac.bfs();
        ac.traverse(S);
        ac.dfs(0);
        for (int i = 0; i < K; i++) {
                cout << ac.dp[ac.str_to_id[i]] << '\n';
        }
}
 
int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
