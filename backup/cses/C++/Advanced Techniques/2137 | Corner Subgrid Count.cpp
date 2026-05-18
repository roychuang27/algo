#pragma GCC optimize("Ofast")
#pragma GCC target("popcnt")
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <bitset>
#define AC ios_base::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
#define ALL(x) begin(x),end(x)
#define pb emplace_back

int N = 64;

using namespace std;
typedef long long ll;

int main () {
    AC
    int n; cin >> n;
    bitset<3000> bset[3000];
    for (int i = 0; i < n; i++) {
        cin >> bset[i];
    }
    ll ans = 0;
    for (int a = 0; a < n-1; a++) {
        for (int b = a + 1; b < n; b++) {
            int cnt = (bset[a] & bset[b]).count();
            ans += cnt * (cnt - 1) / 2;
        }
    }
    cout << ans << '\n';
    return 0;
}