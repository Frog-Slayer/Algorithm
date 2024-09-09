#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>
using namespace std;
#define all(v) v.begin(), v.end()

typedef pair<int, int> Point;
const int INF = 1e9;

int idx, sink, source;
vector<Point> points;

struct Edge{
    int to;
    int capacity;
    int flow = 0;

    Edge *reverse;
    
    Edge(int _to, int _capacity){
        to = _to;
        capacity = _capacity;
    }

    int left() {
        return capacity - flow;
    }

    void push(int amount){
        flow += amount;
        reverse->flow -= amount;
    }
};

vector<vector<Edge*>> edges;

void add_edge(int i, int j, int capacity) {
    Edge *edge = new Edge(j, capacity);
    Edge *rev = new Edge(i, 0);

    edge->reverse = rev;
    rev->reverse = edge;

    edges[i].push_back(edge);
    edges[j].push_back(rev);
}

int ccw(Point& a, Point& b, Point& c) {
	int ret = (b.first - a.first) * (c.second - b.second) - (b.second - a.second) * (c.first - b.first);
	return ret > 0 ? 1 : ret ? -1 : 0;
}

bool intersect(int a, int b, int c, int d) {
	Point p1 = points[a], p2 = points[b], p3 = points[c], p4 = points[d];

	int p1p2 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
	int p3p4 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

	if (p1p2 == 0 && p3p4 == 0) {
		if (p1 > p2) swap(p1, p2);
		if (p3 > p4) swap(p3, p4);
		
		return p2 >= p3 && p4 >= p1;
	}

	return p1p2 <= 0 && p3p4 <= 0;
}

vector<int> level, work;

bool bfs(){
	for (int i = 0; i < level.size(); i++) level[i] = -1;

    queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty()){
        int front = q.front();
        q.pop();

        for (auto edge : edges[front]){
            if (level[edge->to] != -1) continue;
            if (edge->left() > 0) {
                q.push(edge->to); 
                level[edge->to] = level[front] + 1;
            }
        }
    }

    return level[sink] != -1;
}

int dfs(int current, int flow){
    if (current == sink) return flow;

    for (int i = work[current]; i < edges[current].size(); i++){
        Edge *edge = edges[current][i];
        int to = edge->to; 
        int left = edge->left();

        if (level[to] != level[current] + 1 || left <= 0) continue;

        int min_flow = dfs(to, min(flow, left));

        if (min_flow > 0) {
            edge->push(min_flow);
            return min_flow;
        }
    } 

    return 0;
}

int mcmf() {
	int max_flow = 0;

    while (bfs()){
		for (int i = 0; i < work.size(); i++) work[i] = 0;

        while (true) {
			int f = dfs(source, INF);
			if (!f) break;
			max_flow += f;
        }
    }

	return max_flow;
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		points.emplace_back(x, y);
	}

	vector<tuple<int, int, int, int>> red, blue;

	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int c;
			scanf("%d", &c);
			if (i < j){
				red.emplace_back(i, j, c, ++idx);
				sum += c;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int c;
			scanf("%d", &c);
			if (i < j){
				blue.emplace_back(i, j, c, ++idx);
				sum += c;
			}
		}
	}

	sink = ++idx;
	edges.resize(sink  + 1), level.resize(sink + 1), work.resize(sink + 1);

	for (auto &[ri, rj, rc, rid] : red) {
		add_edge(source, rid, rc);

		for (auto &[bi, bj, bc, bid] : blue) if (intersect(ri, rj, bi, bj)) add_edge(rid, bid, INF);
	}

	for (auto &[bi, bj, bc, bid] : blue) add_edge(bid, sink, bc);

	printf("%d", sum - mcmf());
}
