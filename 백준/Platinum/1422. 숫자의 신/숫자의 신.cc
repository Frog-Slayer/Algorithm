#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int K, N;
vector<int> v;

bool compare(int aNum, int bNum){
    string a = to_string(aNum), b = to_string(bNum);
    return a + b > b + a;
}

int main(){
    scanf("%d%d", &K, &N);
    v.resize(K);

    for (int i = 0; i < K; i++){
        scanf("%d", &v[i]);
    }

    sort(v.begin(), v.end());

    while (v.size() < N){
        v.push_back(v.back());
    }

    sort(v.begin(), v.end(), compare);

    for (int i = 0; i < N; i++) printf("%d", v[i]);

}