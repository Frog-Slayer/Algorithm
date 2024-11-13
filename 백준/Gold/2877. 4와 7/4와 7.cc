#include <iostream>
#include <vector>
using namespace std;

int main() {
	int K;
	scanf("%d", &K);
	K++;

	vector<int> ans;
	if (K == 1) printf("4");
	else {
		int idx = 0;
		while (K != 1) {
			if (K & 1) ans.emplace_back(7);
			else ans.emplace_back(4); 

			K >>= 1;
		}
	}

	for (int i = ans.size() - 1; i >= 0; i--) printf("%d", ans[i]);
}