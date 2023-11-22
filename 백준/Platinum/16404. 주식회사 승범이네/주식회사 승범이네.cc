#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100000;

int N, M;
int segmentTree[4 * (MAXN + 1)], lazy[4 * (MAXN + 1)];
pair<int, int> range[MAXN + 1];
vector<vector<int>> children;
int idx; 

void eulerTour(int start){
    range[start].first = ++idx;

    for (int child : children[start]){
        eulerTour(child);
    }
    range[start].second = idx;
}

void updateLazy(int node, int start, int end){
    if (!lazy[node]) return;
    
    segmentTree[node] += (end - start + 1) * lazy[node];
    if (start != end) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
}

void updateRange(int node, int start, int end, int left, int right, int val){
    updateLazy(node, start, end);
    if (end < left || right < start) return;
    if (left <= start && end <= right) {
        lazy[node] += val;
        updateLazy(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    updateRange(node * 2, start, mid, left, right, val);
    updateRange(node * 2 + 1, mid + 1, end, left, right, val);
    segmentTree[node] = segmentTree[node * 2] + segmentTree[node * 2 + 1];
}

int query(int node, int start, int end, int index){
    updateLazy(node, start, end);
    if (end < index || index < start) return 0;
    if (start == end) return segmentTree[node];

    int mid = (start + end) / 2;
    return query(node * 2, start,  mid, index) + query(node * 2 + 1, mid + 1, end, index);
}

int main(){
    scanf("%d%d", &N, &M);
    
    children.resize(N + 1);

    for (int i = 1; i <= N; i++){
        int boss;
        scanf("%d", &boss);
        if (boss == -1) continue;
        children[boss].push_back(i);
    }

    eulerTour(1);

    for (int i = 0; i < M; i++) {
        int command, emp, w;
        scanf("%d", &command);

        if (command == 1) {//직원 i가 w만 큼 이익/손해를 봄. => update
            scanf("%d%d", &emp, &w);
            updateRange(1, 1, N, range[emp].first, range[emp].second, w);
        }
        else {//emp의 현재 잔고 보기 => query
            scanf("%d", &emp);
            printf("%d\n", query(1, 1, N, range[emp].first));
        }
    }
    
}