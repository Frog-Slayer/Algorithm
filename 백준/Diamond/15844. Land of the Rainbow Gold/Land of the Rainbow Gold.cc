#include "rainbow.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef long long ll;
const int MAX = 1 << 18;

struct Node {
	Node() {}
	Node(Node *node) {
		val = node->val;
		left = node->left;
		right = node->right;
	}

	ll val;
	Node* left = 0;
	Node* right = 0;
};

struct PST {
	map<int, Node*> root;

	Node* init(int start, int end) {
		Node *nd = new Node();
		if (start == end) return nd;

		int mid = (start + end) / 2;
		nd->left = init(start, mid);
		nd->right = init(mid + 1, end);
		return nd;
	}

	Node* update(Node *node, int start, int end, int idx, int val){
		if (idx < start || end < idx) return node;
		Node *copy = new Node(node);
		copy->val += val;

		if (start == end) return copy;

		int mid = (start + end) / 2;

		if (idx <= mid) copy->left = update(copy->left, start, mid, idx, val);
		else copy->right = update(copy->right, mid + 1, end, idx, val);

		return copy;
	}

	void update(vector<pair<int, int>> &v) {
		sort(all(v));
		v.erase(unique(all(v)), v.end());

		root[0] = init(0, MAX - 1);
		int last = 0;

		for (int i = 0, j = 0; i < v.size(); i++) {
			int r = v[i].first;
			root[r] = new Node(root[last]);
			root[r] = update(root[r], 0, MAX - 1, v[i].second, 1);
			last = r;
		}
	}

	ll query(Node *node, int start, int end, int left, int right) {
		if (right < start || end < left) return 0;
		if (left <= start && end <= right) return node->val;

		int mid = (start + end) / 2;

		return query(node->left, start, mid, left, right) + query(node->right, mid + 1, end, left, right);
	}

	ll query(int top, int bottom, int left, int right) {
		if (top < bottom) return 0;
		auto it_top = root.upper_bound(top); 
		if (it_top == root.begin()) return 0;
		it_top--;

		auto it_bottom = root.lower_bound(bottom);
		if (it_bottom == root.begin()) return query(it_top->second, 0, MAX - 1, left, right);

		it_bottom--;
		return query(it_top->second, 0, MAX - 1, left, right) -  query(it_bottom->second, 0, MAX - 1, left, right);
	}

} vertex, edge_horizontal, edge_vertical, river;


int min_r = MAX, min_c = MAX, max_r, max_c;

void init(int R, int C, int sr, int sc, int M, char* S) {
	vector<pair<int, int>> serpent;
	serpent.emplace_back(sr, sc);

	for (int i = 0; S[i]; i++) {
		switch (S[i]) {
			case 'N': sr--; break;
			case 'E': sc++; break;
			case 'W': sc--; break;
			case 'S': sr++; break;
		}
		serpent.emplace_back(sr, sc);
	}

	vector<pair<int, int>> v, eh, ev, f;

	for (auto &p : serpent) {
		int r = p.first, c = p.second;
		min_r = min(min_r, r);
		min_c = min(min_c, c);
		max_r = max(max_r, r);
		max_c = max(max_c, c);

		//vertex
		v.emplace_back(r - 1, c - 1);
		v.emplace_back(r - 1, c);
		v.emplace_back(r, c - 1);
		v.emplace_back(r, c);

		eh.emplace_back(r - 1, c - 1);
		eh.emplace_back(r, c - 1);

		ev.emplace_back(r - 1, c - 1);
		ev.emplace_back(r - 1, c);

		f.emplace_back(r, c);
	}

	vertex.update(v);
	edge_horizontal.update(eh);
	edge_vertical.update(ev);
	river.update(f);
}

int colour(int ar, int ac, int br, int bc) {
	ll v = vertex.query(br - 1, ar, ac, bc - 1);
	ll ev = edge_vertical.query(br- 1, ar- 1, ac, bc- 1), eh = edge_horizontal.query(br - 1, ar, ac - 1, bc - 1);
	ll r = river.query(br, ar, ac, bc);
	
	int c = (ar < min_r && max_r < br && ac < min_c && max_c < bc) ? 2 : 1;

	return ev + eh - v - r + c;
}