#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
#define Segment pair<Vector2, Vector2>
#define _USE_MATH_DEFINES

typedef double ld;

const int MAX_NM = 50;
const ld EPSILON = 1e-7;

int N, M;
int wall_cnt;
char room[MAX_NM][MAX_NM + 1];
bool printlog = false;

struct Vector2 {
	ld x;
	ld y;
	ld angle;

	Vector2(){ x = 0; y = 0; angle = 0;}
	
	Vector2(ld _x, ld _y) { x = _x, y = _y; angle = atan2(_y, _x); }

	ld cross(const Vector2& rhs) {
		return x * rhs.y - y * rhs.x;	
	}

	Vector2 operator * (ld r) {
		return Vector2(x * r, y * r);
	}

	Vector2 operator +(const Vector2& rhs) {
		return Vector2(x + rhs.x, y + rhs.y); 
	}

	Vector2 operator -(const Vector2& rhs) {
		return Vector2(x - rhs.x, y - rhs.y); 
	}

	Vector2& operator -=(const Vector2& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		angle = atan2(y, x);
		return *this;
	}

	Vector2& operator +=(const Vector2& rhs) {
		x += rhs.x;
		y += rhs.y;
		angle = atan2(y, x);
		return *this;
	}

	bool operator ==(const Vector2& rhs) const {
		return fabs(x - rhs.x) <= EPSILON && fabs(y - rhs.y) <= EPSILON;
	}

	bool operator !=(const Vector2& rhs) {
		return fabs(x - rhs.x) > EPSILON || fabs(y - rhs.y) > EPSILON;
	}

	bool operator < (const Vector2& rhs) const {
		if (x == rhs.x) return y < rhs.y;
		return x < rhs.x;
	}

	ld length() {
		return x * x + y * y;
	}

	bool is_one_line(const Vector2 &rhs) {
		return fabs(x - rhs.x) <= EPSILON || fabs(y - rhs.y) <= EPSILON ;
	}
};

Vector2 light_source;
vector<Vector2> closest, farthest;
set<Vector2> points;
set<Segment> segs;
map<ld, map<ld, vector<Segment>>> segm;
vector<ld> seg_angle;
set<ld> angles;


void push_points_and_segments(int left, int top, int right, int bottom) {
	Vector2 leftTop(left, top), rightTop(right, top), leftBottom(left, bottom), rightBottom(right, bottom);

	points.insert(leftTop);
	points.insert(rightTop);
	points.insert(rightBottom);
	points.insert(leftBottom);

	segs.insert({leftTop, rightTop});
	segs.insert({leftBottom, rightBottom});
	segs.insert({leftTop, leftBottom});
	segs.insert({rightTop, rightBottom});
}

int ccw(Vector2 &a, Vector2 &b, Vector2 &c){
	ld ret = (b - a).cross(c - a);
	if (fabs(ret) <= EPSILON) return 0; 
	if (ret < 0) return -1;
	return 1;
}

int intersect(Segment &seg1, Segment &seg2){
	Vector2 p1 = seg1.first, p2 = seg1.second;
	Vector2 p3 = seg2.first, p4 = seg2.second;

	int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	if (p1p2 < 0 && p3p4 < 0) return 1;//선분 내에서 
	if (p1p2 == 0 || p3p4 == 0) return 0;//양 끝점에서
	return -1; //교차 안 함
}

ld calc_area(Vector2 &p1, Vector2 &p2) {
	return fabs((p1 - light_source).cross(p2 - light_source))/ 2; }

Vector2 find_intersection(Segment& seg1, Segment& seg2) {
	Vector2 &a = seg1.first, &b = seg1.second, &c = seg2.first, &d = seg2.second;
	ld det = (b - a).cross(d - c);
	return a + (b - a)*((c - a).cross(d - c) / det);
}

void search(Vector2 point) {
	ld angle = (point - light_source).angle;

	if (angles.find(angle) != angles.end()) return;
	angles.insert(angle);
	point = light_source + (point - light_source) * 100; //해당 방향으로 멀리를 봐보자
	Segment light = {light_source, point};
	vector<pair<Vector2, int>> tmp;
	
	for(auto m = segm.lower_bound(angle); m != segm.end(); m++) {

		for (auto mm = (*m).second.begin(); mm != (*m).second.end(); mm++) {
			if ((*mm).first > angle) break;
			for (Segment seg : (*mm).second) {

				int intersect_state = intersect(light, seg);
				if (intersect_state < 0) continue;//교차 안 하는 경우

				Vector2 intersection = find_intersection(seg, light);
				if (intersect_state) tmp.push_back({intersection, 0});//벽에 막혔음
				else {//꼭짓점. 광원-교점-나머지 꼭짓점의 방향을 계산해서 넣어주기
					if (angle != (intersection - light_source).angle) continue;
					Vector2 v1 = seg.first, v2 = seg.second;
					if (v1 != intersection) swap(v1, v2);
					int cc = ccw(v1, light_source, v2);
					tmp.push_back({intersection, cc});
				}
			}
		}
	}

	//광원과의 거리를 기준으로 정렬
	sort(tmp.begin(), tmp.end(), [&](auto v1, auto v2) {
			return (v1.first - light_source).length() < (v2.first - light_source).length();
			});

	Vector2 close = tmp[0].first, far = tmp[0].first;

	for (int i = 0; i < tmp.size(); i++) {
		if (tmp[i].second == 0 || tmp[i].second != tmp[0].second) {
			far = tmp[i].first;
			break; }
	}

	closest.push_back(close);
	farthest.push_back(far);
}

ld follow(Vector2 p, int i) {
	int sz = closest.size();
	if (sz == i) return 0;
	int j = (i + 1) % sz;

	bool match_close = p.is_one_line(closest[j]), match_far = p.is_one_line(farthest[j]);
	ld ret = -1;

	if (match_far){
		ld area = calc_area(p, farthest[j]); 
		ld next = follow(closest[j], i + 1);
		if (next >= 0) ret = area + next;
	}
	else if (match_close) {
		ld area = calc_area(p, closest[j]); 
		ld next = follow(farthest[j], i + 1);
		if (next >= 0) ret = area + next;
	}

	return ret;
}

int main(){
	scanf("%d%d", &N, &M);

	for (int i = 0; i < N; i++) {
		scanf("%s", room[i]);
		for (int j = 0; j < M; j++) {
			if (room[i][j] == '*') light_source = Vector2(i + 0.5, j + 0.5);
			else if (room[i][j] == '#') {
				push_points_and_segments(i, j, i + 1, j + 1);
				wall_cnt++;
			}
			if (i == 0) push_points_and_segments(i, j, i, j + 1);
			else if (i == N - 1) push_points_and_segments(i + 1, j, i + 1, j + 1);
		}
		push_points_and_segments(i, 0, i + 1, 0);
		push_points_and_segments(i, M, i + 1, M);
	}

	for (Segment seg : segs) {
		ld seg_max = max((seg.first - light_source).angle, (seg.second - light_source).angle);
		ld seg_min = min((seg.first - light_source).angle, (seg.second - light_source).angle);

		if (seg_max - seg_min > M_PI) {
			segm[seg_min + 2 * M_PI][seg_max].push_back(seg);
			swap(seg_max, seg_min);
			seg_min -= 2 * M_PI;
		}
		segm[seg_max][seg_min].push_back(seg);
	}

	for (Vector2 p : points) {
		search(p);
	}

	sort(closest.begin(), closest.end(), [](Vector2 v1, Vector2 v2) {
			v1 -= light_source, v2 -= light_source;
			return v1.angle < v2.angle;
			});

	sort(farthest.begin(), farthest.end(), [](Vector2 v1, Vector2 v2) {
			v1 -= light_source, v2 -= light_source;
			return v1.angle < v2.angle;
			});

	ld ans = max(follow(closest[0], 0), follow(farthest[0], 0));

	/**
	for (int i = 0; i < closest.size(); i++) {
		printf("[%d]: (%f, %f) - (%f, %f)\n", i, closest[i].x, closest[i].y, farthest[i].x, farthest[i].y);
	}
	*/

	printf("%.14f\n", N * M - ans - wall_cnt);

}