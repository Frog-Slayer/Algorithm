#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int NIL = -1;
const bool LEFT = false;
const bool RIGHT = true;

struct Hungarian {
	int N, M;
	vector<vector<int>> w;
	vector<bool> FL, FR;
	vector<int> slack, slack_l, rmatch, lmatch, l_pred, r_pred, lh, rh;

	Hungarian(int N, int M) : N(N), M(M),  w(N, vector<int>(M)), lh(N), rh(M), lmatch(N, NIL), rmatch(M, NIL), l_pred(N, NIL), r_pred(M, NIL), FL(N), FR(M), slack(M), slack_l(M) {}

	int find_augmenting_path() {
		queue<pair<int, bool>> q;

		fill(all(FL), false), fill(all(FR), false);
		fill(all(slack), INT_MAX), fill(all(slack_l), NIL);

		for (int l = 0; l < N; l++) {
			if (lmatch[l] != NIL) continue;//unmatched l in L
			l_pred[l] = NIL;
			q.emplace(l, LEFT);
			FL[l] = true;
		}

		for (int l = 0; l < N; l++) {
			if (!FL[l]) continue;

			for (int r = 0; r < M; r++) {
				if (lh[l] + rh[r] - w[l][r] < slack[r]) {
					slack[r] = lh[l] + rh[r] - w[l][r]; 
					slack_l[r] = l;
				}
			}
		}

		while (true) {
			if (q.empty()) {
				int delta = INT_MAX;

				for (int r = 0; r < M; r++) if (!FR[r]) delta = min(delta, slack[r]);

				if (delta == INT_MAX) return -1;

				for (int i = 0; i < N; i++) if (FL[i]) lh[i] -= delta;

				for (int i = 0; i < M; i++) if (FR[i]) rh[i] += delta;

				for (int i = 0; i < M; i++) {
					if (FR[i]) continue;
						slack[i] -= delta;
						
						if (!slack[i]) {
							r_pred[i] = slack_l[i];

							if (rmatch[i] == NIL) return i;//unmatched
							q.emplace(i, RIGHT);
							FR[i] = true;
					}
				}
			}

			auto [u, V] = q.front();
			q.pop();

			if (V == RIGHT) {//matched right
				int l = rmatch[u];
				l_pred[l] = u;
				FL[l] = true;
				q.emplace(l, LEFT);

				for (int r = 0; r < M; r++) {
					if (!FR[r] && (slack[r] > lh[l] + rh[r] - w[l][r])) {
						slack[r] = lh[l] + rh[r] - w[l][r];
						slack_l[r] = l;
					}
				}
			}
			else {//left
				for (int r = 0; r < M; r++) {
					if ((rmatch[u] != r && lh[u] + rh[r] == w[u][r]) && !FR[r]) {
						r_pred[r] = u;

						if (rmatch[r] == NIL) return r;//unmatched
						q.emplace(r, RIGHT);
						FR[r] = true;
					}
				}
			}
		}
	}

	void update_match(int cur) {//backtrace augmenting path
		bool toggle = RIGHT;

		while (cur != NIL) {
			if (toggle == RIGHT) {
				rmatch[cur] = r_pred[cur];
				lmatch[r_pred[cur]] = cur;
				cur = r_pred[cur];
			}
			else cur = l_pred[cur];

			toggle = !toggle;
		}
	}

	int hungarian() {
		for (int l = 0; l < N; l++) lh[l] = *max_element(all(w[l]));

		int max_match_weight = 0;

		while (true) {
			int r = find_augmenting_path();
			if (r < 0) break;
			update_match(r);
		}

		for (int l = 0; l < N; l++) max_match_weight += w[l][lmatch[l]];

		return max_match_weight;
	};

};

int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<pair<int, int>> bottle(N), courier(M);

	for (int i = 0; i < N; i++) cin >> bottle[i].first >> bottle[i].second;
	for (int i = 0; i < M; i++) cin >> courier[i].first >> courier[i].second;

	pair<int, int> restaurant;
	cin >> restaurant.first >> restaurant.second;

	auto dist = [](pair<int, int> &p1, pair<int, int> &p2) -> int{
		return abs(p1.first - p2.first) + abs(p1.second - p2.second);
	};

	Hungarian hun(N, M + N - 1);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M + N - 1; j++) {

			int bottle_to_courier = dist(bottle[i], courier[j]);
			int bottle_to_restaurant = dist(bottle[i], restaurant);

			if (j >= M) hun.w[i][j] = -2 * bottle_to_restaurant;
			else hun.w[i][j] = -(bottle_to_courier + bottle_to_restaurant);
		}
	}

	cout << - hun.hungarian();
}


