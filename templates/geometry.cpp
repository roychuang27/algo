using ld = long double;

constexpr ld EPS = 1e-7;

struct Point {
        ld x, y;
        Point(ld _x, ld _y) : x(_x), y(_y) {};
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
bool eq(const Point &p, const Point &q) { return abs(p - q) < EPS; }

struct Circle : Point {
        ld r;
        Circle(ld x, ld y, ld r) : Point(x, y), r(r) {}
        Circle(Point p, ld r) : Point(p), r(r) {}
        friend ostream& operator << (ostream &s, const Circle &c) {return s << '(' << c.x << ", " << c.y << ", " << c.r << ')';}
};

vector<Point> circle_circle_intersect_points(const Circle &p, const Circle &q)  {
        ld d = abs(p - q);
        if (d < EPS) return {};
        if (d > p.r + q.r + EPS) return {};
        if (d < abs(p.r - q.r) - EPS) return {};
        ld rcos = (SQ(d) + SQ(p.r) - SQ(q.r)) / (2.0 * d), rsin;
        if (p.r - abs(rcos) < EPS) {
                rsin = 0;
        } else {
                rsin = sqrt(SQ(p.r) - SQ(rcos));
        }
        Point dir = (q - p) / d;
        Point p1 = p + complex_mul(dir, Point(rcos, rsin));
        Point p2 = p + complex_mul(dir, Point(rcos, -rsin));
        if (eq(p1, p2)) {
                return {p1};
        } else {
                return {p1, p2};
        }
}
