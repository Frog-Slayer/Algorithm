#include <iostream>
using namespace std;

const int MAXN = 100000;
const int INF = 1000000000;
pair<int, int> tree[(MAXN + 1) *4];

pair<int, int> min(pair<int, int> p1, pair<int, int> p2){
    if (p1 < p2) return p1;
    return p2;
}

void update(int node, int start, int end, int idx, int val){
    if (idx < start || end < idx) return;
    if (start == end) {
        tree[node] = {val, idx};
        return;
    }
    
    int mid = (start + end)/2;

    update(node * 2, start, mid, idx, val);
    update(node * 2 + 1, mid + 1, end, idx, val);

    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

pair<int, int> query(int node, int start, int end, int left, int right){
    if (right < start || end < left) return {INF, INF};
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end)/2;

    return min(query(node * 2, start, mid, left, right),
                query(node * 2 + 1, mid + 1, end, left, right));

}

int main(){

    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++){
        int a;
        scanf("%d", &a);
        update(1, 1, N, i, a);
    }

    int M;
    scanf("%d", &M);    

    for (int i = 0; i < M; i++){
        int command;
        scanf("%d", &command);

        if (command == 1){
            int idx, val;
            scanf("%d%d", &idx, &val);
            update(1, 1, N, idx, val);
        }
        else {
            int from, to;
            scanf("%d%d", &from, &to);
            pair<int, int> res = query(1, 1, N, from, to);

            printf("%d\n", res.second);
        }
    }
}