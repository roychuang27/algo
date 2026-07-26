#include <iostream>
#include <map>
#include <vector>
#ifdef LOCAL
#define test(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define testv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

void solution() {
        int N;
        cin >> N;
        vector<map<int, int>> trie(N+1);
        vector<vector<int>> idx(N+1);
        vector<int> pos(N+1);
        int it = 1;
        pos[0] = 0;

        for (int i = 1; i <= N; i++) {
                int x, y;
                cin >> x >> y;
                if (trie[pos[x]][y] == 0) {
                        trie[pos[x]][y] = it;
                        pos[i] = it;
                        idx[it].emplace_back(i);
                        it++;
                } else {
                        pos[i] = trie[pos[x]][y];
                        idx[pos[i]].emplace_back(i);
                }
        }

        const auto dfs = [&](this auto&& self, int cur) -> void {
                test(cur);
                for (auto& v : idx[cur]) cout << v << ' ';
                for (auto& [key, value] : trie[cur]) {
                        self(value);
                }
        };

        dfs(0);
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
