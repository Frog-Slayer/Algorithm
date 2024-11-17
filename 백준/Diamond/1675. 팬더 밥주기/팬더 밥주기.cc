//Seg2D Offline Bottom-up implementation: https://infossm.github.io/blog/2019/11/15/2D-segment-tree/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()
#define lb(v, x) lower_bound(all(v), x) - v.begin()
#define ub(v, x) upper_bound(all(v), x) - v.begin()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

typedef unsigned short us;

struct Segtree_2D{
  int n;
  vector<vector<us>> tree;
  vector<vector<us>> used;

  Segtree_2D(int n) : n(n), tree(2 * n), used(2 * n) {}

  void fake_update(int x, int y){
    for (x += n; x >= 1; x >>= 1) used[x].emplace_back(y);
  }

  void fake_query(int x1, int y1, int x2, int y2){
    for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1){
      if(x1 & 1){ 
		  used[x1].emplace_back(y1); 
		  used[x1++].emplace_back(y2);
	  }

      if(x2 & 1){ 
		  used[--x2].emplace_back(y1); 
		  used[x2].emplace_back(y2); 
	  }
    }
  }

  void prepare(){
    for(int i = 0; i < 2 * n; i++){
		if (!used[i].empty()) { 
			compress(used[i]);
		}

		tree[i].resize(used[i].size() * 2);
    }
  }

  void update(int x, int y, us val) {
    for(x += n; x >= 1; x >>= 1){
		int i = lb(used[x], y) + used[x].size();
		tree[x][i] = max(tree[x][i], val);

		for(; i > 1; i >>= 1) tree[x][i>>1] = max(tree[x][i], tree[x][i^1]);
    }
  }

  us query(int x, int y1, int y2){
    us ret = 0;
    y1 = lb(used[x], y1);
    y2 = lb(used[x], y2);

    for (y1 += used[x].size(), y2 += used[x].size() + 1; y1 < y2; y1 >>= 1, y2 >>= 1){
		if(y1 & 1) ret = max(ret, tree[x][y1++]);
		if(y2 & 1) ret = max(ret, tree[x][--y2]);
    }
    return ret;
  }

  us query(int x1, int y1, int x2, int y2) {
    us ret = 0;

    for (x1 += n, x2 += n+1; x1 < x2; x1 >>= 1, x2 >>= 1){
      if (x1 & 1) ret = max(ret, query(x1++, y1, y2));
      if (x2 & 1) ret = max(ret, query(--x2, y1, y2));
    }

    return ret;
  }
};

int main() {
	fastio;

	int N;
	cin >> N;


	vector<tuple<int, int, int, int>> bamboo;
	vector<int> xx, yy;

	for (int i = 0; i < N; i++) {
		int x, y, w, l;
		cin >> x >> y >> w >> l;
		bamboo.emplace_back(w, x + y, x - y, l);//회전
		xx.emplace_back(x + y);
		yy.emplace_back(x - y);
	}

	compress(xx);
	compress(yy);

	Segtree_2D tree(xx.size());
	sort(all(bamboo));

	int ans = 0;

	for (auto &[w, x, y, l] : bamboo) {
		int lx = lb(xx, x - l);
		int ly = lb(yy, y - l);
		int rx = ub(xx, x + l) - 1;
		int ry = ub(yy, y + l) - 1;

		tree.fake_update(lb(xx, x), lb(yy, y));
		tree.fake_query(lx, ly, rx, ry);
	}

	tree.prepare();

	for (int i = 0, j = 0; i < N; i = j) {
		while (j < N && get<0>(bamboo[j]) == get<0>(bamboo[i])) j++;

		vector<int> upd;

		for (int k = i; k < j; k++) {
			auto &[w, x, y, l] = bamboo[k];
			int lx = lb(xx, x - l);
			int ly = lb(yy, y - l);
			int rx = ub(xx, x + l) - 1;
			int ry = ub(yy, y + l) - 1;

			upd.emplace_back(tree.query(lx, ly, rx, ry));
		}

		for (int k = i; k < j; k++) {
			auto &[w, x, y, l] = bamboo[k];
			tree.update(lb(xx, x), lb(yy, y), upd[k - i] + 1);
			ans = max(ans, upd[k - i] + 1);
		}
	}
	
	cout << ans;
}