#include <cmath>
#include <iostream>

constexpr double EPS = 1e-10;
constexpr double PI = M_PI;

class Point {
    public:
        double x, y;
        Point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) {}
        Point(const Point &p) : x(p.x), y(p.y) {}
        Point& operator=(const Point &p) { x = p.x; y = p.y; return *this; }
        Point operator+() const { return Point(x, y); }
        Point operator-() const { return Point(-x, -y); }
        Point operator+(const Point &p) const { return Point(*this) += p; }
        Point operator-(const Point &p) const { return Point(*this) -= p; }
        Point operator*(double v) const { return Point(*this) *= v; }
        Point operator/(double v) const { return Point(*this) /= v; }
        Point& operator+=(const Point &p) { x += p.x; y += p.y; return *this; }
        Point& operator-=(const Point &p) { x -= p.x; y -= p.y; return *this; }
        Point& operator*=(double v) { x *= v; y *= v; return *this; }
        Point& operator/=(double v) { x /= v; y /= v; return *this; }
        friend Point operator*(double v, const Point &p) { return p * v; }
        friend Point rot(const Point &p, double angle) { return Point(std::cos(angle) * p.x - std::sin(angle) * p.y, std::sin(angle) * p.x + std::cos(angle) * p.y); }
        friend Point rot90(const Point &p) { return Point(-p.y, p.x); }
        friend double dot(const Point &p, const Point &q) { return p.x * q.x + p.y * q.y; }
        friend double abs(const Point &p) { return sqrt(dot(p, p)); }
        friend double dis(const Point &p, const Point &q) { return abs(p - q); }
        friend bool eq(const Point &p, const Point &q) { return dis(p, q) < EPS; }
        friend std::istream& operator>>(std::istream &s, Point &p) { return s >> p.x >> p.y; }
        friend std::ostream& operator<<(std::ostream &s, const Point &p) { return s << "(" << p.x << ", " << p.y << ")"; }
};

class Circle {
    public:
        Point center;
        double r;
        Circle() : center(Point(0.0, 0.0)), r(0.0) {}
        Circle(double cx, double cy, double rr) : center(Point(cx, cy)), r(rr) {}
        Circle(Point p, double rr) : center(p), r(rr) {}
        Circle& operator=(const Circle &c) { center = c.center; r = c.r; return *this; }
        friend Circle mv(const Circle &c, double x, double y) { return Circle(c.center.x + x, c.center.y + y, c.r); }
        friend bool eq(const Circle &c, const Circle &d) { return dis(c.center, d.center) < EPS && abs(c.r - d.r) < EPS; }
        friend std::ostream& operator<<(std::ostream &s, const Circle &c) { return s << "(" << c.center.x << ", " << c.center.y << ", " << c.r << ")"; }
};
