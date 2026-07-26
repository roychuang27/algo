#include <iostream>
#include <map>
#include <vector>
#include <utility>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()

using namespace std;
using lli = long long int;

void solution() {
        int N, M;
        lli S;
        cin >> N >> M >> S;
        vector<int> ds(N);
        for (int &d : ds) cin >> d;
        // vector<pair<int, int>> hs(M);
        // for (auto &[p, r] : hs) cin >> p >> r;
        map<int, int> mp;
        for (int i = 0; i < M; i++) {
                int p, r;
                cin >> p >> r;
                mp[p-1] = r;
        }
        bool ex = 0;
        for (int i = 0; i < N; i++) {
                if (not ex) S -= ds[i];
                else        S -= 2*ds[i];
                if (S <= 0)
                        ex = 1;
                S += mp[i];
        }
        cout << S << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
