#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

int N;
vector<int> BB;
vector<int> tree;

struct Student {
	int A;
	int B;
	int idx;
	int sorted_idx;

	Student(int a, int b, int i) : A(a), B(b), idx(i) {}

	bool operator<(Student &rhs) {
		if (B == rhs.B) return A < rhs.A;
		return B < rhs.B;
	}
};

vector<Student> students;
vector<pair<int, int>> queries;

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || end < idx) return;
	if (start == end) {
		tree[node] = val;
		return;
	}

	int mid = (start + end)/2;

	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

int query(int node, int start, int end, int left, int right, int val) {
	if (right < start || end < left) return 0;
	if (tree[node] < val) return 0;
	if (start == end) return start;

	int mid = (start + end) / 2;
	int left_subquery = query(node * 2, start, mid, left, right, val); 
	if (left_subquery) return left_subquery;

	int right_subquery = query(node * 2 + 1, mid + 1, end, left, right, val);
	return right_subquery;
}

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		char c;
		scanf("\n%c", &c);

		if (c == 'D') {
			int a, b;
			scanf("%d%d", &a, &b);
			students.emplace_back(a, b, students.size() + 1);
			BB.emplace_back(b);
			queries.emplace_back(c, students.back().idx);
		}
		else {
			int p;
			scanf("%d", &p);
			queries.emplace_back(c, p);
		}
	}

	tree.resize(students.size() * 4 + 4);

	sort(students.begin(), students.end());

	for (int i = 0; i < students.size(); i++) students[i].sorted_idx = i + 1;

	vector<Student> sorted(students);

	sort(students.begin(), students.end(), [&](auto &s1, auto &s2) { return s1.idx < s2.idx; });

	for (int i = 0; i < N; i++) {
		pair<int, int> &p = queries[i];

		if (p.first == 'D') update(1, 1, students.size(), students[p.second - 1].sorted_idx, students[p.second - 1].A);
		else {
			int q = query(1, 1, students.size(), students[p.second - 1].sorted_idx + 1, students.size(), students[p.second - 1].A); 
			if (q) printf("%d\n", sorted[q - 1].idx);
			else printf("NE\n");
		}
	}
}