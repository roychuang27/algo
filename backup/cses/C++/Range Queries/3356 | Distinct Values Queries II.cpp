#include <iostream>
#include <vector>
#include <map>
#include <set>

#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                                  \
        {                                          \
                for (auto i : x) cout << i << ' '; \
                cout << endl;                      \
        }
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

using namespace std;
using lli = long long int;

const int INF = 0x3f3f3f3f;
const int nodes_cnt_max = 2e5 + 10;
vector<int> l(nodes_cnt_max, -1);
vector<int> r(nodes_cnt_max, -1);
map<int, set<int>> mp;

struct ZKW {
        vector<lli> t = vector<lli>(nodes_cnt_max * 2);
        int N;

        void init(int arr_size) {
                N = arr_size;
                for (int i = 0; i <= 2 * N + 1; i++) t[i] = 0;
        }

        void printdbg() {
                cerr << "You are trying to print something" << endl;
                int l = N, r = 2 * N - 1;
                while (l <= r) {
                        for (int i = l; i <= r; i++) cerr << t[i] << ' ';
                        cerr << endl;
                        if (l % 2 == 1) l++;
                        if (r % 2 == 0) r--;
                        l /= 2;
                        r /= 2;
                }
        }

        void build() {
                for (int i = N; i < 2 * N; i++) {
                        t[i] = l[i - N];
                }
                for (int i = N - 1; i >= 1; i--) {
                        t[i] = max(t[i * 2], t[i * 2 + 1]);
                }
        }

        void modify(int idx, lli val) {
                // cerr << "modify " << idx << " " << val << '\n';
                l[idx] = val;
                idx += N;
                t[idx] = val;
                idx /= 2;
                while (idx >= 1) {
                        t[idx] = max(t[2 * idx], t[2 * idx + 1]);
                        idx /= 2;
                }
        }

        lli query(int l, int r) {
                l += N;
                r += N;
                lli res = -1;
                while (l <= r) {
                        if (l % 2 == 1) res = max(t[l++], res);
                        if (r % 2 == 0) res = max(t[r--], res);
                        l /= 2;
                        r /= 2;
                }
                return res;
        }
} zkw;

int getl(int x, int i) {
        auto &st = mp[x];
        if (SZ(st) == 0) return -1;
        auto it = st.lower_bound(i);
        if (it == st.begin()) return -1;
        --it;
        return *it;
}

int getr(int x, int i) {
        auto &st = mp[x];
        auto it = st.upper_bound(i);
        if (it == st.end()) return -1;
        return *it;
}

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<int> xs(N);
        zkw.init(N);
        map<int, int> mp2;
        for (int i = 0; i < N; i++) {
                int x; cin >> x;
                xs[i] = x;
                if (mp2.find(x) == mp2.end()) {
                        l[i] = -1;
                } else {
                        l[i] = mp2[x];
                        r[l[i]] = i;
                }
                mp2[x] = i;
                mp[x].insert(i);
        }
        zkw.build();
        
        for (int i = 0; i < Q; i++) {
                int op; cin >> op;
                if (op == 1) {
                        int k, u;
                        cin >> k >> u;
                        k--;
                        int x = xs[k];
                        mp[x].erase(k);
                        if (l[k] != -1) {
                                r[l[k]] = r[k];
                        }
                        if (r[k] != -1) {
                                zkw.modify(r[k], l[k]);
                        }
                        xs[k] = u;
                        mp[u].insert(k);
                        int gl = getl(u, k), gr = getr(u, k);
                        if (gl != -1) {
                                r[gl] = k;
                        }
                        zkw.modify(k, gl);
                        r[k] = gr;
                        if (gr != -1) {
                                zkw.modify(gr, k);
                        }
                }
                if (op == 2) {
                        int a, b;
                        cin >> a >> b;
                        a--, b--;
                        
                        // for (int i = 0; i < N; i++) cerr << l[i] << ' ';
                        // cerr << endl;
                        // cerr << zkw.query(a, b) << endl;
                        // zkw.printdbg();

                        if (zkw.query(a, b) >= a) cout << "NO\n";
                        else cout << "YES\n";
                }
        }
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}