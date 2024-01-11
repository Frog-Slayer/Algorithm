#include <iostream>
#include <vector>
using namespace std;

int main(){
    int N, a0;
    bool noAnswer = false;
    double lb= -2e6, ub = 2e6;
    vector<int> S;
    
    scanf("%d%d", &N, &a0);

    
    if (!N) printf("0.0");
    else {
        S.push_back(a0);

        double l, u; 

        for (int i = 1; i <= N; i++){
            int s;
            scanf("%d", &s);
            S.push_back(s);

            l = 1.0 * S[i] - S[0];
            u = 1.0 * S[i] - S[0] + 1;
            l /= i;
            u /= i;

            lb = max(lb, l);
            ub = min(ub, u);
        }

        //차이가 음수가 되면 불가능
        //평균 변화량이 가능한 최소 등차 +1보다 크거나 같으면 불가능
        if (ub < lb) noAnswer = true;

        for (int i = 1; i <= N; i++){
            double d = S[i] - S[i-1];
            double l = (S[i] - S[0]) * 1.0 / i;
            double u = (S[i] - S[0] + 1) * 1.0 / i;

            if (d < 0) noAnswer = true;
            if (lb < l || lb >= u) noAnswer = true;
        }


        if (noAnswer) printf("-1");
        else printf("%.10g", lb);
    }
}