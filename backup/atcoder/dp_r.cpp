#include <iostream>
#include <vector>
#ifdef LOCAL
#define test(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define testv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define SZ(x) ((int) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

constexpr lli MOD = 1e9 + 7;

vector<vector<lli>> matrices_multiply(vector<vector<lli>>& A,
                                      vector<vector<lli>>& B) {
        if (SZ(A[0]) != SZ(B)) return {};
        vector<vector<lli>> res(SZ(A), vector<lli>(SZ(B[0]), 0LL));
        for (int i = 0; i < SZ(A); i++) {
                for (int j = 0; j < SZ(B[0]); j++) {
                        for (int k = 0; k < SZ(A[0]); k++) {
                                res[i][j] += A[i][k] * B[k][j];
                                if (res[i][j] >= MOD) res[i][j] %= MOD;
                        }
                }
        }
        return res;
}

vector<vector<lli>> matrix_fast_power(vector<vector<lli>>& A, lli power) {
        if (SZ(A) != SZ(A[0])) return {};
        vector<vector<lli>> res(SZ(A), vector<lli>(SZ(A[0]), 0LL));
        for (int i = 0; i < SZ(A); i++) res[i][i] = 1;
        while (power > 0) {
                if (power & 1) res = matrices_multiply(res, A);
                power >>= 1;
                A = matrices_multiply(A, A);
        }
        return res;
}

void solution() {
        int N;
        lli K;
        cin >> N >> K;
        vector<vector<lli>> A(N, vector<lli> (N));
        for (auto &v : A) for (auto &a : v) cin >> a;
        auto res = matrix_fast_power(A, K);
        lli ans = 0;
        for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                        ans += res[i][j];
                        if (ans >= MOD) ans %= MOD;
                }
        }
        cout << ans << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
