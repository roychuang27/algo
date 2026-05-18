#include <algorithm>
#include <array>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,abm")
#include <unistd.h>

#define BUF_SIZE 20000000
#define num_length 10

#define fast_get_char (ptr_buf_start == ptr_buf_end && (ptr_buf_end = (ptr_buf_start = buf) + read(0, buf, BUF_SIZE), ptr_buf_start == ptr_buf_end) ? -1 : *ptr_buf_start++)
#define fast_put_char(x) (vi[ptr_buf_out++] = (x))

static char buf[BUF_SIZE], vi[BUF_SIZE], *ptr_buf_start = buf, *ptr_buf_end = buf;
static int ptr_buf_out;

int readInt() {
    int re = 0, neg = 0;
    char c = fast_get_char;
    while (c == ' ' || c == '\n') c = fast_get_char;

    if (c == '-') neg = 1, c = fast_get_char;

    while (c >= '0' && c <= '9') {
        re = (re << 3) + (re << 1) + (c ^ '0'); 
        c = fast_get_char;
    }
    return neg ? -re : re;
}

unsigned readUInt() {
    int re = 0;
    char c = fast_get_char;
    while (c == ' ' || c == '\n') c = fast_get_char;

    while (c >= '0' && c <= '9') {
        re = (re << 3) + (re << 1) + (c ^ '0'); 
        c = fast_get_char;
    }
    return re;
}

void outInt(int x) {
    char str[num_length];
    int p = 0;

    if (x < 0) {
        fast_put_char('-');
        x = -x;
    }

    do {
        str[p++] = '0' ^ (x % 10);
        x /= 10;
    } while (x);

    while (p--) fast_put_char(str[p]);
    fast_put_char('\n');
}

void outUInt(unsigned x) {
    char str[num_length];
    int p = 0;

    do {
        str[p++] = '0' ^ (x % 10);
        x /= 10;
    } while (x);

    while (p--) fast_put_char(str[p]);
    fast_put_char('\n');
}

using namespace std;
using lli = long long int;

class Fenwick {
        public:
        const int capacity = 2e5;
        vector<lli> b;
        
        Fenwick() {
                b = vector<lli> (capacity + 10, 0);
        }
        
        int lowbit(int x) {
                return x & -x;
        }
        
        void modify(int idx, int delta) {
                for (int pos = idx; pos <= capacity; pos += lowbit(pos)) {
                        b[pos] += delta;
                }
        }
        
        lli query(int idx) {
                if (idx == 0)
                        return 0;
                lli res = 0;
                for (int pos = idx; pos >= 1; pos -= lowbit(pos)) {
                        res += b[pos];
                }
                return res;
        }
};

void solution() {
        int N = readUInt(), Q = readUInt();
        vector<pair<int, int>> xs(N + 1);
        for (int i = 1; i <= N; i++) {
                xs[i].first = readUInt();
                xs[i].second = i;
        }

        // a <= i <= b, c <= x_i <= d

        vector<array<int, 5>> qs; // i, a, b, x, sign
        vector<int> ans(Q, 0);
        for (int i = 0; i < Q; i++) {
                int a = readUInt(), b = readUInt(), c = readUInt(), d = readUInt();
                qs.push_back({i, a, b, c-1, -1});
                qs.push_back({i, a, b, d, 1});
        }
        Fenwick fenwick;
        
        sort(qs.begin(), qs.end(),
                [&](auto q1, auto q2) {
                        return q1[3] < q2[3];
                }
        );
        
        sort(xs.begin(), xs.end(),
                [&](auto x1, auto x2) {
                        return x1.first < x2.first;
                }
        );
        
        int p = 1;
        for (auto &[i, l, r, x, sign] : qs) {
                while (p <= N and xs[p].first <= x) {
                        fenwick.modify(xs[p].second, +1);
                        p++;
                }
                ans[i] += sign * (fenwick.query(r) - fenwick.query(l-1));
        }
        
        for (auto &k : ans) outUInt(k);
}

int main() {
        solution();
        write(1, vi, ptr_buf_out);
        return 0;
}