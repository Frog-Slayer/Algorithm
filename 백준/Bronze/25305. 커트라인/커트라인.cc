#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)

int main() {
	fastio;

	int N, k;
	cin >> N >> k;

	vector<int> score(N);

	for (int i = 0; i < N; i++) cin >> score[i];

	sort(score.begin(), score.end(), greater());

	cout << score[k - 1];

}