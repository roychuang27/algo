/*
 * Submission ID: 14518329
 * Problem: Maximum Subarray Sum II
 * Link: https://cses.fi/problemset/task/1644
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,avx")
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

#define SZ(x) ((int) x.size())
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef long long lli;

lli dq[200005];
lli pre[200005];

int main() {
	int N = readUInt(), A = readUInt(), B = readUInt();
	pre[0] = 0;
	for (int i = 1; i <= N; i++) {
		pre[i] = pre[i-1] + readInt();
	}
	int l = 0, r = -1;
	lli ans = -1e18;
	for (int i = A; i <= N; i++) {
		if (r >= l && dq[l] < i-B) l++;
		while (r >= l && pre[dq[r]] > pre[i-A]) r--;
		dq[++r] = i - A;
		ans = max(pre[i] - pre[dq[l]], ans);
	}
	outInt(ans);
	write(1, vi, ptr_buf_out);
// 	cout << ans << endl;
	return 0;
}