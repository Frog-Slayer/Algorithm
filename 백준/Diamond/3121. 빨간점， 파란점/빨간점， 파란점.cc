#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;

typedef tuple<int, int, char> Dot;
const int INF = 1000;

struct Node {
	int left = 0;
    int right = 0;
    int total = 0;
	bool is_red_only = false;
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

void update(int node, int idx, int left, int right, int val){
    if (right < idx || idx < left) return;
    if (left == right) {
		tree[node].left = tree[node].right = tree[node].total = tree[node].is_red_only = val;
        return;
    }

    int mid = (left + right) / 2;

    update(node * 2, idx, left, mid, val);
    update(node * 2 + 1, idx, mid + 1, right, val);

    Node &left_sub = tree[node * 2]; 
    Node &right_sub = tree[node * 2 + 1];  

    Node ret;

	if (right_sub.is_red_only) ret.right = right_sub.right + left_sub.right;
	else ret.right = right_sub.right;

	if (left_sub.is_red_only) ret.left = left_sub.left + right_sub.left;
	else ret.left = left_sub.left;

	ret.total = max({left_sub.total, right_sub.total, left_sub.right + right_sub.left});

	if (left_sub.is_red_only && right_sub.is_red_only) ret.is_red_only = true;

    tree[node] = ret;
}

void update(int idx, Dot &t) {
	char c = get<2>(t);
	update(1, idx, 0, N - 1, c == 'R');
}

int solve(){
	sort(v.begin(), v.end());
	tree.resize(4 * N);

	for (int i = 0; i < N; i++) {
		update(i, v[i]);
	}

	for (int i = 0; i < N; i++) p.push_back(i);

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			lines.emplace_back(i, j, v[i], v[j]);
		}
	}

	sort(lines.begin(), lines.end());

	int ans = tree[1].total;

	for (int i = 0, j = 0; i < lines.size(); i = j) {
		while (j < lines.size() && lines[i] == lines[j]) j++;
		for (int k = i; k < j; k++) {
			int a = lines[k].i, b = lines[k].j;

			swap(v[p[a]], v[p[b]]);
			swap(p[a], p[b]);

			a = p[a], b = p[b];

			update(a, v[a]);
			update(b, v[b]);
		}
		ans = max(ans, tree[1].total);
	}
	
	return ans;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		char c;

		scanf("%d %d %c", &x, &y, &c);
		v.emplace_back(x, y, c);
		if (N == 1) {
			printf("%d", c == 'R' ? 1 : 0);
			return 0;
		}
	}

	printf("%d", solve());

}