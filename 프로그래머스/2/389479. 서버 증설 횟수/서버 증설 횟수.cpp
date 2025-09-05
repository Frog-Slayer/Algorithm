#include <string>
#include <vector>

using namespace std;

int solution(vector<int> players, int m, int k) {
    int cur = 0;
    int ans = 0;
    vector<int> servers(25);
    
    for (int i = 0; i < 24; i++) { 
        cur -= servers[i];
        
        if (players[i] >= (cur + 1) * m) { 
            //서버 증설
            int aug = (players[i] - (cur + 1) * m) / m + 1;
            cur += aug;
            ans += aug;
            
            //어느 시점에 닫을지
            servers[min(24, i + k)] += aug;
        }
    }
    
    return ans;
}