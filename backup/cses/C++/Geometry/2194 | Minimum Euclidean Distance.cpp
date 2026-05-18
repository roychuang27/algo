#include <algorithm>
#include <climits>
#include <cmath>
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

struct Point {
        lli x, y;
};

lli two_dist_sq(Point &a, Point &b) { return SQ(a.x - b.x) + SQ(a.y - b.y); }

constexpr lli INF = 4e18;

void solution() {
        int N;
        cin >> N;
        vector<Point> pts(N);
        for (int i = 0; i < N; i++) cin >> pts[i].x >> pts[i].y;
        sort(pts.begin(), pts.end(), [](Point &a, Point &b) {
                return a.x < b.x;
        });

        const auto get_min_dist_sq = [&](auto &&self, int start, int end) -> lli {
                if (end == start) return INF;
                if (end - start == 1) {
                        return two_dist_sq(pts[start], pts[end]);
                }
                int mid = (start + end) / 2;
                lli cx = pts[mid].x;
                lli d = min(self(self, start, mid), self(self, mid+1, end));
                lli dsqrt = sqrt(d);
                vector<Point> candidates;
                for (int i = start; i <= end; i++) {
                        if (SQ(pts[i].x - cx) >= d) continue;
                        candidates.emplace_back(pts[i]);
                }
                sort(candidates.begin(), candidates.end(), [](auto &a, auto &b) {
                        return a.y < b.y;
                });
                int M = SZ(candidates);
                for (int i = 0; i < M; i++) {
                        for (int j = i+1; j < M; j++) {
                                if (candidates[j].y > candidates[i].y + dsqrt) break;
                                d = min(d, two_dist_sq(candidates[i], candidates[j]));
                        }
                }
                return d;
        };

        cout << get_min_dist_sq(get_min_dist_sq, 0, N-1);
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
