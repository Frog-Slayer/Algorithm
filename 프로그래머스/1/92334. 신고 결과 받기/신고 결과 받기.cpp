#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define all(v) v.begin(), v.end()

using namespace std;

vector<string> parse(string s) { 
    vector<string> ret;
    string token = "";
    
    for (char c : s) { 
        if (c == ' ') { 
            ret.emplace_back(token);
            token = "";
        }
        else token += c;
    }
    
    if (!token.empty()) ret.emplace_back(token);
    
    return ret;
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    map<string, int> id_map;
    map<int, vector<int>> reported_by;
    map<int, int> reported_cnt;
    
    for (auto id: id_list) { 
        id_map[id] = id_map.size();
    }
    
    vector<string> report_unique(report);
    
    sort(all(report_unique));
    report_unique.erase(unique(all(report_unique)), report_unique.end());
    
    for (auto r : report_unique) { 
        vector<string> parsed = parse(r);
        int from = id_map[parsed[0]], to = id_map[parsed[1]];
        
        reported_cnt[to]++;
        reported_by[to].emplace_back(from);
    }
    
    vector<int> answer(id_list.size());
    
    for (auto [reported, cnt] : reported_cnt) { 
        if (cnt >= k) { 
            for (auto reporter : reported_by[reported]) { 
                answer[reporter]++;
            }
        }
    }
    
    
    return answer;
}