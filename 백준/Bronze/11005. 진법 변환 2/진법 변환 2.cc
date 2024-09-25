#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, B;
	scanf("%d%d", &N, &B);

	vector<char> ans;

	while (N) {
		int c = N % B;
		if (c < 10) ans.emplace_back(c + '0');
		else ans.emplace_back(c - 10 + 'A');
		N /= B;
	}

	for (int i = ans.size() - 1; i >=0 ; i--) printf("%c", ans[i]);


}
