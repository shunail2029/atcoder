#include <vector>

#include "../geometry/basic.cpp"

// area 面積
double area(const Point &a, const Point &b, const Point &c) {
    double len_a = Point::dis(b, c), len_b = Point::dis(c, a), len_c = Point::dis(a, b);
    double s = (len_a + len_b + len_c) / 2.0;
    return sqrt(s * (s - len_a) * (s - len_b) * (s - len_c));
}

// centroid 重心
Point centroid(const Point &a, const Point &b, const Point &c) {
    return (a + b + c) / 3.0;
}

// circumcenter 外心
Point circumcenter(const Point &a, const Point &b, const Point &c) {
    double A = std::acos(Point::dot(b-a, c-a) / Point::dis(a, b) / Point::dis(a, c)),
           B = std::acos(Point::dot(c-b, a-b) / Point::dis(b, c) / Point::dis(b, a)),
           C = std::acos(Point::dot(a-c, b-c) / Point::dis(c, a) / Point::dis(c, b));
    double sin2A = std::sin(A * 2), sin2B = std::sin(B * 2), sin2C = std::sin(C * 2);
    return Point((a.x * sin2A + b.x * sin2B + c.x * sin2C) / (sin2A + sin2B + sin2C),
                 (a.y * sin2A + b.y * sin2B + c.y * sin2C) / (sin2A + sin2B + sin2C));
}

// radius of circumcenter
double rCC(const Point &a, const Point &b, const Point &c) {
    return Point::dis(b, c) / 2.0 / std::sin(std::acos(Point::dot(b-a, c-a) / Point::dis(a, b) / Point::dis(a, c)));
}

// incenter 内心
Point incenter(const Point &a, const Point &b, const Point &c) {
    double len_a = Point::dis(b, c), len_b = Point::dis(c, a), len_c = Point::dis(a, b);
    return Point((a.x * len_a + b.x * len_b + c.x * len_c) / (len_a + len_b + len_c),
                 (a.y * len_a + b.y * len_b + c.y * len_c) / (len_a + len_b + len_c));
}

// radius of incenter
double rIC(const Point &a, const Point &b, const Point &c) {
    return 2.0 * area(a, b, c) / (Point::dis(a, b) + Point::dis(b, c) + Point::dis(c, a));
}

// orthocenter 垂心
Point orthocenter(const Point &a, const Point &b, const Point &c) {
    double A = std::acos(Point::dot(b-a, c-a) / Point::dis(a, b) / Point::dis(a, c)),
           B = std::acos(Point::dot(c-b, a-b) / Point::dis(b, c) / Point::dis(b, a)),
           C = std::acos(Point::dot(a-c, b-c) / Point::dis(c, a) / Point::dis(c, b));
    double tanA = std::tan(A), tanB = std::tan(B), tanC = std::tan(C);
    return Point((a.x * tanA + b.x * tanB + c.x * tanC) / (tanA + tanB + tanC),
                 (a.y * tanA + b.y * tanB + c.y * tanC) / (tanA + tanB + tanC));
}

// excenter 傍心
std::vector<Point> excenter(const Point &a, const Point &b, const Point &c) {
    double len_a = Point::dis(b, c), len_b = Point::dis(c, a), len_c = Point::dis(a, b);
    std::vector<Point> res;
    res.push_back(Point((-a.x * len_a + b.x * len_b + c.x * len_c) / (-len_a + len_b + len_c),
                        (-a.y * len_a + b.y * len_b + c.y * len_c) / (-len_a + len_b + len_c)));
    res.push_back(Point((a.x * len_a - b.x * len_b + c.x * len_c) / (len_a - len_b + len_c),
                        (a.y * len_a - b.y * len_b + c.y * len_c) / (len_a - len_b + len_c)));
    res.push_back(Point((a.x * len_a + b.x * len_b - c.x * len_c) / (len_a + len_b - len_c),
                        (a.y * len_a + b.y * len_b - c.y * len_c) / (len_a + len_b - len_c)));
    return res;
}

// radius of excenter
std::vector<double> rEC(const Point &a, const Point &b, const Point &c) {
    double len_a = Point::dis(b, c), len_b = Point::dis(c, a), len_c = Point::dis(a, b);
    double S = area(a, b, c);
    std::vector<double> res;
    res.push_back(2.0 * S / (-len_a + len_b + len_c));
    res.push_back(2.0 * S / (len_a - len_b + len_c));
    res.push_back(2.0 * S / (len_a + len_b - len_c));
    return res;
}
