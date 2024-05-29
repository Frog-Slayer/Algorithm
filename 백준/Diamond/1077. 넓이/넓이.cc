#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

typedef long double ld;
typedef pair<ld , ld> Vector2;
typedef pair<Vector2, Vector2> Segment;

int N, M;
vector<Vector2> poly1, poly2;
vector<Vector2> intersectPoly;

ld ccw(Vector2 a, Vector2 b, Vector2 c){
    return (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);
}

int sign(ld l){
    if (l < 0) return -1;
    if (l) return 1;
    return 0;
}

bool compareY(Vector2 a, Vector2 b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second < b.second;
}

ld calcDist(Vector2 a){
	return (a.first - intersectPoly[0].first) * (a.first - intersectPoly[0].first) + (a.second - intersectPoly[0].second) * (a.second - intersectPoly[0].second);
}

bool compareAngle(Vector2 a, Vector2 b) {
	ld c = ccw(intersectPoly[0], a, b);
	if (c) return c > 0;
	return calcDist(a) < calcDist(b);
}

bool isVector2In(Vector2 &a, vector<Vector2> v){
    for (int i = 0; i < v.size(); i++){
        int j = (i + 1) % v.size();
        if (ccw(v[i], v[j], a) <= 0) {
            return false;
        }
    }
    return true;
}

bool intersect(Segment seg1, Segment seg2){
	Vector2 p1 = seg1.first, p2 = seg1.second;
	Vector2 p3 = seg2.first, p4 = seg2.second;

	ld p1p2 = sign(ccw(p1, p2, p3)) * sign(ccw(p1, p2, p4));
	ld p3p4 = sign(ccw(p3, p4, p1)) * sign(ccw(p3, p4, p2));

	if (p1p2 == 0 && p3p4 == 0) {
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);
		
		return (p2 >= p3 && p4 >= p1);
	}

	return p1p2 <= 0 && p3p4 <= 0;
}

double cross(Vector2 a, Vector2 b) {
    return a.first * b.second - a.second * b.first;
}

Vector2 intersection(Segment seg1, Segment seg2){    
    Vector2 a = seg1.first, b = seg1.second, c = seg2.first, d = seg2.second;

    Vector2 ab = {b.first - a.first, b.second - a.second};
    Vector2 cd = {d.first - c.first, d.second - c.second};

    double det = cross(ab, cd);

    Vector2 ac = {c.first - a.first, c.second - a.second};
    double tmp = cross(ac, cd) / det; 

    Vector2 ret = {ab.first * tmp, ab.second * tmp};
    ret.first += a.first;
    ret.second += a.second;

    return ret;
}

int main(){
    scanf("%d%d", &N, &M);

    // 다각형을 이루는 점들이 반시계 방향으로 주어짐
    for (int i = 0; i < N; i++){
        int x, y;
        scanf("%d%d", &x, &y);

        poly1.emplace_back(x, y);
    }

    for (int i = 0; i < M; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        poly2.emplace_back(x, y);
    }

    //poly1 안에 있는 poly2 점 찾기 + poly2 안에 있는 poly1점을 찾는다.
    for (int i = 0; i < poly1.size(); i++){
        if (isVector2In(poly1[i], poly2)) intersectPoly.push_back(poly1[i]);
    }

    for (int i = 0; i < poly2.size(); i++){
        if (isVector2In(poly2[i], poly1)) intersectPoly.push_back(poly2[i]);
    }

    //교차점 찾기
    for (int i = 0; i < poly1.size(); i++){
        int next = (i + 1) % poly1.size();
        Segment seg1 = {poly1[i], poly1[next]};

        for (int j = 0; j < poly2.size(); j++){
            int next2 = (j + 1) % poly2.size();
            Segment seg2 = {poly2[j], poly2[next2]};

            if (intersect(seg1, seg2)){
                intersectPoly.push_back(intersection(seg1, seg2));
            }
        }
    }

    if (intersectPoly.empty()){
        printf("0.0");
        return 0;
    }

    // 교차 다각형의 점들을 재정렬 
    sort(intersectPoly.begin(), intersectPoly.end(), compareY);
    sort(intersectPoly.begin() + 1, intersectPoly.end(), compareAngle);

    //0, i, i+1이 이루는 삼각형의 크기를 더해감
    double ans = 0;
    for (int i = 1; i < intersectPoly.size() - 1; i++){
        ld t = ccw(intersectPoly[0], intersectPoly[i], intersectPoly[i + 1]) / 2;
        ans += t;
    }

    printf("%.12lf", ans);
}