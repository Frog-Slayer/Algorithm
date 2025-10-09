#include <string>
#include <vector>

using namespace std;

pair<int, int> ans;

void dfs(int idx, vector<vector<int>> &users, vector<int> &emoticons, vector<int> &rates ) { 
    if (idx == emoticons.size()) { 
    	int cnt = 0, total  = 0;
    	for (auto user: users) { 
            int sum = 0;
        	int ratio = user[0], threshold = user[1];
            
            for (int j = 0; j < emoticons.size(); j++) { 
                if (rates[j] >= ratio) { 
                    sum += emoticons[j] * (100 - rates[j]) / 100;
                }
            }
            
            if (sum >= threshold) cnt++;
            else total += sum;
        }
        
        ans = max(ans, {cnt, total});
        return;
    }
    
    for (int rate = 10; rate <= 40; rate += 10) { 
    	rates[idx] = rate;
        dfs(idx + 1, users, emoticons, rates);
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    //4^7 = 2^14 = 16384
    vector<int> rates(emoticons.size());
    
    dfs(0, users, emoticons, rates);
    
    vector<int> answer = {ans.first, ans.second};
    return answer;
}