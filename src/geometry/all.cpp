#include <cstdio>
#include <cassert>
#include <algorithm>
#include <complex>
#include <vector>
using namespace std;
#define EPS 1e-8
typedef complex<double> Point;
namespace std {
    bool operator < (const Point &a, const Point &b) {
        return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
    }
    Point operator / (const Point &p, const double &a) {
        return Point(real(p)/a, imag(p)/a);
    }
    Point operator * (const Point &p, const double &a) {
        return Point(real(p)*a, imag(p)*a);
    }
    bool operator == (const Point &a, const Point &b) {
        return real(a) == real(b) && imag(a) == imag(b);
    }
}
typedef vector<Point> Polygon;
struct Line : public vector<Point> { 
    Line () {}
    Line (const Point &a, const Point &b) {
        push_back(a); push_back(b);
    }
};
struct Circle {
    Point c; double r;
    Circle () {}
    Circle (const Point &c, double r) : c(c), r(r) {}
};



double cross (const Point &a, const Point &b) {
    return imag(conj(a)*b);
}
double dot (const Point &a, const Point &b) {
    return real(conj(a)*b);
}
int ccw (Point a, Point b, Point c) {
    b -= a; c -= a;
    if (cross(b, c) > 0)   return +1; //ccw
    if (cross(b, c) < 0)   return -1; //cw
    if (dot(b, c) < 0)     return +2; //c--a--b on line
    if (norm(b) < norm(c)) return -2; //a--b--c on line
    return 0; //a--c--b or (c=b)
}

bool parallelLL (const Line &l, const Line &m) {
    return abs(cross(l[1] - l[0],m[1] - m[0])) > EPS ;
}

bool intersectLL (const Line &l, const Line &m) {
    return abs(cross(l[1]-l[0], m[1]-m[0])) > EPS || // non-parallel
        abs(cross(l[1]-l[0], m[0]-l[0])) < EPS;   // same line
}
bool intersectLS (const Line &l, const Line &s) {
    return cross(l[1]-l[0], s[0]-l[0])*       // s[0] is left of l
        cross(l[1]-l[0], s[1]-l[0]) < EPS; // s[1] is right of l
}
bool intersectLP (const Line &l, const Point &p) {
    return abs(cross(l[1]-p, l[0]-p)) < EPS;
}
bool intersectSS (const Line &s, const Line &t) {
    return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
        ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}
bool intersectSP (const Line &s, const Point &p) {
    return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // triangle inequality
}
Point projection(const Line &l, const Point &p) {
    double t = dot(p-l[0], l[0]-l[1]) / norm(l[0]-l[1]);
    return l[0] + t*(l[0]-l[1]);
}

Point reflection(const Line &l, const Point &p) {
    return p + 2.0 * (projection(l, p) - p);
}

double distanceLP(const Line &l, const Point &p) {
    return abs(p - projection(l, p));
}
double distanceLL(const Line &l, const Line &m) {
    return intersectLL(l, m) ? 0 : distanceLP(l, m[0]);
}
double distanceLS(const Line &l, const Line &s) {
    if (intersectLS(l, s)) return 0;
    return min(distanceLP(l, s[0]), distanceLP(l, s[1]));
}
double distanceSP(const Line &s, const Point &p) {
    const Point r = projection(s, p);
    if (intersectSP(s, r)) return abs(r - p);
    return min(abs(s[0] - p), abs(s[1] - p));
}
double distanceSS(const Line &s, const Line &t) {
    if (intersectSS(s, t)) return 0;
    return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
            min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}
Point crosspoint(const Line &l, const Line &m) {
    double A = cross(l[1] - l[0], m[1] - m[0]);
    double B = cross(l[1] - l[0], l[1] - m[0]);
    if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
    if (abs(A) < EPS) assert(false); // !!!PRECONDITION NOT SATISFIED!!!
    return m[0] + B / A * (m[1] - m[0]);
}

double area (const Polygon &g) {
    double sum = 0;
    for (int i = 0; i < g.size(); i++) 
        sum += cross(g[i], g[(i+1)%g.size()]);
    return abs(sum)/2;
}

// O(N log N)
Polygon convexHull (Polygon g) {
    int n = g.size(), k = 0;
    sort(g.begin(), g.end());
    Polygon ch(2*n);
    for (int i = 0; i < n; ch[k++] = g[i++]) //lower-hull
        while (k >= 2 && ccw(ch[k-2], ch[k-1], g[i]) <= 0) --k;
    for (int i = n-2, t = k+1; i >= 0; ch[k++] = g[i--]) //upper-hull
        while (k >= t && ccw(ch[k-2], ch[k-1], g[i]) <= 0) --k;
    ch.resize(k-1);
    return ch;
}


//O(N)
//return left of l in g
Polygon convexCut (const Polygon &g, const Line &l) {
    Polygon ret;
    for (int i = 0; i < g.size(); i++) {
        Point a = g[i], b = g[(i+1)%g.size()];
        if (ccw(l[0], l[1], a) != -1) ret.push_back(a);
        if (ccw(l[0], l[1], a) * ccw(l[0], l[1], b) < 0)
            ret.push_back(crosspoint(Line(a,b), l));
    }
    return ret;
}

//点と多角形の包含判定
bool inPolygon (const Polygon &g, const Point &p) {
    double sum = 0.0;
    int n = g.size();
    for (int i = 0; i < g.size(); i++) {
        int j = (i+1)%n;
        if (intersectSP(Line(g[i], g[j]), p)) return true;
        sum += arg((g[j]-p)/(g[i]-p));
    }
    return abs(sum) > 1;
}

//法線ベクトルを求める
vector<Point> normal (const Point &p) {
    vector<Point> res;
    res.push_back( Point(-imag(p), real(p)));
    res.push_back( Point(imag(p), -real(p)));
    return res;
}

//2等分線を両方向求める。
vector<Point> bisector (const Point &a, const Point &b) {
    vector<Point> res;
    vector<Point> normals = normal(a-b);
    Point center = (a+b)/2;
    res.push_back(normals[0]);
    res.push_back(normals[1]);
    return res;
}


// 誤差を加味した符号判定
int sign(double a){
    if(a > EPS) return +1;
    if(a < -EPS) return -1;
    return 0;
}

// 誤差を加味した同一判定
bool equal(double a, double b){ 
    return abs(b - a) < EPS;
}


// 円の接線 (中心から偏角thの点で接する接線)
Line circleTangent(Circle& C, double th){
    Point p0 = C.c + polar(C.r, th);
    Point p1 = p0 + polar(1.0, th + M_PI / 2);
    return Line(p0, p1);
}

// 二つの円の共通接線 (Cの中心から接点へのベクトルの偏角を返す)
vector<double> commonTangents(const Circle &C, const Circle &D){
    vector<double> res;
    Point v = D.c - C.c;
    double l = abs(v); // 二円の中心間の距離
    double a = arg(v); // 二円の中心間の偏角
    if(sign(l - abs(C.r - D.r)) > 0){
        // 交わる or 外接 or 離れている
        // 二つの外側接線
        double a1 = acos((C.r - D.r) / l);
        res.push_back(a + a1);
        res.push_back(a - a1);
        if(sign(l - (C.r + D.r)) > 0){
            // 離れている
            // 二つの内側接線
            double a2 = acos((C.r + D.r) / l);
            res.push_back(a + a2);
            res.push_back(a - a2);
        }
    }
    if((equal(abs(C.r - D.r), l) || equal(C.r + D.r, l)) && sign(l) != 0){
        // 内接 or 外接
        // 一つの接線
        res.push_back(a);
    }
    return res;
}


vector<Point> crosspointLC(const Line &l, const Circle &c) {
    vector<Point> ret;
    Point center = projection(l, c.c);
    double d = abs(center - c.c);
    double t = sqrt(c.r * c.r - d * d);
    if (isnan(t)) { return ret; }
    Point vect = (l[1] - l[0]);
    vect /= abs(vect);
    ret.push_back(center - vect * t);//
    if (t > EPS) {
        ret.push_back(center + vect * t);
    }
    return ret;
}
vector<Point> crosspointCC(const Circle &c1, const Circle &c2) {
    vector<Point> ret;
    double d = abs(c1.c - c2.c);
    if (max(c1.r, c2.r) - min(c1.r, c2.r) - d> -EPS) { return ret; }
    double x = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
    Point start = c1.c + (c2.c - c1.c) / d * x;
    Point vect = (c1.c - c2.c) * Point(0.0, 1.0);
    return crosspointLC(Line(start, start + vect), c1);
}

