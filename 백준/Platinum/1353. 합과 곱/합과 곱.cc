#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int main(){
    int S, P;
    scanf("%d%d", &S, &P);
    double e = M_E;

    if (S == P) printf("1");
    else if (pow(e, S / e) < P) printf("-1");
    else {
        double prev = 0;
        for (int i = 2; i <= 1000000000; i++){
            double tmp = pow(1.0 * S / i, i);
            if (tmp < prev) {
                printf("-1");
                break;
            }
            if (tmp >= P) {
                printf("%d", i);
                break;
            }
            prev = tmp;
        }
    } 
}