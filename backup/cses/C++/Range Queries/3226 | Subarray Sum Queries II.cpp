#pragma GCC optimize("Ofast")
#include <algorithm>

#include <unistd.h>

#define BUF_SIZE 20000000
#define num_length 20

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

void outInt(long long x) {
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

using namespace std;
typedef long long lli;

const lli inf = 1e18;

struct Node {
    lli M, L, R, S;
    
    void set_value_for_single_node(lli val) {
        M = max(0LL, val);
        L = val;
        R = val;
        S = val;
    }

    void set_void_node() {
        M = -inf;
        L = -inf;
        R = -inf;
        S = 0;
    }
    
    Node operator+ (Node r) {
        Node ret;
        ret.M = max({M, r.M, R + r.L});
        ret.L = max(L, S + r.L);
        ret.R = max(R + r.S, r.R);
        ret.S = S + r.S;
        return ret;
    }
};

const int maxN = 2e5;
int arr[maxN + 5];

struct ZKW {
    Node tree[400005];
    int N = 0;
    
    void init(int n) {
        N = n;
    }
    
    void build() {
        for (int i = 0; i < N; i++) {
            tree[N + i].set_value_for_single_node(arr[i]);
        }
        for (int i = N - 1; i > 0; i--) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }
    
    void modify(int idx, int val) {
        idx += N;
        tree[idx].set_value_for_single_node(val);
        idx /= 2;
        while (idx >= 1) {
            tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
            idx /= 2;
        }
    }
    
    lli query(int l, int r) {
        l += N;
        r += N;
        Node resL, resR;
        resL.set_void_node();
        resR.set_void_node();
        while (l <= r) {
            if (l % 2 == 1) {
                resL = resL + tree[l];
                l++;
            }
            if (r % 2 == 0) {
                resR = tree[r] + resR;
                r--;
            }
            l /= 2;
            r /= 2;
        }
        return (resL + resR).M;
    }
} zkw;

void solve () {
    int n = readUInt(), q = readUInt();
    zkw.init(n);
    for (int i = 0; i < n; i++) {
        arr[i] = readInt();
    }
    zkw.build();
    while (q--) {
        // zkw.printdbg();
        int a = readUInt(), b = readUInt();
        outInt(zkw.query(a-1, b-1));
    }
    write(1, vi, ptr_buf_out);
}

int main () {
    solve();
    return 0;
}