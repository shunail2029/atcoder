#include <cmath>
#include <iostream>

constexpr double EPS = 1e-10;
constexpr double PI = M_PI;

class Point {
    public:
        double x, y;
        Point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) {}
        Point operator=(const Point &p) { x = p.x; y = p.y; return *this; }
};
inline Point operator+(const Point &p) { return Point(p.x, p.y); }
inline Point operator-(const Point &p) { return Point(-p.x, -p.y); }
inline Point operator+(const Point &p, const Point &q) { return Point(p.x + q.x, p.y + q.y); }
inline Point operator-(const Point &p, const Point &q) { return Point(p.x - q.x, p.y - q.y); }
inline Point operator+=(Point &p, const Point &q) { p.x += q.x; p.y += q.y; return p; }
inline Point operator-=(Point &p, const Point &q) { p.x -= q.x; p.y -= q.y; return p; }
inline Point operator*(const Point &p, double v) { return Point(p.x * v, p.y * v); }
inline Point operator*(double v, const Point &p) { return Point(p.x * v, p.y * v); }
inline Point operator/(const Point &p, double v) { return Point(p.x / v, p.y / v); }
inline Point rot(const Point &p, double angle) { return Point(std::cos(angle) * p.x - std::sin(angle) * p.y, std::sin(angle) * p.x + std::cos(angle) * p.y); }
inline Point rot90(const Point &p) { return Point(-p.y, p.x); }
inline double dot(const Point &p, const Point &q) { return p.x * q.x + p.y * q.y; }
inline double abs(const Point &p) { return sqrt(dot(p, p)); }
inline double dis(const Point &p, const Point &q) { return abs(p - q); }
inline bool eq(const Point &p, const Point &q) { return dis(p, q) < EPS; }
inline std::istream& operator>>(std::istream &s, Point &p) { return s >> p.x >> p.y; }
inline std::ostream& operator<<(std::ostream &s, const Point &p) { return s << "(" << p.x << ", " << p.y << ")"; }

class Circle {
    public:
        Point center;
        double r;
        Circle() : center(Point(0.0, 0.0)), r(0.0) {}
        Circle(double cx, double cy, double rr) : center(Point(cx, cy)), r(rr) {}
        Circle(Point p, double rr) : center(p), r(rr) {}
        Circle operator=(const Circle &c) { center = c.center; r = c.r; return *this; }
};
inline Circle mv(const Circle &c, double x, double y) { return Circle(c.center.x + x, c.center.y + y, c.r); }
inline bool eq(const Circle &c, const Circle &d) { return dis(c.center, d.center) < EPS && abs(c.r - d.r) < EPS; }
inline std::ostream& operator<<(std::ostream &s, const Circle &c) { return s << "(" << c.center.x << ", " << c.center.y << ", " << c.r << ")"; }
