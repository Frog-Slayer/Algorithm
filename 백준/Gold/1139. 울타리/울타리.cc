#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

const int MAXN = 16;
int N;
double dp[1 << MAXN];
vector<int> sides;

double calcArea(double A, double B, double C){
    double p = (A + B + C)/2;
    return sqrt(p * (p - A) * (p - B) * (p - C));
}


double solve(int flag){
    int cnt = 0;
    for (int i = 0; i < N; i++){
        if (flag & (1 << i)) cnt++;
    }

    if (N - cnt < 3) return dp[flag] = 0;
    if (dp[flag] > -1) return dp[flag];

    double ret = 0;
    vector<int> tmp;
    
    for (int i = 0; i < N; i++){
        if (!(flag & (1 << i))) tmp.push_back(i);
    }

    for (int i = 0; i < tmp.size(); i++){
        for (int j = i + 1; j < tmp.size(); j++){
            for (int k = j + 1; k < tmp.size(); k++){
                double A = sides[tmp[i]], B = sides[tmp[j]], C = sides[tmp[k]];
                if (A + B <= C) continue;
                int mask = 0;
                mask |= (1 << tmp[i]);
                mask |= (1 << tmp[j]);
                mask |= (1 << tmp[k]);

                double area = calcArea(A, B, C);
                ret = max(ret, solve(flag | mask) + area);
            }
        }
    }

    return dp[flag] = ret;
}


int main(){
    scanf("%d", &N);

    for (int i = 0; i < N; i++){
        int n;
        scanf("%d", &n);
        sides.push_back(n);
    }

    for (int i = 0; i < (1 << N); i++){
        dp[i] = -1;
    }

    sort(sides.begin(), sides.end());

    double ans = solve(0);
    printf("%.10g", ans);

}