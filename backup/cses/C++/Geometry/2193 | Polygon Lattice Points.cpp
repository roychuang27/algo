#include <algorithm>
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

using ld = long long int;

struct Point {
        ld x, y;
        Point(ld _x = 0, ld _y = 0) : x(_x), y(_y) {};
        friend ostream& operator << (ostream &s, const Point &p) { return s << '(' << p.x << ", " << p.y << ')'; }
};

Point operator + (const Point &lhs, const Point &rhs) { return Point(lhs.x + rhs.x, lhs.y + rhs.y); }
Point operator - (const Point &lhs, const Point &rhs) { return Point(lhs.x - rhs.x, lhs.y - rhs.y); }
Point operator * (const ld &lhs, const Point &rhs) { return Point(lhs * rhs.x, lhs * rhs.y); }
Point operator * (const Point &lhs, const ld &rhs) { return Point(lhs.x * rhs, lhs.y * rhs); }
Point operator / (const Point &lhs, const ld &rhs) { return Point(lhs.x / rhs, lhs.y / rhs); }
Point complex_mul(const Point &lhs, const Point &rhs) { return Point(lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x); }
ld dot(const Point &lhs, const Point &rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
ld det(const Point &lhs, const Point &rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }
ld abs(const Point &p) { return sqrt(SQ(p.x) + SQ(p.y)); }

void solution() {
        int N;
        cin >> N;
        vector<Point> pts(N+1);
        for (int i = 0; i < N; i++) cin >> pts[i].x >> pts[i].y;
        pts[N] = pts[0];
        ld area = 0;
        for (int i = 0; i < N; i++) area += det(pts[i], pts[i+1]);
        area = labs(area);
        area /= 2;
        lli b = 0;
        for (int i = 0; i < N; i++) {
                b += __gcd<lli>(labs(pts[i+1].x - pts[i].x), labs(pts[i+1].y - pts[i].y));
        }
        cout << (area + 1 - b / 2) << ' ' << b << '\n';
}

int main() {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        solution();
        return 0;
}
