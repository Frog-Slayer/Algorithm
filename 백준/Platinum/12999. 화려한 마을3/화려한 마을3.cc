#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <tuple>
using namespace std;

const int MAX_N = 1e5;
const int MAX_K = 2e5 + 1;

int N, Q, P;
int A[MAX_N + 1], cnt[MAX_K], ccnt[MAX_N + 1];

vector<tuple<int, int, int>> queries;
vector<int> ans;
int aans = 0;

void expand(int idx){
	//값 
	ccnt[cnt[idx]]--;
	cnt[idx]++;
	ccnt[cnt[idx]]++;
	aans = max(aans, cnt[idx]);
}

void shrink(int idx){
	ccnt[cnt[idx]]--;
	cnt[idx]--;
	ccnt[cnt[idx]]++;

	if (ccnt[aans] == 0) aans = cnt[idx];
}

int main(){
	scanf("%d%d", &N, &Q);
	ans.resize(Q);

	for (int i = 1; i <= N; i++){
		scanf("%d", &A[i]);
		A[i] += (int)1e5;
	}

	for (int q = 0; q < Q; q++){
		int i, j;
		scanf("%d%d", &i, &j);
		queries.emplace_back(q, i, j);
	}

	int k = sqrt(N);

	sort(queries.begin(), queries.end(), [k](tuple<int, int, int>  &a, tuple<int, int, int>  &b) {
			int s1 = get<1>(a), e1 = get<2>(a), s2 = get<1>(b), e2 = get<2>(b);
			if (s1/k < s2/k) return true;
			return (s1/k  == s2/k && e1 < e2);
		});

	int idx, s, e;
	tie(idx, s, e) = queries[0];
	int left = s, right = e;

	for (int i = s; i <= e; i++){
		expand(A[i]);
	}
	ans[idx] = aans;
	
	for (int i = 1; i < Q; i++){
		tie(idx, s, e) = queries[i];
		while (left > s) expand(A[--left]);

		while (left < s) shrink(A[left++]); 

		while (right > e) shrink(A[right--]);

		while (right < e) expand(A[++right]);

		ans[idx] = aans;
	}

	for (int i = 0; i < Q; i++) printf("%d\n", ans[i]);
}