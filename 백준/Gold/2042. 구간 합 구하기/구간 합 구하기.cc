#include <stdio.h>
using namespace std;
#define LL long long

int N, M, K, a, b;
LL nums[1000001], c;
LL tree[4000001];

LL maketree(int start, int end, int node) {
	if (start == end) return tree[node] = nums[start];
	else return tree[node] = maketree(start,(start + end) / 2,2 * node) + maketree((start + end) / 2 + 1, end , 2 * node + 1);	
}

void change_node(int start, int end, int node, int index, LL value) {
	if (start > index || index > end) return;
	tree[node] += value;
	if (start != end) {
		change_node(start, (start + end) / 2, node * 2, index, value);
		change_node((start + end) / 2 + 1, end, node * 2 + 1, index, value);
	}

}

LL find_sum(int node, int start, int end, int left, LL right) {//해당노드, 노드가 담당하는 범위(start~end), 구하고자하는 범위(left~right)
	if (left > end || right < start) return 0;
	else if (left <= start && end <= right) return tree[node];
	else return find_sum(2 * node, start, (start + end) / 2, left, right) + find_sum(2 * node + 1, (start + end) / 2 + 1, end, left, right);	
}


int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%lld", &nums[i]);
	}
	maketree(1, N, 1);
	for (int i = 0; i < M + K; i++) {
		scanf("%d%d%lld", &a, &b, &c);
		if (a == 1) {
			change_node(1, N, 1, b, c - nums[b]);
			nums[b] = c;
		}
		else {
			printf("%lld\n", find_sum(1, 1, N, b, c));
		}
	}
	
}
