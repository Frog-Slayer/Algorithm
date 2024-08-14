#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, sum;
vector<pair<int, int>> seats;
vector<vector<int>> dp;

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int s;
		scanf("%d", &s);
		sum += s;
		seats.emplace_back(s, i + 1);
	}

	dp.resize(sum + 1);

	sort(seats.begin(), seats.end(), greater<>());

	dp[0].push_back(0);

	int ans = 0;
	for (int i = 0; i < N; i++) {
		int seat = seats[i].first, idx = seats[i].second;
		for (int j = sum / 2; j >= 0; j--) {
			if (dp[j].empty()) continue;//i번째를 넣지 않고서는 j 의석을 채울 수 없음
			if (!dp[j + seat].empty()) continue;//i번째 정당보다 의석 수가 많은 정당들로 채울 수 있었으면 제외 
			ans = max(ans, j + seat);
			dp[j + seat] = dp[j];
			dp[j + seat].push_back(idx);
		}
	}

	printf("%d\n", dp[ans].size() - 1);
	for (int &seat : dp[ans]) if (seat) printf("%d ", seat);

}
