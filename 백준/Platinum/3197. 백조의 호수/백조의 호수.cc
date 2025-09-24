#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

typedef pair<int, int> Point;

const char GLACIER = 'X';
const char WATER = '.';
const char SWAN = 'L';


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

vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};
vector<Point> swans;
vector<Point> next_melt;

int main() {
	fastio;

	int R, C;
	cin >> R >> C;
	vector<string> lake(R);
	UF uf(R * C);

	for (int i = 0; i < R; i++) cin >> lake[i];

	for (int i = 0; i < R; i++) { 
		for (int j = 0; j < C; j++) { 
			if (lake[i][j] == GLACIER){ 
				for (int d = 0; d < 4; d++) { 
					int nx = i + dx[d], ny = j + dy[d];
					if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
					if (lake[nx][ny] == GLACIER) continue; 
					next_melt.emplace_back(i, j);
					break;
				}
			}
			else if (lake[i][j] == SWAN) swans.emplace_back(i, j);
		}
	}

	for (int i = 0; i < R; i++) { 
		for (int j = 0; j < C; j++) { 
			if (lake[i][j] != GLACIER) { 
				for (int d = 0; d < 4; d++) { 
					int nx = i + dx[d], ny = j + dy[d];
					if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
					if (lake[nx][ny] != GLACIER) uf.merge(i * C + j, nx * C + ny);
				}
			}
		}
	}

	auto point_to_index = [&](Point p) { 
		return p.first * C + p.second;
	};

	int ans = 0;

	while (uf.find(point_to_index(swans[0])) != uf.find(point_to_index(swans[1]))) { 
		vector<Point> melt(next_melt);
		next_melt.clear();
		vector<vector<bool>> visited(R, vector<bool>(C));

		for (auto [x, y] : melt) lake[x][y] = WATER;

		for (auto [x, y] : melt) { 
			for (int d = 0; d < 4; d++) { 
				int nx = x + dx[d], ny = y + dy[d];
				if (nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
				if (lake[nx][ny] == GLACIER) { 
					if (!visited[nx][ny]) { 
						visited[nx][ny] = true;
						next_melt.emplace_back(nx, ny);
					}
				}
				else uf.merge(point_to_index(Point(x, y)), point_to_index(Point(nx, ny)));
			}
		}

		ans++;
	}

	cout << ans;
}
