#include <iostream>
using namespace std;

const int MAXN = 100000;
const long long INF = 100000000000000;

int N, D;
long long seg[MAXN * 4], dp[MAXN];

void update(int node, int start, int end, int idx, long long val)
{
    if (start == end)
    {
        seg[node] = val;
        return;
    }

    int mid = (start + end) / 2;

    if (idx <= (start + end) / 2)
        update(node* 2, start, mid, idx, val);
    else
        update(node* 2 + 1, mid + 1, end, idx, val);
    seg[node] = max(seg[node* 2], seg[node* 2 + 1]);
}

long long find(int node, int start, int end, int i, int j)
{
    if (j < start || end < i) return -INF;
    if (i <= start && j >= end) return seg[node];

    int mid = (start + end) / 2;
    return max(find(node* 2, start, mid, i, j), find(node* 2 + 1, mid + 1, end, i, j));
}

int main(){
    scanf("%d%d", &N, &D);
    long long ans = -INF;

    for (int i = 0; i < N; i++) {
        scanf("%lld", &dp[i]);
    }

    for (int i = 0; i < N; i++){
        dp[i] = max(dp[i], find(1, 0, N, i - D > 0? i -D : 0, i - 1) + dp[i]);
        update(1, 0, N, i, dp[i]);
        ans = max(ans, dp[i]);
    }
    printf("%lld", ans);
}