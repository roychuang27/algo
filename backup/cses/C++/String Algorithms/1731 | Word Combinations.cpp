#pragma GCC optimize("Ofast")
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#define fastio cin.tie(0)->sync_with_stdio(false)
#define SZ(x) ((int) x.size())

using namespace std;
typedef long long int lli;

lli dp[1000006] = {0};

const int mod = 1e9 + 7;

struct TRIE {
    int graph[1000006][26];
    bool is_end[1000006];
    int nodes;

    void init() {
        memset(graph, -1, sizeof(graph));
        memset(is_end, 0, sizeof(is_end));
        nodes = 1;
    }
    
    bool existnxt(int id, int c) {
        return graph[id][c] != -1;
    }

    int getnxt(int id, int c) {
        if (existnxt(id, c)) return graph[id][c];
        nodes++;
        graph[id][c] = nodes - 1;
        return graph[id][c];
    }

    void insert(string s) {
        int id = 0;
        for (char c : s) {
            c -= 'a';
            id = getnxt(id, c);
        }
        is_end[id] = 1;
    }

    void traversal(string s, int origin) {
        int idx = origin;
        int id = 0;
        for (int i = origin; i < SZ(s); i++) {
            char c = s[i];
            c -= 'a';
            if (is_end[id]) {
                dp[idx] += dp[origin];
                if (dp[idx] >= mod) dp[idx] %= mod;
            }
            if (existnxt(id, c)){
                id = getnxt(id, c);
                idx++;
            } else {
                return;
            }
        }
        if (is_end[id]) {
            dp[idx] += dp[origin];
            if (dp[idx] >= mod) dp[idx] %= mod;
        }
    }
} trie;

void solve() {
    trie.init();
    string s;
    cin >> s;
    int K; cin >> K;
    for (int i = 0; i < K; i++) {
        string ss; cin >> ss;
        trie.insert(ss);
    }
    int N = SZ(s);
    dp[0] = 1;

    for (int i = 0; i < N; i++) {
        trie.traversal(s, i);
    }
    
    // for (int i = 0; i <= N; i++) cout << dp[i] << ' ';

    cout << dp[N] << '\n';
}

int main () {
    fastio;
    solve();
    return 0;
}