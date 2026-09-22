#include <bits/stdc++.h>
#ifdef LOCAL
#define test(...) do { std::cerr << "Line(" << __LINE__ << ") [" #__VA_ARGS__ "] =>"; ([](auto&&... args){ ((std::cerr << ' ' << args), ...); }(__VA_ARGS__)); std::cerr << std::endl; } while(0)
#define testv(x) do { std::cerr << "Line(" << __LINE__ << ") " #x " => ["; int _i=0; for (auto& _e : (x)) std::cerr << (_i++ ? ", " : "") << _e; std::cerr << "]" << std::endl; } while(0)
#else
#define test(...) 0
#define testv(...) 0
#endif
#define ALL(x) std::begin(x), std::end(x)
#define rALL(x) std::rbegin(x), std::rend(x)
#define SZ(x) ((int) x.size())
#define SQ(x) ((x) * (x))
#define CORDCOMP(x, fx) std::sort(ALL(x)); x.erase(std::unique(ALL(x)), std::end(x)); const auto fx = [&](int val) -> int { return std::lower_bound(ALL(x), val) - std::begin(x); }
#define fst first
#define sec second

using lli = long long int;
using namespace std;

void solution() {
        int N, Q;
        cin >> N >> Q;
        vector<int> P(N+1), P2(N+1);
        for (int i = 1; i <= N; i++) {
                cin >> P[i];
                P2[P[i]] = i;
        }
        testv(P);
        testv(P2);

        bool s = 0;

        for (int _ = 0; _ < Q; _++) {
                int op;
                cin >> op;
                if (op == 1) {
                        int x, y;
                        cin >> x >> y;
                        if (s) {
                                swap(P2[x], P2[y]);
                                swap(P[P2[x]], P[P2[y]]);
                        } else {
                                swap(P[x], P[y]);
                                swap(P2[P[x]], P2[P[y]]);
                        }
                }
                if (op == 2) {
                        s = !s;
                }
                testv(P);
                testv(P2);
        }

        if (s) {
                for (int i = 0; i < N; i++) cout << P2[i+1] << ' ';
                cout << '\n';
        } else {
                for (int i = 0; i < N; i++) cout << P[i+1] << ' ';
                cout << '\n';
        } 
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
