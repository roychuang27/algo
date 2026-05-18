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
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
