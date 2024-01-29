#include <iostream>
#include <deque>
using namespace std;

const int MAX = 65536;
int N, K;
int tree[(65536 + 1) * 4];
deque<int> deq;

long long ans;

void update(int node, int start, int end, int idx, int val){
    if (idx < start || end < idx) return;
    tree[node] += val;
    if (start == end) return;

    int mid = (start + end) / 2;
    update(node * 2, start, mid, idx, val);
    update(node * 2 + 1, mid + 1, end, idx, val);
}

int query(int node, int start, int end, int sum){// 0~i까지의 합이 sum인 i구하기
    if (start == end) return end; 

    int left = tree[node * 2], right = tree[node * 2 + 1];
    int mid = (start + end) / 2;
    if (sum <= left) return query(node * 2, start, mid, sum);
    return query(node * 2 + 1, mid + 1, end, sum - left);
}

int main(){
    scanf("%d%d", &N, &K);

    for (int i = 1; i <= N; i++){
        int n;
        scanf("%d", &n);
        deq.push_back(n);
        if (deq.size() > K) {
            update(1, 0, 65536, deq.front(), -1);
            deq.pop_front();
        }
        update(1, 0, 65536, n, 1);

        if (deq.size() == K){
            int q = query(1, 0, 65536, (K + 1) / 2);
            ans += q;
        }
    }

    printf("%lld", ans);
}