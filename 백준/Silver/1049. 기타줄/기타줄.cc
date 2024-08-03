#include <iostream>
using namespace std;

int N, M;
int min_pack = 1000, min_single = 1000;

int main(){
	scanf("%d%d", &N, &M);

	for (int i = 0; i < M; i++) {
		int pack, single;
		scanf("%d%d", &pack, &single);

		min_pack = min(min_pack, pack);
		min_single = min(min_single, single);
	}

	if (min_single * 6 < min_pack) printf("%d", min_single * N); 
	else printf("%d", min(min_pack * (N / 6) + min_single * (N % 6), min_pack * (N / 6 + 1)));
}