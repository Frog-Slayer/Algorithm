#include <iostream>
#include <unordered_map>
using namespace std;

long long M, N;
unordered_map<long long, bool> umap;

bool divide(long long n){
	if (umap.find(n) != umap.end()) return umap[n];
	if (!n) return false;
	if (n < M) return false;
	if (n == M) return true;

	return umap[n] = divide(n/2) || divide(n - n / 2);
}

int main(){
	scanf("%lld%lld", &N, &M);
	printf("%s", divide(N) ? "YES" : "NO");
}