#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

const double EPS = 1e-9;

int cmp(double x, double y)
{
    return (x < y - EPS) ? -1 : (x > y + EPS);
}

struct Point
{
    double x, y;

    Point(double _x = 0, double _y = 0): x(_x), y(_y)   {}

    int cmp(const Point& p)
    {
        if(x != p.x)    return ::cmp(x, p.x);
        return ::cmp(y, p.y);
    }

    #define op(x) bool operator x (const Point& p) const {return cmp(p) x 0;} op(>)   op(<)   op(==)  op(>=)  op(<=)  op(!=)
    #undef op

    Point operator + (const Point& q)   const
    {
        return Point(x + q.x, y + q.y);
    }

    Point operator - (const Point& q)   const
    {
        return Point(x - q.x, y - q.y);
    }

    Point operator * (const Point& q)   const
    {
        return Point(x * q.x, y * q.y);
    }

    Point operator / (const Point& q)   const
    {
        return Point(x / q.x, y / q.y);
    }

    double dot(const Point& q)  const
    {
        return x*q.x + y*q.y;
    }

    double cross(const Point& q)  const
    {
        return x*q.y - y*q.x;
    }

    double norm()
    {
        return x*x + y*y;
    }

    double len()
    {
        return sqrt(norm());
    }

    Point rotate(double alpha)
    {
        double cosa = cos(alpha), sina = sin(alpha);
        return Point(x*cosa - y*sina, x*sina + y*cosa);
    }
};

struct Line
{
    double a, b, c;
    Point A, B;

    Line(double a, double b, double c): a(a), b(b), c(c)    {}

    Line(Point A, Point B): A(A), B(B)
    {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a*A.x + b*B.y); 
    }

    Line(Point P, double k)
    {
        a = -k;
        b = 1;
        c = k*P.x - P.y;
    }

    double f(Point A)
    {
        return a*A.x + b*A.y + c;
    }
};

bool areParallel(Line l1, Line l2)
{
    return cmp(l1.a*l2.b, l1.b*l2.a) == 0;
}

bool areSame(Line l1, Line l2)
{
    return areParallel(l1, l2) && cmp(l1.c*l2.a, l2.c*l1.a) == 0 && cmp(l1.c*l2.b, l1.b*l2.c) == 0;
}

bool areIntersect(Line l1, Line l2, Point &p)
{
    if(areParallel(l1, l2)) return false;
    double dx = l1.b*l2.c - l2.b*l1.c;
    double dy = l1.c*l2.a - l2.c*l1.a;
    double d = l1.a*l2.b - l2.a*l1.b;
    p = Point(dx/d, dy/d);
    return true;
}

struct Circle : Point 
{
    double r;

    Circle(double x = 0, double y = 0, double r = 0) : Point(x, y), r(r) {}
    Circle(Point p, double r) : Point(p), r(r)  {}

    bool contains(Point p)
    {
        return (*this - p).len() <= r + EPS;
    }
};

vector<Point> intersection(Line l1, Circle cir)
{
    double r = cir.r;
    double a = l.a, b = l.b, c = l.c + l.a*cir.x + l.b*cir.y;
    vector<Point> res;

    double
}