#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100000;
int N, M;
vector<int> arr;
vector<int> tree[MAXN * 4];

void makeTree(int start, int end, int node){
    tree[node].insert(tree[node].begin(), arr.begin() + start, arr.begin() + end + 1);
    sort(tree[node].begin(), tree[node].end());

    if (start == end) {
        return;
    }
    int mid = (start + end) / 2;

    makeTree(start, mid, node * 2);
    makeTree(mid + 1, end, node * 2 + 1);

}

//left, right : 탐색 범위, start, end :  node가 담당하는 범위
int query(int left, int right, int node, int start, int end, int val){
    if (end < left || right < start) return 0;
    if (left <= start &&  end <= right) {
        int ub = upper_bound(tree[node].begin(), tree[node].end(), val) - tree[node].begin();
        return tree[node].size() - ub;
    } 

    int mid = (start + end) / 2;

    return query(left, right, node * 2, start, mid, val) + query(left, right, node * 2 + 1, mid + 1, end, val);
}

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int n;
        scanf("%d", &n);
        arr.push_back(n);
    }

    makeTree(0, N - 1, 1);

    scanf("%d", &M);

    int ans = 0;
    for (int m = 0; m < M; m++){
        int a, b, c;
        int i, j, k;
        scanf("%d%d%d", &a, &b, &c);
        
        i = a ^ ans;
        j = b ^ ans;
        k = c ^ ans;

        printf("%d\n", ans = query(i - 1, j - 1, 1, 0, N - 1, k));
    }
}