/*
 * Submission ID: 16590233
 * Problem: Apples and Bananas
 * Link: https://cses.fi/problemset/task/2111
 */

#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#define test(x) cerr << "Line(" << __LINE__ << ") " #x << ' ' << x << endl
#define printv(x)                          \
{                                          \
        for (auto i : x) cout << i << ' '; \
        cout << endl;                      \
}
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) x.begin(), x.end()
#define rALL(x) x.begin(), x.end()

using namespace std;
using lli = long long int;

#include <unistd.h>
 
struct fastIO {
    static constexpr unsigned Ibuf_size = 1 << 16, Obuf_size = 1 << 16;
 
    static constexpr array<char, 200> digit_table = []() {
        array<char, 200> ret{};
        for (int i = 0; i < 100; i++) {
            int x = i;
            for (int t = 2; t--; ) {
                ret[i * 2 + t] = (x % 10) ^ 48;
                x /= 10;
            }
        }
        return ret;
    }();
 
    static constexpr array<unsigned, 5> ten_pow = []() {
        array<unsigned, 5> ret{};
        ret[0] = 1;
        for (int i = 1; i < 5; i++) ret[i] = ret[i - 1] * 10;
        return ret;
    }();
 
    char Ibuf[Ibuf_size], Obuf[Obuf_size], num_buf[32], Ic, not_eof;
 
    unsigned Il, Ir, Or;
 
    explicit operator bool() const
    { return not_eof; }
 
    fastIO() : Il(), Ir(), Or(), Ic(), not_eof(1) {}
    ~fastIO() { flush(); }
 
    char get_char() {
        if (Il == Ir) Ir = (Il = 0) + read(0, Ibuf, Ibuf_size);
        if (Ir == 0) return (not_eof = 0);
        return Ibuf[Il++];
    }
 
    void skip_space() {
        while (isspace(Ic = get_char()));
    }
 
    void flush() {
        write(1, Obuf, Or);
        Or = 0;
    }
 
    fastIO& operator>>(char& c) {
        skip_space();
        c = Ic;
        return *this;
    }
 
    template <class Int, typename = enable_if_t<is_integral_v<Int>>>
    fastIO& operator>>(Int& x) {
        skip_space();
        bool neg = (Ic == '-');
        if (neg) Ic = get_char();
        Int ret{};
        if (isdigit(Ic)) {
            ret = Ic & 15;
            while (isdigit(Ic = get_char()))
                ret = ret * 10 + (Ic & 15);
        }
        x = neg ? -ret : ret;
        return *this;
    }
 
    fastIO& operator>>(string& str) {
        skip_space();
        if (Ic != 0) {
            str.clear();
            do {
                str.push_back(Ic);
            } while (!isspace(Ic = get_char()) && Ic);
        }
        return *this;
    }
 
    fastIO& operator<<(char c) {
        if (Or == Obuf_size) flush();
        Obuf[Or++] = c;
        return *this;
    }
 
    template <class Int, typename = enable_if_t<is_integral_v<Int>>>
    fastIO& operator<<(Int x) {
        make_unsigned_t<Int> y = x;
        if constexpr (is_signed_v<Int>) {
            if (x < 0) {
                y = -x;
                (*this) << '-';
            }
        }
        int __i = 32;
        do {
            *(short*)&num_buf[__i - 2] = *(const short*)&digit_table[(y % 100) * 2];
            __i -= 1 + (y >= 10);
        } while (y /= 100);
        if (Or + 32 - __i >= Obuf_size) flush();
        for (; __i < 32; ) Obuf[Or++] = num_buf[__i++];
        return *this;
    }
 
    fastIO& operator<<(string_view sv) {
        if (Or + size(sv) >= Obuf_size) {
            flush();
            write(1, data(sv), size(sv));
        }
        else {
            copy(begin(sv), end(sv), &Obuf[Or]);
            Or += size(sv);
        }
        return *this;
    }
} IO;
 
#define cin IO
#define cout IO

using ld = double;
const ld PI = acos(-1.0);

struct CD {
        ld real = 0, imag = 0;
        CD(ld x, ld y) : real(x), imag(y) {};
        CD(ld x) : real(x), imag(0) {};
        CD operator+(const CD other) {
                return {real + other.real, imag + other.imag};
        }
        CD operator-(const CD other) {
                return {real - other.real, imag - other.imag};
        }
        CD operator*(const CD other) {
                return {real*other.real - imag*other.imag, real*other.imag + imag*other.real};
        }
        bool operator==(const CD other) {
                return real == other.real and imag == other.imag;
        }
        bool operator!=(const CD other) {
                return real != other.real or imag != other.imag;
        }
};

vector<CD> mem_omega(2e7, -1);
CD get_omega(int i, int n) {
        int h = (i + n / 2);
        if (mem_omega[h] != CD(-1)) return mem_omega[h];
        ld angle = (ld) i / n * (2 * PI);
        mem_omega[h] = CD(cos(angle), sin(angle));
        return mem_omega[h];
};

void FFT(vector<CD> &v, int inv){
        int N = v.size();
        if (N == 1) return;
        vector<CD> even(N / 2, 0), odd(N / 2, 0);
        for (int i = 0; i < N / 2; i++) even[i] = v[2*i], odd[i] = v[2*i+1];
        FFT(even, inv);
        FFT(odd,  inv);
        for (int i = 0; i < N / 2; i++) {
                CD z = get_omega(i, N);
                if (inv == -1) z = {z.real, -1 * z.imag};
                v[i]         = even[i] + z * odd[i];
                v[i + N / 2] = even[i] - z * odd[i];
        }
}

void solution() {
        int K, N, M; cin >> K >> N >> M;
        const int s = (1 << (int)ceil(log2(2*K+2)));
        vector<CD> A(s, 0), C(s, 0);
        for (int i = 0; i < N; i++) { int x; cin >> x; A[x].real++; }
        for (int i = 0; i < M; i++) { int x; cin >> x; A[x].imag++; }
        FFT(A, 1);
        for (int i = 0; i < s; i++)
                C[i] = A[i] * A[i];
        FFT(C, -1);
        for (int i = 2; i <= 2*K; i++)
                cout << llround(C[i].imag/(2*s)) << ' ';
        cout << '\n';
}

int main() {
        // cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
