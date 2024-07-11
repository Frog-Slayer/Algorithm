#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX_DIST = 200000000;
int N;

struct Vect{
	int idx;
	int x;
	int y;
	int op;

	Vect(int _idx, int _x, int _y, int _op) {
		idx = _idx;
		op = _op;

		switch (op) {
			case 1: x = _x, y = _y; break;
			case 2: x = -_x, y = _y; break;
			case 3: x = _x, y = -_y; break;
			case 4: x = -_x, y = -_y; 
		}
	}

	bool operator<(const Vect& rhs) {
		return tie(x, y, idx) < tie(rhs.x, rhs.y, rhs.idx);
	}

	int dist(Vect &rhs) {
		if (idx == rhs.idx) return MAX_DIST;
		return (rhs.x - x) * (rhs.x - x) + (rhs.y - y) * (rhs. y - y);
	}

};

vector<Vect> v;

bool by_y(Vect &l, Vect &r) { return tie(l.y, l.x, l.idx) < tie(r.y, r.x, r.idx); }
int pow(int a) { return a * a; }

pair<int, int> solve(int start, int end) {

	if (start == end) return {start, end};

	int min_dist = v[start].dist(v[end]);
	pair<int, int> ret = { start, end };

	int mid = (start + end) / 2;
	pair<int, int> left_min = solve(start, mid), right_min = solve(mid + 1, end);

	int left_dist = v[left_min.first].dist(v[left_min.second]);
	int right_dist = v[right_min.first].dist(v[right_min.second]);

	if (left_dist < min_dist) { min_dist = left_dist; ret = left_min; }
	if (right_dist < min_dist) { min_dist = right_dist; ret = right_min; }

	double dist = sqrt(min_dist);

	vector<Vect> candidate;
	for (int i = mid; i >= start && v[i].x >= v[mid].x - dist; i--) candidate.emplace_back(i, v[i].x, v[i].y, 1);
	for (int i = mid + 1; i <= end && v[i].x <= v[mid].x + dist; i++) candidate.emplace_back(i, v[i].x, v[i].y, 1);

	sort(candidate.begin(), candidate.end(), by_y);

	for (int i = 0; i < candidate.size(); i++) {
		for (int j = i + 1; j < candidate.size(); j++) {
			if (pow(candidate[i].y - candidate[j].y) >= min_dist) break;
			int cand_dist = candidate[i].dist(candidate[j]);
			if (cand_dist < min_dist) {
				min_dist = cand_dist;
				ret = { candidate[i].idx, candidate[j].idx };
			}
		}
	}

	return ret;
}

int main() {
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (x >= 0) {
			if (y >= 0) v.emplace_back(i, x, y, 1);
			else v.emplace_back(i, x, y, 3);
		}
		else {
			if (y >= 0) v.emplace_back(i, x, y, 2);
			else v.emplace_back(i, x, y, 4);
		}
	}

	sort(v.begin(), v.end());
	pair<int, int> ans = solve(0, N-1);

	switch(v[ans.second].op) {
		case 1: v[ans.second].op = 4; break;
		case 2: v[ans.second].op = 3; break;
		case 3: v[ans.second].op = 2; break;
		case 4: v[ans.second].op = 1; break;
	}

	printf("%d %d %d %d", v[ans.first].idx, v[ans.first].op, v[ans.second].idx, v[ans.second].op);
}