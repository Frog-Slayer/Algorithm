#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

const int MAXY = 2e4 + 1;

typedef tuple<int, bool, int, int> Line; 

int N;
int tree[MAXY * 4], cnt[MAXY * 4];
vector<Line> verticals, horizontals;//0-> start, 1 -> end

void update(int node, int start, int end, int left, int right, int val){
    if (right < start || end < left) return;
    if (left <= start && end <= right) {
        cnt[node] += val;
    }
    else {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, left, right, val);
        update(node * 2 + 1, mid + 1, end, left, right, val);
    }

    if (cnt[node]) tree[node] = (end - start + 1);
    else {
        if (start == end) tree[node] = 0;
        else tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int x1, x2, y1, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        x1 += 1e4, x2 += 1e4;
        y1 += 1e4, y2 += 1e4;

        verticals.push_back({x1, 0, y1, y2});
        verticals.push_back({x2, 1, y1, y2});
        horizontals.push_back({y1, 0, x1, x2});
        horizontals.push_back({y2, 1, x1, x2});
    }

    sort(verticals.begin(), verticals.end());
    sort(horizontals.begin(), horizontals.end());

    int ans = 0;
    int prev = 0;

    for (auto [x, isEnd, y1, y2] : verticals){

        if (!isEnd) update(1, 0, 2e4, y1, y2 - 1, 1);
        else update(1, 0, 2e4 , y1, y2 - 1, -1);

        ans += abs(tree[1] - prev);
        prev = tree[1];
    }    

    prev = 0;

    for (auto [y, isEnd, x1, x2] : horizontals){
        if (!isEnd) update(1, 0, 2e4, x1, x2 - 1, 1);
        else update(1, 0, 2e4, x1, x2 - 1, -1);

        ans += abs(tree[1] - prev);
        prev = tree[1];
    }

    printf("%d", ans);

}