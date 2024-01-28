#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<pair<int, int>, int> Point;
vector<Point> points;
int N;

int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int x, y;
        scanf("%d%d", &x, &y);
        points.push_back({{x, y}, i +1});
    }

    sort(points.begin(), points.end());

    double maxSlope = 0;
    int a = 0, b = 0;

    for (int i = 1; i < N; i++){
        double slope = 1.0 * (points[i].first.second - points[i-1].first.second) / (points[i].first.first - points[i-1].first.first);
        if (abs(slope) > maxSlope) {
            maxSlope = abs(slope); 
            a = points[i].second, b = points[i-1].second;
            if (a > b) swap(a, b);
        }
        else if (abs(slope) == maxSlope){
            if (points[i].second < a || points[i-1].second < a){
                a = points[i].second, b = points[i-1].second;
            }
        }
    }

    for (int i = 0; i < N; i++){
        if (points[i].second == a) continue;
        double slope = 1.0 * (points[a].first.second - points[i].first.second) / (points[a].first.first - points[i].first.first);
        if (abs(slope) == maxSlope && (points[i].second < b)) b = points[i].second;
    }

    for (int i = 0; i < N; i++){
        if (points[i].second == b) continue;
        double slope = 1.0 * (points[b].first.second - points[i].first.second) / (points[b].first.first - points[i].first.first);
        if (slope == maxSlope && (points[i].second < a)) a = points[i].second;
    }

    if (a > b) swap(a, b);
    printf("%d %d", a, b);

}