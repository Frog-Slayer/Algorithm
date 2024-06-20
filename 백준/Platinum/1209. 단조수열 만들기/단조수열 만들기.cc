#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

int N;
vector<int> v, nums;
long long asc_dp[2000][2000], desc_dp[2000][2000];

int main(){
	scanf("%d", &N);
	v.resize(N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &v[i]);
		nums.push_back(v[i]);
	}
	
	sort(nums.begin(), nums.end());
	nums.erase(unique(nums.begin(), nums.end()), nums.end());

	for (int i = 0; i < nums.size(); i++) {
		asc_dp[0][i] = abs(v[0] - nums[i]);	
	}

	for (int i = 1; i < N; i++) {
		long long tmp = LLONG_MAX;
		for (int j = 0; j < nums.size(); j++) {
			tmp = min(asc_dp[i - 1][j], tmp);
			asc_dp[i][j] = tmp + abs(v[i] - nums[j]);
		}
	}

	sort(nums.begin(), nums.end(), greater());

	for (int i = 0; i < nums.size(); i++) {
		desc_dp[0][i] = abs(v[0] - nums[i]);	
	}

	for (int i = 1; i < N; i++) {
		long long tmp = LLONG_MAX;
		for (int j = 0; j < nums.size(); j++) {
			tmp = min(desc_dp[i - 1][j], tmp);
			desc_dp[i][j] = tmp + abs(v[i] - nums[j]);
		}
	}

	long long ans = LLONG_MAX;

	for (int i = 0; i < nums.size(); i++) {
		ans = min(ans, asc_dp[N - 1][i]);
		ans = min(ans, desc_dp[N - 1][i]);
	}

	printf("%lld", ans);
}