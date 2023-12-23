#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXY = 2e5;

typedef pair<int, pair<int, int>> Vertical;

int N;
long long tree[MAXY * 8], cnt[MAXY * 8];
vector<pair<Vertical, bool>> verticals;//0-> start, 1 -> end
vector<int> yy;

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

    if (cnt[node]) tree[node] = (yy[end] - yy[start-1]);
    else {
        if (start == end) tree[node] = 0;
        else tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
}

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int x1, x2, y1, y2;
        scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
        verticals.push_back({{x1, {y1, y2}}, 0});
        verticals.push_back({{x2, {y1, y2}}, 1});

        yy.push_back(y1);
        yy.push_back(y2);
    }

    sort(verticals.begin(), verticals.end());
    sort(yy.begin(), yy.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());

    long long ans = 0;

    for (int i = 0; i < 2 * N; i++){
        int x = 0;
        int y1 = verticals[i].first.second.first, y2 = verticals[i].first.second.second;
        y1 = lower_bound(yy.begin(), yy.end(), y1) - yy.begin();
        y2 = lower_bound(yy.begin(), yy.end(), y2) - yy.begin();

        if (i) {
            x = verticals[i].first.first - verticals[i - 1].first.first;
            ans += tree[1] * x;
        }

        if (!verticals[i].second) update(1, 0, yy.size() - 1, ++y1, y2, 1);
        else update(1, 0, yy.size() - 1, ++y1, y2, -1);
    }    

    printf("%lld", ans);

}