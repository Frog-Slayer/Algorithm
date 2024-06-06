#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define LEFT_CHILD node * 2
#define RIGHT_CHILD node * 2 + 1

typedef pair<int, int> pii;
typedef pair<pii, int> piii; 

const int MAX_N = 1e5;
int N;
int tree[4 * MAX_N + 8];

vector<pair<pii, pii>> v;
priority_queue<piii, vector<piii>, greater<>> pq;


void update(int node, int start, int end, int idx, int val){ 
	if (idx < start || end < idx) return;

	if (start == end) {
		tree[node] = max(tree[node], val);
		return;
	}

	int mid = (start + end) >> 1;

	update(LEFT_CHILD, start, mid, idx, val);
	update(RIGHT_CHILD, mid + 1, end, idx, val);

	tree[node] = max(tree[LEFT_CHILD], tree[RIGHT_CHILD]);
}

int query(int node, int start, int end, int left, int right) {
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) >> 1;

	return max(query(LEFT_CHILD, start, mid, left, right), query(RIGHT_CHILD, mid + 1, end, left, right));
}

void update(int idx, int val){
	update(1, 0, MAX_N, idx, val);
}

int query(int left, int right) {
	return query(1, 0, MAX_N, left, right);
}

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		int lb_x, lb_y, rt_x, rt_y;
		scanf("%d%d%d%d", &lb_x, &lb_y, &rt_x, &rt_y);
		v.push_back({{lb_x, lb_y}, {rt_x, rt_y}});
	}

	sort(v.begin(), v.end());

	for (int i = 0; i < N; i++) {
		pii lb = v[i].first, rt = v[i].second;

		while (!pq.empty()){
			piii top = pq.top();
			int x = top.first.first, y = top.first.second, to_update = top.second;
			
			if (x < lb.first) {
				update(y, to_update);
				pq.pop();
			}
			else break;
		}

		int q = query(0, lb.second - 1);
		pq.push({rt, q + 1});
	}

	while (!pq.empty()){
		piii top = pq.top();
		int x = top.first.first, y = top.first.second, to_update = top.second;
			
		update(y, to_update);
		pq.pop();
	}
	
	printf("%d", tree[1]);
}