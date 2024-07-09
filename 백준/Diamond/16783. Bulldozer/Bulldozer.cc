#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;

typedef tuple<int, int, long long> Dot;
const int INF = 1000;

struct Node{
    long long left = 0;
    long long right = 0;
    long long total = 0;
    long long sum = 0;
};

struct Line {
	int i, j;
	long long dx, dy;

	Line(int _i, int _j, Dot dot_i, Dot dot_j) {
		i = _i;
		j = _j;
		dx = get<0>(dot_i) - get<0>(dot_j); 
		dy = get<1>(dot_i) - get<1>(dot_j); 
	}
	
	bool operator==(const Line &rhs) {
		return dx * rhs.dy == dy * rhs.dx;
	}

	bool operator<(const Line &rhs) {
		long long slp = dy * rhs.dx, r_slp = rhs.dy * dx;
		return tie(slp, i, j) < tie(r_slp, rhs.i, rhs.j);
	}
};

int N;
vector<Dot> v;
vector<int> p;
vector<Node> tree; 
vector<Line> lines;

void update(int node, int idx, int left, int right, long long val){
    if (right < idx || idx < left) return;
    if (left == right) {
		tree[node].left += val;
		tree[node].right += val;
		tree[node].sum += val;
		tree[node].total += val;
        return;
    }

    int mid = (left + right) / 2;

    update(node * 2, idx, left, mid, val);
    update(node * 2 + 1, idx, mid + 1, right, val);

	Node &left_sub = tree[node * 2];
    Node &right_sub = tree[node * 2 + 1];

    Node ret;
    ret.left= max(left_sub.left, left_sub.sum + right_sub.left);
    ret.right = max(right_sub.right, right_sub.sum + left_sub.right);
    ret.sum = left_sub.sum + right_sub.sum;
	ret.total = max({ret.left, ret.right, left_sub.total, right_sub.total, left_sub.right + right_sub.left});

    tree[node] = ret;
}

void update(int i, long long d) {
	update(1, i, 0, N -1, d);
}

long long solve(){
	sort(v.begin(), v.end());
	tree.resize(4 * N);

	for (int i = 0; i < N; i++) {
		update(i, get<2>(v[i]));
	}

	for (int i = 0; i < N; i++) p.push_back(i);

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			lines.emplace_back(i, j, v[i], v[j]);
		}
	}

	sort(lines.begin(), lines.end());

	long long ans = tree[1].total;

	for (int i = 0, j = 0; i < lines.size(); i = j) {
		while (j < lines.size() && lines[i] == lines[j]) j++;
		for (int k = i; k < j; k++) {
			int a = lines[k].i, b = lines[k].j;

			swap(v[p[a]], v[p[b]]);
			swap(p[a], p[b]);

			a = p[a], b = p[b];

			update(a, get<2>(v[a]) - get<2>(v[b]));
			update(b, get<2>(v[b]) - get<2>(v[a]));
		}
		ans = max(ans, tree[1].total);
	}
	
	return ans;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y, w;

		scanf("%d %d %d", &x, &y, &w);
		v.emplace_back(x, y, w);
	}

	long long ans = solve();
	printf("%lld", ans > 0 ? ans : 0);

}