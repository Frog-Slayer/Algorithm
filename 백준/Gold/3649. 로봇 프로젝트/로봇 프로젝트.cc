#include <iostream>
#include <algorithm>
using namespace std;

int x, n, L;
int legos[1000000];

int main(){
    while (scanf("%d", &x) != EOF){
        x *= 10000000;
        scanf("%d", &n);
        for (int i = 0; i < n; i++){
            scanf("%d", &legos[i]);
        }
        sort(legos, legos + n);

        int left = 0, right = n - 1;
        int sum = 0;
        bool ans = false;

        while (left < right){
            sum = legos[left] + legos[right];
            if (sum == x) {
                ans = true;
                break;
            } 
            else if (sum < x) left++;
            else right--;
        }
        if (ans) printf("yes %d %d\n", legos[left], legos[right]);
        else printf("danger\n");
    }
}