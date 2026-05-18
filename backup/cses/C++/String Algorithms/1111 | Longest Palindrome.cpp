#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#ifdef LOCAL
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

vector<int> manacher(string &s) {
        int N = SZ(s);
        vector<int> m(N);
        m[0] = 0;
        int L = 0, R = 0;
        for (int i = 1; i < N; i++) {
                if (i <= R) {
                        m[i] = min(m[L + L - i], R - i);
                }
                while (m[i] < i and i + m[i] + 1 < N and s[i + m[i] + 1] == s[i - m[i] - 1]) {
                        m[i]++;
                }
                if (i + m[i] > R) {
                        L = i;
                        R = i + m[i];
                }
        }
        return m;
}

void solution() {
        string s; cin >> s;
        string t;
        for (const char c : s) {
                t += '.';
                t += c;
        }
        t += '.';
        test(t);
        vector<int> m = manacher(t);
        testv(m);
        int max_len = 0, center;
        string ans;
        for (int i = 0; i < SZ(m); i++) {
                if (m[i] > max_len) {
                        max_len = m[i];
                        center = i;
                }
        }
        int start = (center - max_len) / 2;
        cout << s.substr(start, max_len) << '\n';
}

int main() {
        cin.tie(nullptr)->sync_with_stdio(false);
        solution();
        return 0;
}
