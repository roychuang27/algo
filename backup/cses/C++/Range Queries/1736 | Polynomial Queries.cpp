/*
 * Submission ID: 16670864
 * Problem: Polynomial Queries
 * Link: https://cses.fi/problemset/task/1736
 */

#include <iostream>
#include <vector>
using namespace std;

using lli = long long;

struct Tag {
    lli s = 0, d = 0;
    Tag operator+(const Tag &other) const {
        return {s + other.s, d + other.d};
    }
};

struct LazySegTree {
    const int N;
    vector<lli> t;
    vector<Tag> tag;

    LazySegTree(const vector<lli> &vec) : N((int)vec.size()), t(4 * N), tag(4 * N) {
        build(1, 0, N - 1, vec);
    }

    void build(int id, int l, int r, const vector<lli> &vec) {
        if (l == r) {
            t[id] = vec[l];
            return;
        }
        int m = (l + r) / 2;
        build(id * 2, l, m, vec);
        build(id * 2 + 1, m + 1, r, vec);
        t[id] = t[id * 2] + t[id * 2 + 1];
    }

    void apply(int id, int len, Tag x) {
        auto [s, d] = x;
        t[id] += (2 * s + (len - 1) * d) * len / 2;
        tag[id] = tag[id] + x;
    }

    void push_down(int id, int l, int r) {
        if (tag[id].s == 0 && tag[id].d == 0) return;
        if (l == r) {
            tag[id] = {};
            return;
        }
        int m = (l + r) / 2;
        int left_len = m - l + 1;
        apply(id * 2, left_len, tag[id]);
        apply(id * 2 + 1, r - m, {tag[id].s + 1LL * left_len * tag[id].d, tag[id].d});
        tag[id] = {};
    }

    void range_update(int id, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(id, r - l + 1, {l - ql + 1, 1});
            return;
        }
        push_down(id, l, r);
        int m = (l + r) / 2;
        range_update(id * 2, l, m, ql, qr);
        range_update(id * 2 + 1, m + 1, r, ql, qr);
        t[id] = t[id * 2] + t[id * 2 + 1];
    }

    lli query_range_sum(int id, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[id];
        push_down(id, l, r);
        int m = (l + r) / 2;
        return query_range_sum(id * 2, l, m, ql, qr)
             + query_range_sum(id * 2 + 1, m + 1, r, ql, qr);
    }
};

void solution() {
    int N, Q;
    cin >> N >> Q;

    vector<lli> A(N);
    for (lli &x : A) cin >> x;

    LazySegTree st(A);

    while (Q--) {
        int op, a, b;
        cin >> op >> a >> b;
        --a; --b;

        if (op == 1) {
            st.range_update(1, 0, N - 1, a, b);
        } else {
            cout << st.query_range_sum(1, 0, N - 1, a, b) << '\n';
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solution();
    return 0;
}
