#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef long long ll;
int N;

struct Event {
	int val;
	int y;
	int len;
	char t;

	Event(int _val, int _y, int _len, char _t) : val(_val), y(_y), len(_len), t(_t) {}

	bool operator<(const Event& e) {
		if (val != e.val) return val < e.val;
		return y < e.y;
	}
};

map<int, vector<Event>> events;
multimap<int, char> yy;

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int r, l, y;
		char t;
		scanf("%d %d %d %c", &l, &r, &y, &t);
		events[l].emplace_back(1, y, r + 1 - l, t);
		events[r + 1].emplace_back(-1, y, r + 1 - l, t);
	}


	ll cur = 0, cnt = 0, ans = 0;

	for (auto &m : events) {
		int x = m.first;
		vector<Event> &e = m.second;

		sort(e.begin(), e.end());

		for (auto &[val, y, len, t] : e)  {
			if (val == 1) {
				auto it = yy.insert({y, t});
				auto prv = prev(it);
				auto nxt = next(it);

				if (it != yy.begin() && prv->second == t) cnt++;
				if (nxt != yy.end() && nxt->second == t) cnt++;
				if (it != yy.begin() && nxt != yy.end() && prv->second == nxt->second) cnt--;

				cur += len;
			}
			else {
				auto it = yy.lower_bound(y);
				auto prv = prev(it);
				auto nxt = next(it);

				if (it != yy.begin() && prv->second == t) cnt--;
				if (nxt != yy.end() && nxt->second == t) cnt--;
				if (it != yy.begin() && nxt != yy.end() && prv->second == nxt->second) cnt++;

				cur -= len;
				yy.erase(it);
			}
		}

		if (!cnt) ans = max(ans, cur);
	}

	printf("%lld", ans);
}