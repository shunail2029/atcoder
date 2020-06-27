#include <algorithm>
#include <vector>

#include "../geometry/basic.cpp"

// Grahum scan グラハムスキャン
std::vector<Point> GrahumScan(std::vector<Point> ps) {
    int n = (int)ps.size();

    std::sort(ps.begin(), ps.end(), [](Point &p, Point &q) -> bool { if (p.x != q.x) return p.x < q.x; else return p.y < q.y; });
    int k = 0;
    std::vector<Point> res(2*n);
    for (int i=0; i<n; ++i) {
        while (k > 1 && Point::cross(ps[i]-res[k-1], res[k-1]-res[k-2]) >= 0) --k;
        res[k++] = ps[i];
    }
    for (int i=n-2, t=k; i>=0; --i) {
        while (k > t && Point::cross(ps[i]-res[k-1], res[k-1]-res[k-2]) >= 0) --k;
        res[k++] = ps[i];
    }
    res.resize(k-1);
    return res;
}

// distance between farthest point pair 最遠点対間距離
// rotating calipers キャリパー法
double rotatingCalipers(std::vector<Point> ps) {
    std::vector<Point> ch = GrahumScan(ps);
    int n = (int)ch.size();
    if (n == 2) return -1.0;

    int si = 0, sj = 0;
    auto comp = [](Point p, Point q) -> bool { if (p.x != q.x) return p.x < q.x; else return p.y < q.y; };
    for (int i=0; i<n; ++i) {
        if (!comp(ch[si], ch[i])) si = i;
        if (comp(ch[sj], ch[i])) sj = i;
    }
    double res = 0.0;
    int i = si, j = sj;
    while (i != si || j != sj) {
        res = std::max(res, Point::dis(ch[i], ch[j]));
        if (Point::cross(ch[(i+1)%n]-ch[i], ch[(j+1)%n]-ch[j]) < 0) i = (i+1)%n;
        else j = (j+1)%n;
    }
    return res;
}
