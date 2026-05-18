#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;

    ll s = (ll)n * (n + 1) / 2;

    if (s % 2 == 1) {
        cout << "NO\n";
        return 0;
    }
    s /= 2;

    vector<int> set1, set2;
    for (int x = n; x >= 1; x--) {
        if (s >= x) {
            s -= x;
            set1.push_back(x);
        } else {
            set2.push_back(x);
        }
    }

    cout << "YES\n";
    cout << set1.size() << "\n";
    for (auto x : set1) cout << x << " ";
    cout << "\n";
    cout << set2.size() << "\n";
    for (auto x : set2) cout << x << " ";
    cout << "\n";
}