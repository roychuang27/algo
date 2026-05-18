#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#ifndef ONLINE_JUDGE
#define test(...) do { cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((cerr << ' ' << args), ...); }(__VA_ARGS__)); cerr << endl; } while(0)
#define testv(x) do { cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) cerr << (_i++ ? ", " : "") << _e; cerr << "]" << endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define printv(x) { for (auto i : (x)) cout << i << ' '; cout << endl; }
#define SQ(x) ((x) * (x))
#define SZ(x) ((int)x.size())
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define rALL(x) rbegin(x), rend(x)
#define fst first
#define sec second
 
using namespace std;
using lli = long long int;
 
lli fpow(lli a, lli p, lli m) {
        lli res = 1;
        while (p) {
                if (p & 1) res = (res * a) % m;
                a = (a * a) % m;
                p >>= 1;
        }
        return res;
}
 
lli inv(lli a, lli p) {
        return fpow(a, p-2, p);
}
 
const lli hash_mod = 998244353;
const lli hash_mul = 257;
 
void solution() {
        string S; cin >> S;
        int N = SZ(S);
        vector<lli> h(N); // h[i] = hash([0...i])
        lli pre_mul = 1, last_hash = 0;
        for (int i = 0; i < N; i++) {
                h[i] = (last_hash + S[i] * pre_mul) % hash_mod;
                pre_mul = (pre_mul * hash_mul) % hash_mod;
                last_hash = h[i];
        }
        testv(h);
        const function<lli(int, int)> get_hash = [&](int l, int r) -> lli {
                if (l == 0) return h[r];
                lli hash = h[r];
                if (hash > h[l-1]) hash -= h[l-1];
                else               hash = hash + hash_mod - h[l-1];
                lli div_inv = inv(fpow(hash_mul, l, hash_mod), hash_mod);
                hash = (hash * div_inv) % hash_mod;
                test(l, r, hash);
                return hash;
        };
        vector<int> ans;
        ans.eb(N);
        for (int len = 1; len < N; len++) {
                if (get_hash(0, len-1) == get_hash(N-len, N-1)) ans.eb(N-len);
        }
        reverse(ALL(ans));
        printv(ans);
}
 
int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
