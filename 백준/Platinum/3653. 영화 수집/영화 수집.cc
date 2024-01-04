#include <iostream>
using namespace std;

const int MAXN = 100000;
int T;
int n, m, newIdx;
int idx[MAXN + 1];
int tree[4 * (MAXN * 2 + 2)];

void update(int node, int start, int end, int left, int right, int val){
    if (end < left || right < start) return;
    if (start == end) {
        tree[node] += val;
        return;
    }

    int mid = (start + end) / 2;
    update(node * 2, start, mid, left, right, val);
    update(node * 2 + 1, mid + 1, end, left, right, val);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

void update(int left, int right, int val){
    update(1, 1, n + m + 1, left, right, val);
}

int query(int node, int start, int end, int left, int right){
    if (end < left || right < start) return 0;
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right); 
}

int query(int left, int right){
    return query(1, 1, n + m + 1, left, right);
}

int main(){
    scanf("%d", &T);

    while (T--){
        scanf("%d%d", &n, &m);
        newIdx = n;
        for (int i = 0; i < 4 * (n + m + 2); i++) tree[i] = 0;
        for (int i = 0; i <= n; i++) idx[i] = (n + 1) - i;
        update(1, n, 1);

        for (int i = 0; i < m; i++){
            int j;
            scanf("%d", &j);
            printf("%d ", query(idx[j] + 1, n + m + 1));

            update(idx[j], idx[j], -1);
            idx[j] = ++newIdx;
            update(idx[j], idx[j], 1);
        }
        printf("\n");
    }
}