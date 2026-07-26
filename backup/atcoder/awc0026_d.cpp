#include <algorithm>
#include <functional>
#include <iostream>
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
        int N, K; cin >> N >> K;
        vector<int> nums;
        vector<pair<int, int>> Q;
        vector<pair<int, int>> events;
        for (int i = 0; i < N; i++) {
                int l, r; cin >> l >> r;
                nums.emplace_back(l); nums.emplace_back(r);
                Q.emplace_back(l, r);
        }
        sort(ALL(nums)); nums.erase(unique(ALL(nums)), nums.end());
        const function c = [&](lli v)->int {
                return lower_bound(ALL(nums), v) - nums.begin();
        };
        vector<int> da(SZ(nums), 0);
        for (const auto &[l, r] : Q) {
                da[c(l)]++;
                da[c(r)]--;
        }
        int ans = 0, prev = -1, preSum = 0;
        for (int i = 0; i < SZ(nums); i++) {
                if (prev != -1 and preSum >= K) ans += (nums[i] - prev);
                preSum += da[i];
                prev = nums[i];
        }
        cout << ans << '\n';

}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
