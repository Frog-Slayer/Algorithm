#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 4e5;
const int MOD = 1e9 + 7;

vector<pair<int, int>> stars;
bool isErased[MAXN + 1];
long long tree[(MAXN + 1) * 4];

void update(int node, int start, int end, int idx, int val){
	if (idx < start || end < idx) return;
	tree[node] += val;
	if (start == end) return;

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);
}

long long query(int node, int start, int end, int left, int right){
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node];
	int mid = (start + end) / 2;
	
	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main(){
	int N;
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++){
		int x, y;
		scanf("%d%d", &x, &y);

		stars.emplace_back(y + 2e5, x + 2e5);
	}

	sort(stars.begin(), stars.end());

	//x축을 기준으로 일단 모두 카운트
	for (int i = 0; i < N; i++){
		update(1, 0, MAXN, stars[i].second, 1);
	}

	long long ans = 0;

	//아래에서부터 별들을 없애감
	for (int i = 0; i < N; i++){
		//같은 y에 있는 경우에는 한번에 다 없앰
		if (!isErased[i]){
			pair<int, int> tmp = {stars[i].first, MAXN};
			int ub = upper_bound(stars.begin(), stars.end(), tmp) - stars.begin();

			for (int j = i; j < ub; j++){
				isErased[j] = true;
				update(1, 0, MAXN, stars[j].second, -1);
			}
		}

		long long left = query(1, 0, MAXN, 0, stars[i].second - 1) % MOD;
		long long right = query(1, 0, MAXN, stars[i].second + 1, MAXN) % MOD; 

		ans += (left * right) % MOD;
		ans %= MOD;
	}

	printf("%lld", ans);
}