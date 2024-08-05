#include <iostream>
#include <stack>
using namespace std;
#define LLD long long int

int main() {
	LLD N, left, right, index, height, ans, arr[100000];
	stack<LLD> stk;
	while (1) {
		ans = index = left = right = 0;
		scanf("%lld", &N);
		if (!N) break;

		for (int i = 0; i < N; i++) {
			scanf("%lld", &arr[i]);
		}

		while (index < N) {
			if (stk.empty() || arr[stk.top()] <= arr[index]) {
				stk.push(index); index++;
			}
			else if (!stk.empty() && arr[stk.top()] > arr[index]) {
				right = index - 1; height = arr[stk.top()];

				stk.pop();
				if (stk.empty()) left = 0; 
				else left = stk.top() + 1;
				if (ans < height * (right - left + 1)) ans = height * (right - left + 1);
			}
		}

		
		while (!stk.empty()) {
			right = N - 1;
			height = arr[stk.top()];
			stk.pop();
			if (stk.empty()) left = 0;
			else left = stk.top() + 1;

			if (ans < height * (right - left + 1)) ans = height * (right - left + 1);
		}

		
		printf("%lld\n", ans);
	}
}