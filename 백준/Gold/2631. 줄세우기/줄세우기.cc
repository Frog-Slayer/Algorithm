#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, h;
vector<int> height, dp;

int main(){
	scanf("%d", &N);
	for (int i = 0; i < N; i++){
		scanf("%d", &h);
		height.push_back(h);
	}


	for (int i = 0; i < N; i++){
		if (dp.empty()) dp.push_back(height[i]); 
		else if (height[i] > dp.back()) dp.push_back(height[i]); 
		else {
			int pushIdx = lower_bound(dp.begin(), dp.end(), height[i]) - dp.begin();	
			dp[pushIdx] = height[i];
		}
	}
	printf("%ld", N - dp.size());
}