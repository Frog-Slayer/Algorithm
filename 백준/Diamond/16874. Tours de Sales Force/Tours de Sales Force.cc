#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <queue>
#include <iomanip>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

const int NIL = -1;
const bool LEFT = false;
const bool RIGHT = true;
const double INF = 1e9;
const double EPS = 1e-6;

const int MAX_V_SIZE = 16;

struct Hungarian {
	int N, M;
	vector<vector<double>> w;
	vector<bool> FL, FR;
	vector<int> slack_l, rmatch, lmatch, l_pred, r_pred;
	vector<double> lh, rh, slack;

	Hungarian(int N, int M) : N(N), M(M),  w(N, vector<double>(M)), lh(N), rh(M), lmatch(N, NIL), rmatch(M, NIL), l_pred(N, NIL), r_pred(M, NIL), FL(N), FR(M), slack(M), slack_l(M) {}

	int find_augmenting_path() {
		queue<pair<int, bool>> q;

		fill(all(FL), false), fill(all(FR), false);
		fill(all(slack), INF), fill(all(slack_l), NIL);

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
				double delta = INF;

				for (int r = 0; r < M; r++) if (!FR[r]) delta = min(delta, slack[r]);

				if (delta == INF) return -1;

				for (int i = 0; i < N; i++) if (FL[i]) lh[i] -= delta;

				for (int i = 0; i < M; i++) if (FR[i]) rh[i] += delta;

				for (int i = 0; i < M; i++) {
					if (FR[i]) continue;
					slack[i] -= delta;
						
					if (fabsl(slack[i]) < EPS) {
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

	double hungarian() {
		for (int l = 0; l < N; l++) lh[l] = *max_element(all(w[l]));

		double max_match_weight = 0;

		while (true) {
			int r = find_augmenting_path();
			if (r < 0) break;
			update_match(r);
		}

		for (int l = 0; l < N; l++) max_match_weight += w[l][lmatch[l]];

		return max_match_weight;
	};

};


double dist(const pair<int, int> &p1, const pair<int, int> &p2) {
	return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
}

double w[MAX_V_SIZE][MAX_V_SIZE], dp[1 << MAX_V_SIZE][MAX_V_SIZE];

double TSP(const vector<pair<int, int>> &v, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			w[j][i] = w[i][j] = dist(v[i], v[j]);
		}
	}

	for (int i = 0; i < (1 << N); i++) for (int j = 0; j < N; j++) dp[i][j] = INF;

	dp[1][0] = 0;

	for (int mask = 1; mask < (1 << N); mask++) {
        for (int cur = 0; cur < N; cur++) {
            if (!(mask & (1 << cur))) continue;

            for (int next = 0; next < N; next++) {
                if (mask & (1 << next)) continue;

                int new_mask = mask | (1 << next);
                dp[new_mask][next] = min(dp[new_mask][next], dp[mask][cur] + w[cur][next]);
            }
        }
    }

    double min_tour = INF;

    for (int cur = 0; cur < N; cur++) min_tour = min(min_tour, dp[(1 << N) - 1][cur] + w[cur][0]);

	return min_tour;
}

int main() {
	fastio;

	int N;
	cin >> N;

	vector<vector<pair<int, int>>> clients(N);

	double pre_fire = 0;

	for (int i = 0; i < N; i++) {
		int n;
		cin >> n;

		for (int j = 0; j < n; j++) {
			int x, y;
			cin >> x >> y;

			clients[i].emplace_back(x, y);
		}

		pre_fire += TSP(clients[i], n);
	}

	Hungarian hun(N / 2, N / 2);

	for (int i = 0; i < N / 2; i++) {
		for (int j = N / 2; j < N; j++) {
			vector<pair<int, int>> v(clients[i]);
			v.insert(v.end(), all(clients[j]));

			hun.w[i][j - N / 2] = -TSP(v, v.size());
		}
	}

	cout << fixed << setprecision(6) << pre_fire << ' ' << -hun.hungarian();
}


