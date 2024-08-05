#include <iostream>
#include <stack>
using namespace std;

typedef long long ll;

const int MAX_N = 100000;

int N, height;
int arr[MAX_N];
ll sum[MAX_N];
stack<ll> stk;

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);

		sum[i] = arr[i];

		if (i) sum[i] += sum[i - 1];
	}

	int left, right, index;
	ll ans;

	ans = index = left = right = 0;
	int a = 0, b = 0;

	while (index < N) {
		if (stk.empty() || arr[stk.top()] <= arr[index]) {
			stk.push(index); 
			index++;
		}
		else if (!stk.empty() && arr[stk.top()] > arr[index]) {
			right = index - 1; height = arr[stk.top()];

			stk.pop();
			if (stk.empty()) left = 0; 
			else left = stk.top() + 1;

			ll tmp = height * (sum[right] - (left ? sum[left - 1] : 0));
			if (ans < tmp) {
				ans = tmp;
				a = left, b = right;
			}
		}
	}
	
	while (!stk.empty()) {
		right = N - 1;
		height = arr[stk.top()];
		stk.pop();

		if (stk.empty()) left = 0;
		else left = stk.top() + 1;

		ll tmp = height * (sum[right] - (left ? sum[left - 1] : 0));
		if (ans < tmp) {
			ans = tmp;
			a = left, b = right;
		}
	}

	printf("%lld\n%d %d", ans, a + 1, b + 1);
}