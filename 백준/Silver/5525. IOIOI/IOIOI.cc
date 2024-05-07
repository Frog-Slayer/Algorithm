#include <iostream>
using namespace std;

const int MAX_M = 1e6;
int N, M;
char S[MAX_M + 1];
int cnt[MAX_M];

int main(){
	scanf("%d", &N);
	scanf("%d", &M);
	scanf("%s", S);

	int ans = 0;
	for (int i = 1; i < M - 1; i++){
		if (S[i] == 'O' && S[i - 1] == 'I' && S[i + 1] == 'I'){
			cnt[i] = cnt[i-2] + 1;
			if (cnt[i] >= N) ans++;
		}
	}

	printf("%d", ans);
}