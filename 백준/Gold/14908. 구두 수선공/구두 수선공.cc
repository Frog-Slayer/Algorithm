#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

struct Task{ 
	int i;
	int t;
	int s;

	bool operator<(const Task &o) { 
		if (t * o.s == o.t * s) return i < o.i;
		return t * o.s < o.t * s;
	}
};

int main() { 
	fastio;

	int N;
	cin >> N;

	vector<Task> tasks(N);

	for (int i = 0; i < N; i++) {
		int t, s;
		cin >> t >> s;

		tasks[i] = {i + 1, t, s};
	}

	sort(all(tasks));

	for (int i = 0; i < N; i++) cout << tasks[i].i << ' ';
}