#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define fastio cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false)
#define all(v) v.begin(), v.end()

int A[10001], parent[10001];

int find(int a) { 
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}

bool merge(int a, int b) { 
	a = find(a), b = find(b);
	if (a == b) return false;

	if (A[a] > A[b]) swap(a, b);
	parent[b] = a;

	return true;
}

int main () { 
	fastio;

	int N, M, k;
	cin >> N >> M >> k;

	for (int i = 1; i <= N; i++) { 
		parent[i] = i;
		cin >> A[i]; 
	}

	for (int i = 0; i < M; i++) { 
		int v, w;
		cin >> v >> w;

		merge(v, w);
	}

	int to_merge = 0;

	for (int i = 1; i <= N; i++) { 
		if (find(0) == find(i)) continue;
		to_merge += A[find(i)];
		merge(0, i);
	}

	if (to_merge <= k) cout << to_merge;
	else cout << "Oh no";
	
}
