#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> Point;
typedef pair<Point, int> PP;

int N;
vector<PP> v;

int gcd(int a, int b){
    int r;
    if (a < b) swap(a, b);

    while (b){
        r = a %b;
        a = b;
        b = r;
    }

    return a;
}

bool compare (PP p1, PP p2){
    int x1 = p1.first.first, y1 = p1.first.second, x2 = p2.first.first, y2 = p2.first.second;

    if (1LL * y1 * x2 == 1LL * x1 * y2) return (p1.second > p2.second);
    return 1LL * y1 * x2 > 1LL * x1 * y2;
}

Point divByGcd(Point p1){
    int g = gcd(p1.first, p1.second);
    return {p1.first/g, p1.second/g};
}

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int xbl, ybl, xtr, ytr;
        scanf("%d%d%d%d", &xbl, &ybl, &xtr, &ytr);
        v.push_back({{xbl, ytr}, 1});
        v.push_back({{xtr, ybl}, -1});
    }

    sort(v.begin(), v.end(), compare);
	
    int ans = 0, cur = 0;
    int in = 0, out = 0;

    for (int i = 0; i < 2 * N; i++){
        Point p = divByGcd(v[i].first);
        int val = v[i].second; 

        cur += val;
        ans = max(ans, cur);
    }

    printf("%d", ans);
}