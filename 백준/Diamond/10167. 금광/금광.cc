#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> Point;
const long long INF = 10e9 * 3000;

int N;
struct Node{
    long long leftMax = -INF;
    long long rightMax = -INF;
    long long totalMax = -INF;
    long long sum = 0;
};

vector<pair<Point, int>> points;
vector<Node> tree;
vector<int> xs, ys;

void compress(){
    sort(xs.begin(), xs.end());
    sort(ys.begin(), ys.end());

    for (int i = 0; i < N; i++){
        points[i].first.first = lower_bound(xs.begin(), xs.end(), points[i].first.first) - xs.begin();
        points[i].first.second = lower_bound(ys.begin(), ys.end(), points[i].first.second) - ys.begin();
    }
}

void updateTree(int node, int idx, int left, int right, int val){
    if (right < idx || idx < left) return;
    if (left == right) {
        tree[node].leftMax += val;
        tree[node].rightMax += val;
        tree[node].sum += val;
        tree[node].totalMax += val;
        return;
    }

    int mid = (left + right) / 2;

    updateTree(node * 2, idx, left, mid, val);
    updateTree(node * 2 + 1, idx, mid + 1, right, val);

    Node leftSub = tree[node * 2]; 
    Node rightSub = tree[node * 2 + 1];  

    Node ret;
    ret.leftMax = max(leftSub.leftMax, leftSub.sum + rightSub.leftMax); 
    ret.rightMax= max(rightSub.rightMax, rightSub.sum + leftSub.rightMax); 
    ret.sum = leftSub.sum + rightSub.sum;
    ret.totalMax = max(ret.leftMax, ret.rightMax); 
    ret.totalMax = max(ret.totalMax, leftSub.totalMax); 
    ret.totalMax = max(ret.totalMax, rightSub.totalMax); 
    ret.totalMax = max(ret.totalMax, leftSub.rightMax + rightSub.leftMax);
    tree[node] = ret;
}

bool compare(pair<Point, int> &p1, pair<Point, int> &p2){
    if (p1.first.second != p2.first.second) return p1.first.second < p2.first.second;
    return p1.first.first< p2.first.first;
}

int main(){
    scanf("%d", &N);
    tree.resize(N << 2);

    for (int i = 0; i < N; i++){
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        points.push_back({{x, y}, w});
        xs.push_back(x);
        ys.push_back(y);
    }

    compress();
    sort(points.begin(), points.end(), compare);

    long long ans = 0;

    //아랫변 정하고
    for (int i = 0; i < N; i = upper_bound(ys.begin(), ys.end(), ys[i]) - ys.begin()){
        // printf("i: %d\n", i);
        for (int j = 0; j  < 4 * N; j++) tree[j] = {0, 0, 0, 0};

        for (int j = i; j < N; j++){
            if (points[j].first.second < points[i].first.second) continue; //사이에 있어야 함
            updateTree(1, points[j].first.first, 0, N-1, points[j].second);
            Node node = tree[1];
            // printf("(left %lld right %lld total %lld sum %lld)\n", node.leftMax, node.rightMax, node.totalMax, node.sum);
            if (j == N - 1 || points[j].first.second != points[j + 1].first.second) ans = max(ans, node.totalMax);

        }
    }
    printf("%lld", ans);
}