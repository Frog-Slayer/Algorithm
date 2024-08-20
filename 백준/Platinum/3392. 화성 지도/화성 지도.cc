#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXY = 30000;

typedef pair<int, int> Point;
typedef pair<Point, Point> Segment;

int N;
int tree[MAXY * 4 + 4], cnt[MAXY * 4 + 4];
vector<pair<Segment, bool>> verticals;//0-> start, 1 -> end

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
        verticals.push_back({{{x1, y1}, {x1, y2}}, 0});
        verticals.push_back({{{x2, y1}, {x2, y2}}, 1});
    }

    sort(verticals.begin(), verticals.end());

    int ans = 0;

    for (int i = 0; i < 2 * N; i++){
        int x = 0;
        int y2 = verticals[i].first.second.second, y1 = verticals[i].first.first.second;

        if (i) {
            x = verticals[i].first.first.first - verticals[i-1].first.first.first;
            ans += tree[1] * x;
        }
        if (!verticals[i].second) update(1, 0, MAXY, y1, y2 - 1, 1);
        else update(1, 0, MAXY, y1, y2- 1, -1);
    }    

    printf("%d", ans);

}