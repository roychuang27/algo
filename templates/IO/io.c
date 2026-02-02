#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,abm,avx")
#include <unistd.h>

#define BUF_SIZE 20000000
#define NUM_LENGTH 10

#define RC (ptr_buf_start == ptr_buf_end && (ptr_buf_end = (ptr_buf_start = buf) + read(0, buf, BUF_SIZE), ptr_buf_start == ptr_buf_end) ? -1 : *ptr_buf_start++)
#define WC(x) (vi[pi++] = (x))

static char buf[BUF_SIZE], vi[BUF_SIZE], *ptr_buf_start = buf, *ptr_buf_end = buf;
static int pi;

int R() {int re = 0, neg = 0; char c = RC; while(c == ' ' || c == '\n') c = RC; if(c == '-') neg = 1, c = RC; while(c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'); c = RC;} return neg ? -re : re;}
void W(int x) {char str[NUM_LENGTH]; int p = 0;if (x < 0) {WC('-');x = -x;} do{ str[p++] = '0' ^ (x % 10); x /= 10; } while (x); while (p--) WC(str[p]); WC('\n'); }

int main() {
    int a = R();
    int b = R();
    W(a + b);  // Example usage: prints sum of two integers
    write(1, vi, pi);
    return 0;
}
