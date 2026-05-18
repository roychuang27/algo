#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,avx")
#include <unistd.h>

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
#define PU(x) vi[p3++] = x

#define BUF_SIZE 4000000
#define T_SIZE 40
static char buf[BUF_SIZE], vi[BUF_SIZE], *p1 = buf, *p2 = buf;
static int p3;
static int pre[2000001]; // Keep it global to prevent stack overflow
unsigned in() {unsigned re = 0; char c = GU; while (c == ' ' || c == '\n') {c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return re;}
void out(unsigned x) {char str[T_SIZE]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];}vi[p3++] = '\n';if (p3 >= BUF_SIZE - T_SIZE) write(1, vi, p3), p3 = 0;}

int main () {
    int n, q;
    n = in(); q = in();
    int a, b; a = in();
    pre[1] = a;
    for (int i = 2; i <= n; i++) {
        a = in();
        pre[i] = a ^ pre[i-1];
    }
    while (q--) {
        a = in(); b = in();
        if (a == 1) {
            out(pre[b]);
        } else {
            out(pre[b] ^ pre[a-1]);
        }
    }
    write(1, vi, p3);
    return 0;
}