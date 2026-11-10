using ld = long double;

constexpr ld EPS = 1e-7;

struct Point {
        ld x, y;
        Point(ld _x, ld _y):
                x(_x),
                y(_y) {};

        string str() const {
                ostringstream o;
                o << '(' << x << ", " << y << ')';
                return o.str();
        }
};

Point operator+(const Point &lhs, const Point &rhs) {
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}
Point operator-(const Point &lhs, const Point &rhs) {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}
Point operator*(const ld &lhs, const Point &rhs) {
        return Point(lhs * rhs.x, lhs * rhs.y);
}
Point operator*(const Point &lhs, const ld &rhs) {
        return Point(lhs.x * rhs, lhs.y * rhs);
}
Point operator/(const Point &lhs, const ld &rhs) {
        return Point(lhs.x / rhs, lhs.y / rhs);
}
Point complex_mul(const Point &lhs, const Point &rhs) {
        return Point(lhs.x * rhs.x - lhs.y * rhs.y, lhs.x * rhs.y + lhs.y * rhs.x);
}
ld dot(const Point &lhs, const Point &rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
}
ld det(const Point &lhs, const Point &rhs) {
        return lhs.x * rhs.y - lhs.y * rhs.x;
}
ld abs(const Point &p) {
        return sqrt(pow(p.x, 2) + pow(p.y, 2));
}
bool eq(const Point &p, const Point &q) {
        return abs(p - q) < EPS;
}

struct Circle : Point {
        ld r;
        Circle(ld x, ld y, ld r):
                Point(x, y),
                r(r) {
        }
        Circle(Point p, ld r):
                Point(p),
                r(r) {
        }

        string str() const {
                ostringstream o;
                o << '(' << x << ", " << y << ", " << r << ')';
                return o.str();
        }
};

vector<Point> circle_circle_intersect_points(const Circle &p, const Circle &q) {
        ld d = abs(p - q);
        if (d < EPS) {
                return {};
        }
        if (d > p.r + q.r + EPS) {
                return {};
        }
        if (d < abs(p.r - q.r) - EPS) {
                return {};
        }
        ld rcos = (pow(d, 2) + pow(p.r, 2) - pow(q.r, 2)) / (2.0 * d), rsin;
        if (p.r - abs(rcos) < EPS) {
                rsin = 0;
        } else {
                rsin = sqrt(pow(p.r, 2) - pow(rcos, 2));
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
