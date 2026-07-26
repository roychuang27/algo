#include <deque>
#include <iostream>
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
        int N;
        cin >> N;
        deque<pair<int, int>> dq;
        for (int i = 0; i < N; i++) {
                int h, l;
                cin >> h >> l;
                while (!dq.empty() and dq.back().sec <= h) dq.pop_back();
                if (dq.empty() or dq.back().fst < l) dq.push_back({l, h});
        }
        int Q;
        cin >> Q;
        for (int _ = 0; _ < Q; _++) {
                int t;
                cin >> t;
                auto it = lower_bound(ALL(dq), make_pair(t+1, 0));
                cout << it->sec << '\n';
        }
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
