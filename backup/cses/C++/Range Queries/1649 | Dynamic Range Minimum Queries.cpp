#include <bits/stdc++.h>
using namespace std;
 
const int inf = 1e9 + 10;
 
void modify(vector<int> &tree, int n, int k, int x) {
    k += n;
    tree[k] = x;
    for (k >>= 1; k > 0; k >>= 1) {
    	tree[k] = min(tree[k<<1], tree[(k<<1)|1]);
    }
}
 
int getMin(vector<int> &tree, int n, int l, int r) {
    l += n, r += n;
    int ret = inf;
    while (l <= r) {
    	if (l & 1) ret = min(tree[l++], ret);
        if (r % 2 == 0) ret = min(tree[r--], ret);
        l >>= 1, r >>= 1;
    }
    return ret;
}
 
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> tree(2*n+10);
    for (int i = 0; i < n; i++) {
            cin >> tree[i + n];
    }
    for (int i = n - 1; i > 0; i--) {
        tree[i] = min(tree[i<<1], tree[(i<<1)|1]);
    }
    while (q--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            modify(tree, n, a-1, b);
        } else {
            cout << getMin(tree, n, a-1, b-1) << '\n';
        }
    }
    return 0;
}
