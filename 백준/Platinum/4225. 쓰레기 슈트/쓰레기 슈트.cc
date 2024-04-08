#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

typedef pair<int, int> Point;
int n, caseNumber;
vector<Point> v;

long long ccw(Point p1, Point p2, Point p3){
    return 1LL * (p2.first - p1.first) * (p3.second - p1.second) - 1LL * (p2.second - p1.second) * (p3.first - p1.first);
}

bool compareY(Point& p1, Point &p2){
    if (p1.second == p2.second) return p1.first < p2.first;
    return p1.second < p2.second;
}

long long dist(Point &p1, Point &p2){
    return 1LL * (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}

bool compareAngle(Point& p1, Point &p2){
    long long c = ccw(v[0], p1, p2);
    return c ? c > 0 : dist(p1, v[0]) < dist(p2, v[0]);
}

int main(){
    while (true){
        scanf("%d", &n);
        if (!n) break;

        v.clear();

        for (int i = 0; i < n; i++){
            int x, y;
            scanf("%d%d", &x, &y);
            v.emplace_back(x, y);
        }

        sort(v.begin(), v.end(), compareY);
        sort(v.begin() + 1, v.end(), compareAngle); 

        vector<int> stk;

        stk.push_back(0);
        stk.push_back(1);

        int next = 2;

        while (next < n) {
            while (stk.size() >= 2) {
                int second = stk.back();
                stk.pop_back();
                int first = stk.back();
                if (ccw(v[first], v[second], v[next]) > 0) {
                    stk.push_back(second);
                    break;
                }
            }
            stk.push_back(next++);
        }

        double minDist = 1e9;

        for (int i = 0; i < stk.size(); i++){
            int first = stk[i], second = stk[(i + 1) % stk.size()];

            double d = sqrt(dist(v[first], v[second]));
            double maxDist = 0;
            
            for (int k = 0; k < stk.size(); k++){
                // first -> j, first -> second;
                int j = stk[k];
                long long tmp = abs(1LL * (v[j].first - v[first].first) * (v[second].second - v[first].second) - (v[j].second - v[first].second) * (v[second].first - v[first].first));
                maxDist = max(maxDist, tmp / d);
            }

            minDist = min(minDist, maxDist);
        }

        minDist *= 100;
        if (minDist- (long long) minDist> (1e-12)) {
            minDist += 1;
            minDist = (long long) minDist;
        }
        minDist /= 100;
        printf("Case %d: %.2f\n", ++caseNumber, minDist);
    }
}