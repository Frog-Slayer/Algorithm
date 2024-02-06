#include <iostream>
using namespace std;

const int MAXN = 100000;
int N, K;
int tree[(MAXN + 1) * 4];

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end){
		tree[node] = val;
	}
	else {
		int mid = (start + end) / 2;
		update(node * 2, start, mid, idx, val);
		update(node * 2 + 1, mid + 1, end, idx, val);

		tree[node] = tree[node * 2] * tree[node * 2 + 1];
	}
}

int query(int node, int start, int end, int left, int right){
	if (end < left || right < start) return 1;
	if (left <= start && end <= right) return tree[node];

	int mid = (start + end) / 2;
	return query(node * 2, start, mid, left, right) * query(node * 2 + 1, mid + 1, end, left, right);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	while (cin >> N >> K){
		for (int i = 0; i <= 4 * N; i++) tree[i] = 1;

		
		for (int i = 0; i < N; i++){
			int x;
			cin >> x;

			if (x < 0) x = -1;
			else if (x) x = 1;
			else x = 0;
			update(1, 1, N, i + 1, x);
		}

		for (int i = 0; i < K; i++){
			char cmd;

			cin >> cmd;

			if (cmd == 'C') {
				int index, val;
				cin >> index >> val;
				if (val < 0) val = -1;
				else if (val > 0) val = 1;
				
				update(1, 1, N, index, val);
			}
			else {
				int idx1, idx2;
				cin >> idx1 >> idx2;
				int ret = query(1, 1, N, idx1, idx2);
				if (ret < 0) cout << '-';
				else if (ret > 0) cout << '+';
				else cout << '0';
			}
		}
		cout << '\n';
	}
}