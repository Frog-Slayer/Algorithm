#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void){
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N, score, P;

	cin >> N >> score >> P;

	vector<int> arr(N);
	for (int i = 0; i < N; i++) cin >> arr[i];

	if (N >= P && arr.back() >= score) cout << -1; 
	else cout << lower_bound(arr.begin(), arr.end(), score, greater<int>()) - arr.begin() + 1;
}