#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iterator>
#include <sstream>
#include <complex>
#include <bitset>
#include <iomanip>
#include <cctype>
#include <limits>
#include <numeric>
#include <cmath>
#include <functional>
#include <queue>
using namespace std;
 
#define pf printf
 
/**  স্থানাঙ্ক জ্যামিতি **/
 
// বিন্দু  - স্থানাঙ্ক (x, y)
template< typename T >
struct Point {
    T x;
    T y;
 
    Point(T xx, T yy) : x(xx), y(yy) {}
    Point() : x(), y() {}
};
 
 
// স্থানাঙ্ক lhs(x, y) এবং rhs(x, y) এর জন্য অপারেটর ওভারলোডিং :
 
// minus
template<typename T>
Point<T> operator-( const Point<T>& lhs, const Point<T>& rhs) {
    Point<T> ret( lhs.x - rhs.x, lhs.y - rhs.y);
    return ret;
}
 
// plus
template<typename T>
Point<T> operator+( const Point<T>& lhs, const Point<T>& rhs) {
    Point<T> ret( lhs.x + rhs.x, lhs.y + rhs.y);
    return ret;
}
 
// equal to
template<typename T>
bool operator==( const Point<T>& lhs, const Point<T>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
 
// not equal to
template<typename T>
bool operator!=( const Point<T>& lhs, const Point<T>& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}
 
// division
template<typename T>
Point<T> operator/( const Point<T>& lhs, const T&  rhs) {
    Point<T> ret( lhs.x / rhs, lhs.y / rhs);
    return ret;
}
 
// multiplication (point, constant)
template<typename T>
Point<T> operator*( const Point<T>& lhs, const T&  rhs) {
    Point<T> ret( lhs.x * rhs, lhs.y * rhs);
    return ret;
}
 
// multiplicaton (constant, point)
template<typename T>
Point<T> operator*( const T&  lhs, const Point<T>& rhs) {
    return rhs * lhs;
}
 
// print out a co-ordinate in (x, y) form
template<typename T>
ostream& operator<<( ostream& os, const Point<T>& rhs) {
    os << "(" << rhs.x << ", " << rhs.y << ")" ;
    return os;
}
 
// data structure with point
typedef Point <double> PointD;
typedef Point <int> PointI;
typedef pair <PointD, PointD> SegmentD;
typedef vector <PointD> vp;
 
// Cross product (x1*y2 - x2*y1)
template<typename T>
T cross( const Point<T>& A, const Point<T>& B ) {
    return A.x*B.y - A.y*B.x;
}
 
const double tolerance = 0.000002;
 
 
 
 
/*
vector p1p2 ; p1p3
returns
-1 if p1p3 is clockwise of p1p2 ( "right turn" )
+1 if p1p3 is counter-clockwise of p1p2 ( "left turn " )
0 if parallel (overlapped)
*/
template<typename T>
int  ccw(  const Point<T>& p1,
           const Point<T>& p2, const Point<T>& p3) {
    Point<T> v1 = p2 - p1;
    Point<T> v2 = p3 - p1;
 
    T cp = cross(v1, v2);
 
    //v2 is counter clockwise to v1, so we turned left
    if (cp > 0)
        return +1;
 
    //v2 is clockwise of v1,
    if (cp < 0)
        return -1;
 
    //Vectors v1 and v2 are colinear
    return 0;
}
 
// almost same as above
template<>
int ccw<double>(  const Point<double>& p1,
                  const Point<double>& p2, const Point<double>& p3) {
    Point<double> v1 = p2 - p1;
    Point<double> v2 = p3 - p1;
 
    double cp = cross(v1, v2);
 
    //Vectors v1 and v2 are colinear
    if (abs(cp) < tolerance) {
        return 0;
    }
 
    //v2 is counter clockwise to v1, so we turned left
    if (cp > 0)
        return +1;
 
    //v2 is clockwise of v1,
    if (cp < 0)
        return -1;
 
    // scape from above conditions, so some shit happens
    int up = 3;
    throw up;
}
 
// দুইটি বিন্দুর দূরত্ব
double dist( const PointD& p1, const PointD& p2 ) {
    return sqrt( (p1.x-p2.x) * (p1.x-p2.x) + (p1.y-p2.y) * (p1.y-p2.y) );
}
 
// স্থানাঙ্ক তুলনা (point i point j এর থেকে বড়, ছোট বা সমান কিনা)
bool cmp(const PointI& i, const PointI& j) {
    return (i.x != j.x)  ?
           i.x < j.x :
           i.y < j.y;
}
 
// স্থানাঙ্ক তুলনা (y এর সাপেক্ষে)
int cmpYX(const PointI& a, const PointI& b) {
    if (a.y != b.y) {
        return a.y < b.y;
    }
    return a.x < b.x;
}
 
/* Utility functions  */
template<typename T> T gcd(T a, T b) {
    if (a == 0)
        return b;
    while (b != 0) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}
 
/** সরলরেখা **/
template<class T>
class Line {
public:
    //ax + by + c = 0
    T A, B, C;
 
    //  সরলরেখার উপর অবস্থিত দুইটি বিন্দুর স্থানাঙ্ক দেয়া থাকলে রেখার সমীকরণ in ax + by + c = 0 form
    // i.e. (4, 2) & (6, 4) দিয়ে যায় এমন রেখার সমীকরণ x - y - 2 = 0
    Line(const Point<T>& p1, const Point<T>& p2) {
 
        // Building line
        A = p1.y - p2.y;
        B = p2.x - p1.x;
        C = p1.x*p2.y - p2.x * p1.y;
 
        //make A positive
        if (A < 0 or (A == 0 and B < 0) ) {
            A *= -1;
            B *= -1;
            C *= -1;
        }
 
        int gcdAB = gcd( abs(A), abs(B) );
        int gcdABC = gcd( gcdAB, abs(C) );
 
        A /= gcdABC;
        B /= gcdABC;
        C /= gcdABC;
 
        assert(A * p1.x + B * p1.y + C == 0);
        assert(A * p2.x + B * p2.y + C == 0);
    }
};
 
// সরলরেখা lhs(Ax + By + C = 0) এবং rhs(Ax + By + C = 0) এর জন্য অপারেটর ওভারলোডিং :
 
// less than equal to
template<typename T>
bool operator<( const Line<T>& lhs, const Line<T>& rhs) {
    if (lhs.A != rhs.A)
        return lhs.A < rhs.A;
 
    if (lhs.B != rhs.B)
        return lhs.B < rhs.B;
 
    return lhs.C < rhs.C;
}
 
// দুইটি সরলরেখার উপর অবস্থিত দুইটি করে বিন্দু (x1, y1), (x2, y2) দেয়া আছে । দেখতে হবে সমান্তরাল কিনা
// A - p1(x1, y1), p2(x2, y2)
// B - p3(x3, y3), p4(x4, y4)
// x = calculate cross product of (p2 - p1), (p4 - p3)
// if x < ~0 then parallel
bool isParallel( const SegmentD& seg1, const SegmentD& seg2) {
    double z = cross(seg1.second - seg1.first, seg2.second - seg2.first );
 
    if (abs(z) < tolerance)
        return true;
 
    return false;
}
 
// দুইটি বিন্দু দেয়া থাকলে ওই বিন্দুদ্বয় দ্বারা গঠিত সরলরেখার কোন পাশে তৃতীয় বিন্দুটি অবস্থিত সেটা বের করে
// i.e. (2, 2) is in upside(1) and (2, -2) is in downside(-1) of Line formed with (0, 0) and (4, 0)
// i.e. again (2, 2) is in rightside(1) and (-2, 2) is in leftside(-1) of Line formed with (0, 0) and (0, 4)
// তিনটি বিন্দুই একই সরলরেখায় অবস্থিত হলে ০ রিটার্ন করে।
template<typename T>
int getSide( const Point<T>& A, const Point<T>& B, const Point<T>& P) {
    T z = cross(B - A, P - A);
 
    // If there exists any pair (a,b) such that (a+b) is well defined
    // and a+b-a-b != 0,
    // then the + operation is inexact.
    if (numeric_limits<T>::is_exact) {
        if (z > 0) {
#ifdef DEBUG
            cout << "Points " << A << " " << B << " " << P << " 1 " << endl;
#endif
            return 1;
        }
        if (z < 0) {
#ifdef DEBUG
            cout << "Points " << A << " " << B << " " << P << " -1 " << endl;
#endif
            return -1;
        }
    } else {
        if (z > tolerance)
            return 1;
        if (z < tolerance)
            return -1;
    }
 
#ifdef DEBUG
    cout << "Points " << A << " " << B << " " << P << " 0 " << endl;
#endif
    return 0;
}
 
// তিনটি বিন্দু সরলরৈখিক কিনা
template<typename T>
bool isColinear(  const Point<T>& p1,
                  const Point<T>& p2, const Point<T>& p3) {
    return 0 == getSide(p1, p2, p3);
}
 
// x, a ও b এর মধ্যে কিনা
template<typename T>
bool isBetween(T x, T a, T b) {
    return (a <= x and x <= b) or (b <= x and x <= a);
}
 
// (a1, a2) দ্বারা ও (b1, b2) দ্বারা গঠিত সরলরেখা পরস্পরকে ছেদ করে কিনা
template<typename T>
bool intersects(const Point<T>& a1, const Point<T>& a2,
                const Point<T>& b1, const Point<T>& b2) {
    if (a1 == a2) {
        return isBetween(a1.x, b1.x, b2.x) and
               isBetween(a1.y, b1.y, b2.y);
    }
 
    if ( getSide( a1, a2, b1 ) == getSide( a1, a2, b2 ) )
        return false;
 
 
    if (b1 == b2) {
        return isBetween(b1.x, a1.x, a2.x) and
               isBetween(b1.y, a1.y, a2.y);
    }
 
    if ( getSide( b1, b2, a1) == getSide( b1, b2, a2 ) )
        return false;
 
    return true;
}
 
 // http://stackoverflow.com/a/565282/1162233
 //  দুইটি সরলরেখা (x, y) বিন্দুতে ছেদ করবে কিনা
bool getIntersection( const SegmentD& seg1, const SegmentD& seg2, PointD& inter) {
    PointD p = seg1.first;
    PointD r = seg1.second - seg1.first;
 
    PointD q = seg2.first;
    PointD s = seg2.second - seg2.first;
 
    //P + t*r intersects q + u*s
 
    double rCrossS = cross(r, s);
 
    if ( abs( rCrossS ) < tolerance )
        return false;
 
    double t = cross(q - p, s / rCrossS);
 
    if (t + tolerance < 0 or t - tolerance > 1)
        return false;
    // double u = cross(q-p, r / rCrossS);
 
    inter = p + t * r;
    return true;
}
 
typedef vector<PointI> vecP;
 
// দুইটি সরলরেখা সমান কিনা
bool cmpLine(const vecP& v1, const vecP& v2) {
    int i = 0;
    while( i < v1.size() and i < v2.size() ) {
        if (v1[i] != v2[i]) {
            return cmp(v1[i], v2[i]);
        }
        ++i;
    }
 
    return v1.size() < v2.size();
}
 
// Not completed yet
template<typename T>
struct PolarCmp {
    Point<T> origin;
 
    PolarCmp( const Point<T> ori ) : origin(ori) {}
 
    int operator()(const Point<T>& a, const Point<T>& b) {
        int isCCW = ccw(origin, a, b);
 
        if (isCCW == 1)
            return true;
 
        return false;
    }
};

/*
Clockwise angle between two vector v1(p0->p1) and v2(p0->p2)
using vector dot product property
v1.v2 = v1.x * v2.x + v1.y * v2.y

v1.v2 = |v1| * |v2| * cos(theta)
---------------------------------+
                                 |
                                 +-->  theta = acos(v1.v2 / |v1|*|v2|)
*/
double angleBetween(const PointI &v1, const PointI &v2) {
    double len1 = sqrt(v1.x * v1.x + v1.y * v1.y);
    double len2 = sqrt(v2.x * v2.x + v2.y * v2.y);
    
    double dot = v1.x * v2.x + v1.y * v2.y;
    
    double a = dot / (len1 * len2);
    
    double angleRadian;
    if (a >= 1.0)
        angleRadian = 0.0;
    else if (a <= -1.0)
        angleRadian = M_PI;
    else
        angleRadian = acos(a); // 0..PI
    
    double angleDegree = (angleRadian * 180.0) / M_PI;
    
    // always clockwise
    if(v2.x < 0) {
        angleDegree = 360.0 - angleDegree;
    }
    
    return angleDegree;
}
 
 
int main() {
#ifndef ONLINE_JUDGE
    freopen ("input.txt","r",stdin);
#endif
    Line <int> l = Line <int> (PointI(4, 2), PointI(6, 4));
    pf("%d %d %d\n", l.A, l.B, l.C);
    pf("%d\n", getSide(PointI(0, 0), PointI(4, 0), PointI(2, 2)));
    pf("%d\n", getSide(PointI(0, 0), PointI(4, 0), PointI(2, -2)));
    pf("%d\n", getSide(PointI(0, 0), PointI(4, 0), PointI(8, 0)));
    return 0;
}