#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
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
#define F first
#define S second

using namespace std;
using lli = long long int;

void solution() {
        int N, M; cin >> N >> M;
        vector<pair<int, int>> V(N);
        for (auto &[h, s] : V) cin >> h >> s;
        vector<int> P(M);
        for (int &p : P) cin >> p;
        sort(ALL(V));
        sort(ALL(P));
        int it = 0;
        lli S = 0;
        priority_queue<int> pq;
        for (const int &p : P) {
                while (it < N and V[it].F <= p) {
                        pq.push(V[it].S);
                        it++;
                }
                if (pq.empty()) {
                        cout << "-1\n";
                        return;
                }
                S += pq.top();
                pq.pop();
        }
        cout << S << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
