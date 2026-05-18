#pragma GCC optimize("Ofast")
#include <iostream>
#include <algorithm>
#define AC cin.tie(0)->sync_with_stdio(false);
#define pb emplace_back
#define ALL(x) begin(x),end(x)
#define MP(x, y) make_pair((x), (y))
#define SQ(x) ((x)*(x))
#define SZ(x) ((int) x.size())
#define err(x) cerr << #x << ": " << x << endl;

using namespace std;
typedef long long ll;

struct Cell {
    ll M, L, R, S;
};

const int maxN = 2e5;
int arr[maxN + 5];
Cell tree[4*maxN + 5];
int N;

Cell combine (Cell a, Cell b) {
    Cell ret;
    ret.M = max(max(a.M, b.M), a.R + b.L);
    ret.L = max(a.L, a.S + b.L);
    ret.R = max(a.R + b.S, b.R);
    ret.S = a.S + b.S;
    return ret;
}

Cell Val(int x) {
    return {max(x, 0), x, x, x};
}

void build(int id, int l, int r) {
    if (l == r) { // 對應到原陣列特定值
        tree[id] = Val(arr[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid); // 左子節點
    build(id * 2 + 1, mid + 1, r); // 右子節點
    tree[id] = combine(tree[id * 2], tree[id * 2 + 1]); // 合併
}

// id = 節點編號 / k = 原陣列索引 / x = 值 / [l, r] 為當前處理區間
void modify(int id, int k, int x, int l, int r) {
    if (l == r) {
        tree[id] = Val(x);
        return;
    }
    int mid = (l + r) / 2;
    // 該點在左子節點區間內
    if (k <= mid) modify(id * 2, k, x, l, mid);
    // 在右子節點區間內
    else modify(id * 2 + 1, k, x, mid + 1, r);
    // 更新
    tree[id] = combine(tree[id * 2], tree[id * 2 + 1]);
}

// id = 節點編號 / [l, r] 當前處理區間 / [L, R] 欲查詢區間
Cell query(int id, int l, int r, int L, int R) {
    if (l <= L && R <= r) { // 當前處理區間完全落在欲查詢區間內
        return tree[id];
    }
    int mid = (l + r) / 2;
    Cell ret;
    // 欲查詢區間在當左子節點區間內
    if (L <= mid) ret = query(id * 2, l, mid, L, R);
    // 右子節點
    if (R > mid) ret = query(id * 2 + 1, mid + 1, r, L, R);
    return ret;
}

void solve () {
    int q;
    cin >> N >> q;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    build(1, 1, N);
    while (q--) {
        int k, x;
        cin >> k >> x;
        modify(1, k, x, 1, N);
        cout << query(1, 1, N, 1, N).M << '\n';
    }
}

int main () {
    AC
    solve();
    return 0;
}