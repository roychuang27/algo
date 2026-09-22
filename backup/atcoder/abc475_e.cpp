#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#ifdef LOCAL
#define dbg(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define dbgv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define dbg(...) 39
#define dbgv(...) 39
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
template<typename T> struct CORDCOMP { vector<T> v; CORDCOMP(vector<T> x) : v(std::move(x)) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); } int operator()(const T& x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); } };
template<class T> T square(T a) { return a * a; }
template<class T> bool chmin(T &a,T b) { if (b < a) { a = b; return 1; } else return 0; }
template<class T> bool chmax(T &a,T b) { if (a < b) { a = b; return 1; } else return 0; }
template<class T, class U> auto vec(size_t n, U value) { return std::vector<T>(n, value); }
template<class T, class... Args> auto vec(size_t n, Args... args) { return std::vector(n, vec<T>(args...)); }
template<class T, size_t n> auto arr(T value) { array<T, n> res; res.fill(value); return res; }
using lli = long long int;

class TRIE {
    public:
        int N, it;
        vector<array<int, 2>> t;
        vector<int> child_sz;

        TRIE(int _N) : N(_N), it(1), t(N+1, arr<int, 2>(-1)), child_sz(N+1, 0) {}

        void insert(vector<int> &v) {
                int cur = 0;
                for (int c : v) {
                        assert(cur != -1);
                        if (t[cur][c] == -1) {
                                assert(it < N);
                                t[cur][c] = it++;
                        }
                        cur = t[cur][c];
                        child_sz[cur]++;
                }
        }

        void remove(vector<int> &v) {
                int cur = 0;
                for (int c : v) {
                        assert(cur != -1);
                        cur = t[cur][c];
                        child_sz[cur]--;
                }
        }

        int count(vector<int> &v) {
                int res = 0;
                int cur = 0;
                for (int c : v) {
                        assert(cur != -1);
                        if (c == 0 and t[cur][1] != -1)
                                res += child_sz[t[cur][1]];
                        cur = t[cur][c];
                }
                res += child_sz[cur];
                return res;
        }
};

void precompute() {
}

void solve() {
        int N, M, K;
        cin >> N >> M >> K;
        string T;
        cin >> T;
        auto convert = [&](string &s) -> vector<int> {
                vector<int> res(K, 0);
                for (int i = 0; i < K; i++) {
                        if (s[i] == T[i]) res[i] = 1;
                }
                return res;
        };

        vector<vector<int>> v(N);
        for (int i = 0; i < N; i++) {
                string s;
                cin >> s;
                v[i] = convert(s);
        }

        int Q;
        cin >> Q;
        TRIE trie((N + Q) * K);
        for (auto &s : v) trie.insert(s);

        for (int _ = 0; _ < Q; _++) {
                int i, j;
                cin >> i >> j;
                i--;
                j--;
                trie.remove(v[i]);
                v[i][j] ^= 1;
                trie.insert(v[i]);
                int cnt = trie.count(v[i]);
                dbg(cnt);
                dbgv(v[i]);
                if (cnt <= M and *max_element(ALL(v[i])) > 0) {
                        cout << "Yes\n";
                } else {
                        cout << "No\n";
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        precompute();
        solve();
        return 0;
}
