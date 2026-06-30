#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
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
        int N, L, R;
        cin >> N >> L >> R;
        vector<lli> A(N), B(N);
        vector<lli> W(N);
        for (auto &i : A) cin >> i;
        for (auto &i : B) cin >> i;
        for (auto &i : W) cin >> i;
        vector<lli> dist(N, -1);
        set<pair<lli, int>> st;
        for (int i = 1; i < N; i++) {
                st.insert({B[i], i});
        }
        priority_queue<pair<lli, int>> pq;
        pq.push({-W[0], 0});
        while (!pq.empty()) {
                auto [d, cur] = pq.top();
                pq.pop();
                dist[cur] = -d;

                auto it = st.lower_bound({L-A[cur], 0});
                while (it != st.end() and it->fst + A[cur] <= R) {
                        pq.push({d - W[it->sec], it->sec});
                        it = st.erase(it);
                }
        }

        for (auto &i : dist) cout << i << ' ';
        cout << endl;
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
