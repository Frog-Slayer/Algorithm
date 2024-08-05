#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
vector<tuple<int, int, int, int>> v;
vector<int> xx, yy;
vector<pair<int, int>> ans;
int area[100][100];

bool compare(pair<int, int> &p1, pair<int, int> &p2) {
	if (p1.second == p2.second) return p1.first < p2.first;
	return p1.second > p2.second;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		v.emplace_back(x1, y1, x2, y2);

		xx.emplace_back(x1);
		xx.emplace_back(x2);
		yy.emplace_back(y1);
		yy.emplace_back(y2);
	}

	sort(xx.begin(), xx.end());
	sort(yy.begin(), yy.end());

	xx.erase(unique(xx.begin(), xx.end()), xx.end());
	yy.erase(unique(yy.begin(), yy.end()), yy.end());

	for (int i = 0; i < N; i++) {
		auto [x1, y1, x2, y2] = v[i];
		x1 = lower_bound(xx.begin(), xx.end(), x1) - xx.begin();
		x2 = lower_bound(xx.begin(), xx.end(), x2) - xx.begin();
		y1 = lower_bound(yy.begin(), yy.end(), y1) - yy.begin();
		y2 = lower_bound(yy.begin(), yy.end(), y2) - yy.begin();

		for (int x = x1; x < x2; x++) for (int y = y1; y < y2; y++) area[x][y] = i + 1;
	}

	ans.resize(N);
	for (int i = 0; i < N; i++) ans[i].first = i + 1;

	for (int i = 0; i < xx.size() ; i++) {
		for (int j = 0; j < yy.size(); j++) {
			if (area[i][j]) ans[area[i][j] - 1].second += (xx[i + 1] - xx[i]) * (yy[j + 1] - yy[j]);
		}
	}

	sort(ans.begin(), ans.end(), compare);
	sort(ans.begin(), ans.begin() + K);

	for (int i = 0; i < K; i++) cout << ans[i].first << ' '; 
}