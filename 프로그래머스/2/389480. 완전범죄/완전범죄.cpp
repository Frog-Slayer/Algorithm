#include <string>
#include <vector>

using namespace std;
const int INF = 2147483647;

int solution(vector<vector<int>> info, int n, int m) {
    int dp[40][120] = {0, };
    
    for (int i = 0; i < 40; i++) for (int j = 0; j < 120; j++) dp[i][j] = INF;
    
    int len = info.size();
    
    for (int i = 0; i < len; i++) { 
        int clue_a = info[i][0], clue_b = info[i][1];
        
        for (int j = 0; j < m; j++) { 
            dp[i][j] = min(dp[i][j], (i ? dp[i - 1][j] : 0) + clue_a);
            dp[i][j + clue_b] = min(dp[i][j + clue_b], (i ? dp[i - 1][j] : 0));
        }
    }
    
    int ans = INF;
    
    for (int j = 0; j < m; j++) ans = min(ans, dp[len - 1][j]);
    return ans >= n ? - 1 : ans;
}