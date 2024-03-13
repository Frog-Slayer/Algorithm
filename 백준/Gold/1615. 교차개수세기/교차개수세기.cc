#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2000;
int N, M;
int segTree[MAXN * 4];
vector<pair<int, int>> v;

void update(int node, int start, int end, int idx){
    if (idx < start || end < idx) return;
    segTree[node]++;
    if (start == end) return;
    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx);
    update(node * 2 + 1, mid + 1, end, idx);
}

int query(int node, int start, int end, int left, int right){
    if (right < start || end < left) return 0;
    if (left <= start && end <= right) return segTree[node];

    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

int main(){
    scanf("%d%d", &N, &M);

    for (int i = 0; i < M; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        v.emplace_back(a, b);
    }

    sort(v.begin(), v.end());

    long long ans = 0;

    for (int i = 0; i < M; i++){
        int to = v[i].second;
        ans += query(1, 0, N - 1, to + 1, N);
        update(1, 0, N - 1, to);
    }

    printf("%lld", ans);
}