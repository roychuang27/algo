/*
 * Submission ID: 15067306
 * Problem: De Bruijn Sequence
 * Link: https://cses.fi/problemset/task/1692
 */

#include <iostream>
#include <set>
#include <vector>

using namespace std;

const char cs[2] = {'0', '1'};

class deBruijn {
        public:
        int N;
        set<string> visited;
        vector<int> edge_weights;
        
        string res;
        
        void dfs(string cur) {
                for (int i = 0; i < 2; i++) {
                        string nxt = cur + cs[i];
                        if (visited.find(nxt) != visited.end()) continue;
                        
                        visited.insert(nxt);
                        dfs(nxt.substr(1));
                        edge_weights.emplace_back(i);
                }
        }

        deBruijn(int n): N(n) {
                string start = string(N-1, '0');
                
                dfs(start);
                
                for (const auto &k : edge_weights) {
                        res += cs[k];
                }
                res += start;
        }
};

int main() {
        cin.tie(0)->sync_with_stdio(0);
        int N; cin >> N;
        deBruijn d(N);
        cout << d.res << '\n';
}