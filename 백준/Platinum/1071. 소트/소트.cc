#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_NUM = 1000;
int N;
int cnt[MAX_NUM + 1];
vector<int> num;

void _print(int a) {
	while (cnt[a]){
		printf("%d ", a);
		cnt[a]--;
	}
}

int main(){
	scanf("%d", &N);

	for (int n, i = 0; i < N; i++) {
		scanf("%d", &n);
		cnt[n]++;
		num.emplace_back(n);
	}

	sort(num.begin(), num.end());

	for (int i = 0; i < N; i++) {
		if (!cnt[num[i]]) continue;
		if (binary_search(num.begin() + i, num.end(), num[i] + 1) && cnt[num[i] + 1]) {
			auto lb = lower_bound(num.begin() + i, num.end(), num[i] + 2);
			if (lb != num.end() && cnt[*lb]) {
				_print(num[i]);
				printf("%d ", *lb);
				cnt[*lb]--;
			}
			else {
				_print(num[i] + 1);
				_print(num[i]);
			}
		}
		else {
			_print(num[i]);
		}
	}

}