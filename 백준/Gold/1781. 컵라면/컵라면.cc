#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef tuple<int, int> Problem;

struct compare {

	bool operator() (Problem &p1, Problem &p2) {
		auto &[d1, c1] = p1;
		auto &[d2, c2] = p2;

		return c1 > c2;
	}
};

int main() {
	fastio;

	int N;
	cin >> N;

	vector<Problem> problems(N);

	for (int i = 0; i < N; i++) {
		int d, c;
		cin >> d >> c;

		problems[i] = {d, c};
	}

	sort(all(problems));

	priority_queue<Problem, vector<Problem>, compare> pq;

	for (int i = 0; i < N; i++) {
		auto [d, c] = problems[i];
		
		if (pq.empty()) pq.emplace(problems[i]);
		else {
			if (d > pq.size()) pq.emplace(problems[i]); 
			else {
				auto [dt, ct] = pq.top();

				if (ct < c){
					pq.pop();
					pq.emplace(problems[i]);
				}
			}
		}
	}

	int ans = 0;

	while (!pq.empty()) {
		auto [d, c] = pq.top();
		ans += c;
		pq.pop();
	}

	cout << ans;



}
