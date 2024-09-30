#include <iostream>
using namespace std;
#define fastio cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(false)

const int MAX_K = 20;
int weight[1 << (MAX_K + 1)];
int K, ans = 0;

int dfs(int depth, int root) {
	if (depth > K) return 0;

	int left = dfs(depth + 1, root * 2), right = dfs(depth + 1, root * 2 + 1);
	int mx = max(left, right);
	ans += (mx - left) + (mx - right);
	return weight[root] += mx;
}

int main(){
	fastio;
	cin >> K;

	for (int i = 2; i < (1 << (K + 1)); i++){
		cin >> weight[i];
		ans += weight[i];
	}

	int a = dfs(0, 1);

	printf("%d", ans);

}