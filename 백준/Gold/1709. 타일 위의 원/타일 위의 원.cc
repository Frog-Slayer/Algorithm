#include <iostream>
using namespace std;

typedef pair<long long, long long> Point;

long long dist(pair<long long, long long> p){
	return 1LL * p.first * p.first + p.second * p.second;
}

int main() {
	long long N;
	scanf("%lld", &N);
	N /= 2;

	Point cur = {0, N - 1};

	long long cnt = 0;
	while (cur.second >= 0){
		long long d = dist({cur.first + 1, cur.second});

		cnt++;
		if (d < N * N) {
			cur.first++;
		}
		else if (d == N * N) {
			cur.first++;
			cur.second--;
		}
		else {
			cur.second--;
		}
	}

	printf("%lld", 4 * cnt);


}