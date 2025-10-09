#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;
typedef long long ll;

#define all(v) v.begin(), v.end()

vector<int> possible_length;

void init_length() { 
    for (int i = 2; i <= 64; i *= 2) { 
        possible_length.emplace_back(i - 1);
    }
}

vector<int> to_binary(ll num) { 
    vector<int> ret;
    
    while (num) { 
        ret.emplace_back(num & 1);
        num >>= 1;
    }
    
    int padding = *lower_bound(all(possible_length), ret.size()) - ret.size();
    
    while (padding--) ret.emplace_back(0); 
    reverse(all(ret));
    return ret;
}

bool dfs(vector<int> &v, int start, int end) { 
    if (end == start) return true;
    int mid = (start + end) / 2;
    if (!v[mid]) { 
        for (int i = start; i <= end; i++) if (v[i]) return false;
        return true;
    }
    
    return dfs(v, start, mid - 1) && dfs(v, mid + 1, end);
}

bool solution(ll number) { 
    vector<int> bin = to_binary(number);
    return dfs(bin, 0, bin.size() - 1);
}

vector<int> solution(vector<long long> numbers) {
    init_length();
    vector<int> answer;
    
    for (auto number : numbers) { 
        answer.emplace_back(solution(number));
    }
    
    
    return answer;
}