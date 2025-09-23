#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

vector<char> dir = {'E', 'W', 'N', 'S'};
vector<int> dx = {0, 0, -1, 1};
vector<int> dy = {1, -1, 0, 0};

struct UF { 
	vector<int> parent;

	UF(int N) : parent(N) { 
		for (int i = 0; i < N; i++) parent[i] = i;
	}

	void merge(int a, int b) { 
		a = find(a), b = find(b);
		if (a == b) return;
		parent[a] = b;
	}

	int find(int a) { 
		if (parent[a] == a) return a;
		return parent[a] = find(parent[a]);
	}
};


int main() {
	fastio;

	int N, M;
	cin >> N >> M;

	vector<string> map(N);

	for (int i = 0; i < N; i++) cin >> map[i];

	UF uf(N * M);

	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < M; j++) { 
			int d;

			for (d = 0; d < 4 && (map[i][j] != dir[d]); d++) ;

			int nx = i + dx[d], ny = j + dy[d];

			uf.merge(i * M + j, nx * M + ny);
		}
	}

	set<int> s;

	for (int p : uf.parent) s.emplace(uf.find(p));

	cout << s.size();
}
