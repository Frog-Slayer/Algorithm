#include <iostream>
using namespace std;

const int MAXN = 1e5;
int N, T, Q;
int tree[(MAXN + 1) * 4], lazy[(MAXN + 1) * 4];

void updateLazy(int node, int start, int end){
    if (!lazy[node]) return;
    tree[node] = lazy[node];

    if (start != end) {
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
    }

    lazy[node] = 0;
}

void updateTree(int node, int start, int end, int left, int right, int val){
    updateLazy(node, start, end);

    if (end < left || right < start) return;
    if (left <= start && end <= right) {
        lazy[node] = val;
        updateLazy(node, start, end);
        return;
    }

    int mid = (start + end) / 2;
    updateTree(node * 2, start, mid, left, right, val);
    updateTree(node * 2 + 1, mid + 1, end, left, right, val);
    tree[node] = tree[node * 2] | tree[node * 2 + 1];
}

int query(int node, int start, int end, int left, int right){
    updateLazy(node, start, end);
    if (end < left || right < start) return 0;
    if (left <= start && end <= right) return tree[node];
    
    int mid = (start + end) / 2;
    return query(node * 2, start, mid, left, right) | query(node * 2 + 1, mid + 1, end, left, right);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> T >> Q;

    updateTree(1, 1, N, 1, N, 1);

    for (int i = 0; i < Q; i++){
        char command;
        cin >> command;

        if (command == 'C'){
            int x, y, z;
            cin >> x >> y >> z;
            if (x > y) swap(x, y);
            updateTree(1, 1, N, x, y, 1 << (z - 1));
        }
        else {
            int x, y;
            cin >> x >> y;

            if (x > y) swap(x, y);

            int q = query(1, 1, N, x, y);
            int cnt = 0;

            while (q) {
                cnt += (q & 1);
                q >>= 1;
            }

            cout << cnt << '\n';
        }
    }
}