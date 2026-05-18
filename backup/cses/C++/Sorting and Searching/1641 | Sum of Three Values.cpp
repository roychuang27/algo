#pragma GCC optimize("Ofast")
#include <iostream>
#include <utility>
#include <climits>
#include <vector>
#include <algorithm>
#define AC ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ALL(x) begin(x),end(x)
#define pb emplace_back

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void solve () {
    int N;
    ll x;
    cin >> N >> x;
    vector<pair<long long, int>> nums(N);
    for (int i = 0; i < N; i++) {
        ll k;
        cin >> k;
        nums[i].first = k;
        nums[i].second = i + 1;
    }
    sort(ALL(nums));
    for (int i = 0; i < N - 1; i++) {
        int l = 0, r = N - 1;
        ll target = x - nums[i].first;
        if (target > nums[r].first*2) continue;
        if (target < nums[l].first*2) continue;
        while (l < r) {
            if (l == i) {
                l++;
                continue;
            }
            if (r == i) {
                r--;
                continue;
            }
            ll sum = nums[l].first + nums[r].first;
            if (sum == target) {
                cout << nums[l].second << ' ' << nums[i].second
                        << ' ' << nums[r].second << '\n';
                return;
            }
            if (sum < target) l++;
            else r--;
        }
    }
    cout << "IMPOSSIBLE\n";
}

int main () {
    AC
    solve();
    return 0;
}