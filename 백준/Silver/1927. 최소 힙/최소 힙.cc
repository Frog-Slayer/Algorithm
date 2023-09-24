#include <iostream>
#include <queue>
using namespace std;

int N, x;
priority_queue<int, vector<int>, greater<>> pq;

int main(){
	scanf("%d", &N);
	for (int i = 0; i < N; i++){
		scanf("%d", &x);
		if (!x) {
			if (pq.empty()) printf("0");
			else {
				printf("%d", pq.top());
				pq.pop();
			}
			printf("\n");
		}
		else pq.push(x);
	}
}