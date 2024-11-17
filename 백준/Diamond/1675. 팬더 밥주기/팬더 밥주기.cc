#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()
#define lb(v, x) lower_bound(all(v), x) - v.begin()
#define ub(v, x) upper_bound(all(v), x) - v.begin()
#define compress(v) sort(all(v)); v.erase(unique(all(v)), v.end())

struct Seg2D{
  int n;
  vector<vector<int>> a;
  vector<vector<int>> used;

  Seg2D(int n) : n(n), a(2*n), used(2*n) {}

  void fakeUpd(int x, int y){
    for(x += n; x >= 1; x >>= 1) used[x].emplace_back(y);
  }
  void fakeQuery(int x1, int y1, int x2, int y2){
    for(x1 += n, x2 += n+1; x1 < x2; x1 >>= 1, x2 >>= 1){
      if(x1&1){ used[x1].emplace_back(y1); used[x1++].emplace_back(y2); }
      if(x2&1){ used[--x2].emplace_back(y1); used[x2].emplace_back(y2); }
    }
  }
  void prepare(){
    for(int i = 0; i < 2*n; i++){
      if(!used[i].empty()){
        sort(used[i].begin(), used[i].end());
        used[i].erase(unique(used[i].begin(),used[i].end()),used[i].end());
      }
      used[i].shrink_to_fit();
      a[i].resize(used[i].size()*2);
    }
  }
  void upd(int x, int y, int val) {
    for(x += n; x >= 1; x >>= 1){
      int i = lower_bound(used[x].begin(),used[x].end(),y)-used[x].begin() + used[x].size();
      for(a[x][i] = max(a[x][i], val); i > 1; i >>= 1) a[x][i>>1] = max(a[x][i], a[x][i^1]);
    }
  }
  int query1D(int x, int y1, int y2){
    int ret = 0;
    y1 = lower_bound(used[x].begin(),used[x].end(),y1)-used[x].begin();
    y2 = lower_bound(used[x].begin(),used[x].end(),y2)-used[x].begin();
    for(y1 += used[x].size(), y2 += used[x].size()+1; y1 < y2; y1 >>= 1, y2 >>= 1){
      if(y1 & 1) ret = max(ret, a[x][y1++]);
      if(y2 & 1) ret = max(ret, a[x][--y2]);
    }
    return ret;
  }
  // sum of l-th to r-th element(0-indexed)
  int query(int x1, int y1, int x2, int y2) {
    int ret = 0;
    for(x1 += n, x2 += n+1; x1 < x2; x1 >>= 1, x2 >>= 1){
      if(x1&1) ret = max(ret, query1D(x1++, y1, y2));
      if(x2&1) ret = max(ret, query1D(--x2, y1, y2));
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

	Seg2D tree(xx.size());
	sort(all(bamboo));

	int ans = 0;

	for (auto &[w, x, y, l] : bamboo) {
		int lx = lb(xx, x - l);
		int ly = lb(yy, y - l);
		int rx = ub(xx, x + l) - 1;
		int ry = ub(yy, y + l) - 1;

		tree.fakeUpd(lb(xx, x), lb(yy, y));
		tree.fakeQuery(lx, ly, rx, ry);
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
			tree.upd(lb(xx, x), lb(yy, y), upd[k - i] + 1);
			ans = max(ans, upd[k - i] + 1);
		}
	}
	
	cout << ans;
}