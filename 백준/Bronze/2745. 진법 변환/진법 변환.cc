#include <iostream>
using namespace std;

int main() {
	char N[35] = {0, };
	int B;
	scanf("%s %d", N, &B);

	int ans = 0, len = 0;

	for (int i = 0; N[i]; i++) {
		ans *= B;
		if (N[i] >= '0' && N[i] <= '9') ans += N[i] - '0';
		else ans += N[i] - 'A' + 10;
	}

	printf("%d", ans);

}