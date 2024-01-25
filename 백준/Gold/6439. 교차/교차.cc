#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> Point;
typedef pair<Point, Point> Segment;

int ccw (Point a, Point b, Point c){
    int x1 = a.first, y1 = a.second;
    int x2 = b.first, y2 = b.second;
    int x3 = c.first, y3 = c.second;

    int cc = (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3);

    if (cc < 0) return -1;
    return cc > 0;
}

bool isCrossing(Segment seg1, Segment seg2){

    Point p1 = seg1.first, p2 = seg1.second;
    Point p3 = seg2.first, p4 = seg2.second;

    int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
    int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

    if (!p1p2 && !p3p4){
        if (p1 > p2) swap(p1, p2);
        if (p3 > p4) swap(p3, p4);
        return (p3 <= p2 && p1 <= p4);
    }

    return p1p2 <= 0 && p3p4 <= 0;
}


int main(){
    int T;
    scanf("%d", &T);
    
    while (T--){
        int xs, ys, xe, ye, xl, yt, xr, yb;
        scanf("%d%d%d%d%d%d%d%d", &xs, &ys, &xe, &ye, &xl, &yt, &xr, &yb);

        Segment segment = {{xs ,ys}, {xe, ye}};
        
        vector<Segment> rectangle;

        if (xl > xr) swap(xl, xr);
        if (yb > yt) swap(yb, yt);

        rectangle.push_back({{xl, yb}, {xl, yt}});
        rectangle.push_back({{xl, yt}, {xr, yt}});
        rectangle.push_back({{xr, yt}, {xr, yb}});
        rectangle.push_back({{xl, yb}, {xr, yb}});

        Point ps = segment.first, pe = segment.second;

        bool ans = (ps.first >= xl && ps.first <= xr && ps.second >= yb && ps.second <= yt) 
                && (pe.first >= xl && pe.first <= xr && pe.second >= yb && pe.second <= yt);

        for (int i = 0; i < 4; i++){
            if (isCrossing(rectangle[i], segment)) ans = true;
        }

        printf("%c\n", ans ? 'T' : 'F');
    }
}