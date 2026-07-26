#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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
using namespace __gnu_pbds;
using lli = long long int;

using ordered_set = tree<pair<lli, int>, null_type, std::less<pair<lli, int>>, rb_tree_tag, tree_order_statistics_node_update>;

void solution() {
        int N; lli M, K; cin >> N >> M >> K;
        vector<int> A(N+1);
        for (int i = 1; i <= N; i++)
                cin >> A[i];
        vector<lli> B(N+1), S(N+1);
        S[0] = 0;
        for (int i = 1; i <= N; i++) {
                B[i] = A[i] + M;
                S[i] = S[i-1] + B[i];
        }
        ordered_set ost;
        lli ans = 0;
        ost.insert({S[0], 0});
        for (int i = 1; i <= N; i++) {
                auto it = ost.lower_bound({S[i]-K, 0});
                if (it != ost.end()) {
                        int idx = ost.order_of_key(*it);
                        ans += (SZ(ost) - idx);
                }
                ost.insert({S[i], i});
        }
        cout << ans << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}