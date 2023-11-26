#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 262143;//max depth = 18
const long long INF = 262143000000001;
int N; 
int weight[MAXN + 1];
vector<long long> traversalResult;

void inorderTraverse(int top, int bottom, int node, int level){
    if (level > bottom) return;
    inorderTraverse(top, bottom, node * 2, level + 1);
    if (level >= top) traversalResult.push_back(weight[node]);
    inorderTraverse(top, bottom, node * 2 + 1, level + 1);
}

long long getMaxWeightSum(){
    long long maxSum[MAXN + 1] = {0, };
    long long ret = -INF;

    maxSum[0] = traversalResult[0];
    ret = max(ret, maxSum[0]);

    for (int i = 1; i < traversalResult.size(); i++) {
        maxSum[i] = max(maxSum[i - 1] + traversalResult[i], traversalResult[i]);
        ret = max(ret, maxSum[i]);
    }
    return ret;
}

int main(){
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &weight[i]);
    }
    
    int depth;

    for (int i = 0; (1 << i)-1 != N; i++) {
        depth = i + 1;
    }

    long long ans = -INF;

    for (int i = 1; i <= depth; i++){
        for (int j = i; j <= depth; j++){
            traversalResult.clear();
            inorderTraverse(i, j, 1, 1);
            long long maxWeightSum = getMaxWeightSum();
            ans = max(ans, maxWeightSum);
        }
    }


    printf("%lld", ans);
}