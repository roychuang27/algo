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
