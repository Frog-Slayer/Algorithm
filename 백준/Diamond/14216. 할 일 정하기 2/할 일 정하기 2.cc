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
const int MAX = 10000;

int N;
vector<bool> FL, FR;
vector<int> slack, slack_l;

vector<int> rmatch, lmatch;
vector<int> l_pred, r_pred;
vector<vector<int>> w;
vector<int> lh, rh;

int find_augmenting_path() {//find augmenting path and return the index of an unmatched r, if any

	queue<pair<int, bool>> q;//{vertex idx, (0: left, 1: right)}
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

		for (int r = 0; r < N; r++) {//none of R is in FR now
			if (lh[l] + rh[r] - w[l][r] < slack[r]) {
				slack[r] = lh[l] + rh[r] - w[l][r]; 
				if (slack[r] < 0) cout << lh[l] << "+" << rh[r] << "-" << w[l][r] << "=" << slack[r] << '\n';
				slack_l[r] = l;
			}
		}
	}


	while (true) {
		if (q.empty()) {
			int delta = INT_MAX;

			for (int r = 0; r < N; r++) {//optimize delta calculation with slack variable
				if (!FR[r]) delta = min(delta, slack[r]);
			}

			if (delta == INT_MAX) return -1;

			for (int i = 0; i < N; i++){
				if (FL[i]) lh[i] -= delta;

				if (FR[i]) rh[i] += delta;
			}

			for (int i = 0; i < N; i++) {
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

			for (int r = 0; r < N; r++) {
				if (!FR[r] && (slack[r] > lh[l] + rh[r] - w[l][r])) {
					slack[r] = lh[l] + rh[r] - w[l][r];
					slack_l[r] = l;
				}
			}
		}
		else {//left
			for (int r = 0; r < N; r++) {
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

	// default feasible vertex labeling
	for (int l = 0; l < N; l++) lh[l] = *max_element(all(w[l]));

	int max_match_weight = 0;

	while (true) {
		int r = find_augmenting_path();
		if (r < 0) break;
		update_match(r);
	}

	for (int l = 0; l < N; l++) {
		max_match_weight += w[l][lmatch[l]];
	}

	return max_match_weight;
};

void init() {
	w.assign(N, vector<int>(N));
	lh.resize(N);
	rh.resize(N);
	lmatch.resize(N, NIL);
	rmatch.resize(N, NIL);
	l_pred.resize(N, NIL);
	r_pred.resize(N, NIL);

	FL.resize(N);
	FR.resize(N);

	slack.resize(N);
	slack_l.resize(N);
}

int main() {
	fastio;

	cin >> N;

	init();

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> w[i][j];
			w[i][j] = MAX - w[i][j];
		}
	}

	cout << N * MAX - hungarian();
}
