#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> v;

int dfs(int cur) {
	
	vector<int> tmp;

	for (int child : v[cur]) {
		tmp.push_back(dfs(child));
	}

	sort(tmp.begin(), tmp.end(), greater());

	int ret = 0;

	for (int i = 0; i < tmp.size(); i++) {
		ret = max(ret, tmp[i] + i);
	}

	return ret + 1;
}

int main(){
	int N;
	scanf("%d", &N);
	v.resize(N);

	for (int i = 0; i < N; i++) {
		int sup;
		scanf("%d", &sup);
		if (sup < 0) continue;

		v[sup].push_back(i);
	}

	printf("%d", dfs(0) - 1);
}