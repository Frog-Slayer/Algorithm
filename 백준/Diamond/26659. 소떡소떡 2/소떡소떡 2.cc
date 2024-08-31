#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())
#define compressed(x) lower_bound(all(yy), x) - yy.begin();

const int EMPTY = 0;
const int SO = 1;
const int DDUK = 2;

typedef long long ll;
typedef tuple<int, int, int, int> Event;

vector<Event> events;
vector<int> yy;

struct Node {
	ll sdsd = 0;
	bool only = true;
	int lt = EMPTY, rt = EMPTY;
	int lmax = 0, rmax = 0;

	Node () {}

	Node (int t, int length) : lt(t), rt(t), lmax(length), rmax(length), sdsd(length) {}

	Node operator+(const Node &nd) const {
		if (!lt) return nd;
		if (!nd.lt) return *this;
		Node ret;

		ret.only = false;
		ret.lt = lt, ret.rt = nd.rt;
		ret.lmax = lmax, ret.rmax = nd.rmax;
		ret.sdsd = sdsd + nd.sdsd;

		if (rt == nd.lt) {
			ret.sdsd -= min(rmax, nd.lmax);

			if (only && nd.only) {
				ret.only = true;
				ret.lmax = ret.rmax = max(lmax, nd.lmax);
			}
			
			if (only) ret.lmax = max(lmax, nd.lmax);
			if (nd.only) ret.rmax = max(rmax, nd.rmax);
		}
		
		return ret;
	}
};

struct Segtree {
	int N;
	vector<Node> tree;

	void resize(int _N){
		N = _N;
		tree.resize(4 * N);
	}

	void update(int node, int start, int end, int idx, Node& nd) {
		if (idx < start || end < idx) return;
		if (start == end) {
			tree[node] = nd;
			return;
		}

		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, nd);
		update(node * 2 + 1, mid + 1, end, idx, nd);

		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}

	void update(int idx, Node& nd) {
		update(1, 0, N - 1, idx, nd);
	}

	ll query(){
		return tree[1].sdsd;
	}

} tree;

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int l, r, y;
		char t;
		scanf("%d %d %d %c", &l, &r, &y, &t);
		yy.emplace_back(y);
		events.emplace_back(l, y, r - l + 1, t == 'S' ? SO : DDUK);
		events.emplace_back(r + 1, y, 0, EMPTY);
	}

	sort(all(events));
	compress(yy);
	tree.resize(yy.size());

	ll ans = 0;
	for (int i = 0, j = 0; i < events.size(); i = j) {
		while (j < events.size() && get<0>(events[j]) == get<0>(events[i])) {
			auto &[x, y, v, t] = events[j++];
			y = compressed(y);
			Node nd(t, v);
			tree.update(y, nd);
		}
		ans = max(ans, tree.query());
	}

	printf("%lld", ans);
}