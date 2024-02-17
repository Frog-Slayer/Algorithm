#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> Point;

int N;
vector<Point> points; 
bool isChecked[1001][1001];


int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		points.emplace_back(x, y);
	}

	int ans = -1;

	for (int i = 0; i < N; i++){
		for (int j = i + 1; j < N; j++){
			if (isChecked[i][j]) continue;
			int tmp = 0;
			for (int k = j + 1; k < N; k++){
				Point p1 = points[i], p2 = points[j], p3 = points[k];
				if ((p3.first - p1.first) * (p2.second - p1.second) ==
						(p3.second - p1.second) * (p2.first - p1.first)){
					isChecked[i][j] = isChecked[j][i] = isChecked[i][k] = isChecked[k][i] = isChecked[k][j] = isChecked[j][k] = true;
					tmp++;
				}
			}
			if (tmp) ans = max(tmp + 2, ans);
		}
	}


	printf("%d", ans);

}