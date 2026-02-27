#include <iostream>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main () { 
	fastio;

	int R, C;
	cin >> R >> C;

	vector<vector<int>> floor(R + 1, vector<int>(C + 1));

	int cnt;
	cin >> cnt;

	for (int i = 0; i < cnt; i++) { 
		int x, y;
		cin >> x >> y;
		floor[x][y] = 1;
	}

    vector<vector<int>> ps(R + 1, vector<int>(C + 1, 0));

    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            ps[r][c] = floor[r][c]
                     + ps[r - 1][c]
                     + ps[r][c - 1]
                     - ps[r - 1][c - 1];
        }
    }

    int max_area = 0;

    for (int r1 = 1; r1 <= R; r1++) {
        for (int r2 = r1; r2 <= R; r2++) {
            for (int c1 = 1; c1 <= C; c1++) {
                for (int c2 = c1; c2 <= C; c2++) {

                    int cnt =
                        ps[r2][c2]
                      - ps[r1 - 1][c2]
                      - ps[r2][c1 - 1]
                      + ps[r1 - 1][c1 - 1];

                    if (!cnt) {
                        int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                        if (area > max_area)
                            max_area = area;
                    }
                }
            }
        }
    }

    cout << max_area << "\n";
}

