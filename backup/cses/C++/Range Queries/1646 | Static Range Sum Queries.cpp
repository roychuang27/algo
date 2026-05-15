/*
 * Submission ID: 16736175
 * Problem: Static Range Sum Queries
 * Link: https://cses.fi/problemset/task/1646
 */

#include <bits/stdc++.h>
using namespace std;

struct Query {
    int l, r, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    int B = sqrt(n);

    vector<Query> qs(q);
    for (int i = 0; i < q; i++) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].l--, qs[i].r--;
        qs[i].id = i;
    }

    sort(qs.begin(), qs.end(), [&](const Query &x, const Query &y) {
        if (x.l / B == y.l / B)
            return x.r < y.r;
        return (x.l / B) < (y.l / B);
    });

    vector<long long> ans(q);
    long long cur = 0;

    int L = 0, R = -1;

    auto add = [&](int i) {
        cur += a[i];
    };

    auto remove = [&](int i) {
        cur -= a[i];
    };

    for (auto &qr : qs) {
        int l = qr.l, r = qr.r;

        while (R < r) add(++R);
        while (L > l) add(--L);
        while (R > r) remove(R--);
        while (L < l) remove(L++);

        ans[qr.id] = cur;
    }

    for (auto x : ans) cout << x << '\n';
}
