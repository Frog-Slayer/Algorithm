#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

typedef long long ll;

struct Node {
	Node() {};
	Node(int start, int end);
	Node(Node* node);

	ll start, end;
	Node* left = NULL;
	Node* right = NULL;

	ll lazy = 0;
	ll sum = 0;
};

vector<int> yy;

Node::Node(int start, int end) {
	this->start = yy[start];
	this->end = yy[end];
}

Node::Node(Node* node) {
	this->start = node->start;
	this->end = node->end;
	this->left = node->left;
	this->right = node-> right;
	this->sum = node->sum;
	this->lazy = node->lazy;
}

Node* init(int start, int end) {
	Node *ret= new Node(start, end);
	if (end - start == 1) return ret;

	int mid = (start + end)/2;
	ret->left = init(start, mid);
	ret->right = init(mid, end);
	return ret;
}

Node* update(Node* node, ll x, ll y1, ll y2) {
	if (y2 <= node->start || node->end <= y1) return node;

	Node *ret = new Node(node);
	if (y1 <= node->start && node->end <= y2) {
		ret->sum += (ret->end - ret->start) * x;
		ret->lazy += x;
		return ret;
	}

	ret->left = update(ret->left, x, y1, y2);
	ret->right = update(ret->right, x, y1, y2);
	ret->sum = ret->left->sum + ret->right->sum + ret->lazy * (ret->end - ret->start);
	return ret;
}

ll query(Node* node, ll y1, ll y2) {
	if (y2 <= node->start || node->end <= y1) return 0;
	if (y1 <= node->start && node->end <= y2) return node->sum;

	ll intersect = min(node->end, y2) - max(node->start, y1);

	if (node->left && node->right) return query(node->left, y1, y2) + query(node->right, y1, y2) + node->lazy * intersect; 
	return node->sum / (node->end - node->start) * intersect;
}

map<int, Node*> open, area;

ll get_area(ll x, ll y1, ll y2) {
	Node *op = (prev(open.upper_bound(x)))->second;
	Node *ar = (prev(area.upper_bound(x)))->second;

	return query(ar, y1, y2) +  query(op, y1, y2) * x;
}

int main() {
	int r, c, n, q, m;
	scanf("%d%d%d%d%d", &r, &c, &n, &q, &m);
	yy.emplace_back(0);
	yy.emplace_back(c);

	vector<tuple<int, int, int, int>> events;

	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		events.emplace_back(x1, 1, y1, y2);
		events.emplace_back(x2, -1, y1, y2);
		yy.emplace_back(y1);
		yy.emplace_back(y2);
	}

	sort(all(events));
	compress(yy);

	open[0] = init(0, yy.size() - 1); 
	area[0] = init(0, yy.size() - 1);

	for (int i = 0, j = 0; i < events.size(); i = j) {
		Node *open_root = new Node(open.rbegin()->second);
		Node *area_root= new Node(area.rbegin()->second);

		while (j < events.size() && get<0>(events[i]) == get<0>(events[j])) j++;

		for (int k = i; k < j; k++) {
			auto &[x, v, y1, y2] = events[k];
			open_root = update(open_root, v, y1, y2);
			area_root = update(area_root, -v * x, y1, y2);
		}

		open[get<0>(events[i])] = open_root;
		area[get<0>(events[i])] = area_root;
	}

	ll l = 0;

	for (int i = 0; i < q; i++) {
		ll x1, y1, x2, y2, v;
		scanf("%lld%lld%lld%lld%lld", &x1, &y1, &x2, &y2, &v);

		x1 = (x1 + l * v) % m;
		y1 = (y1 + l * v) % m;
		x2 = (x2 + l * v) % m;
		y2 = (y2 + l * v) % m;

		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);

		printf("%lld\n", l = get_area(x2, y1, y2) - get_area(x1, y1, y2));
		l %= m;
	}
}