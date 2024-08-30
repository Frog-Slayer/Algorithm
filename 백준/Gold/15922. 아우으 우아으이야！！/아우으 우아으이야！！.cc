#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N;
	scanf("%d", &N);

	int s, e;
	int ans = 0;

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		if (!i) {
			s = x, e = y;
		}
		else {
			if (e < x) {
				ans += (e - s);
				s = x, e = y;
			}
			else e = max(e, y);
		}
	}

	ans += (e - s);

	printf("%d", ans);
}