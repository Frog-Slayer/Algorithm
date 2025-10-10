#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

int to_minute(string s) { 
    string hour = s.substr(0, 2);
    string minute = s.substr(3, 2);
    
    int h = stoi(hour), m = stoi(minute);
    
    return h * 60 + m;
}

typedef tuple<int, int, bool> Record;

Record parse(string record) { 
    vector<string> tokens;
    string token = "";
    
   	for (char c : record) { 
        if (c == ' ') { 
            tokens.emplace_back(token);
            token = "";
        }
        else token += c;
    }
    
    if (!token.empty()) tokens.emplace_back(token);
    
    int t = to_minute(tokens[0]);
    int n = stoi(tokens[1]);
    bool in_out = tokens[2] == "IN" ? 0 : 1;

    return {t, n, in_out};
}

vector<int> solution(vector<int> fees, vector<string> records) {
    set<int> numset;
    vector<Record> recs;
    
    for (auto record : records) { 
        recs.emplace_back(parse(record));
    }
    
    sort(all(recs), [&](Record &r1, Record &r2) { 
        auto [m1, n1, b1] = r1;
        auto [m2, n2, b2] = r2;
    
        if (n1 == n2) return m1 < m2;//같은 차량이 동일 시간에 드나드는 경우는 없음
        return n1 < n2;
    });
    
    vector<int> acc;
    
    int basic_minute = fees[0];
    int basic_fee = fees[1];
    int unit_minute = fees[2];
    int unit_fee = fees[3];
    
    for (int i = 0; i < recs.size(); i++) { 
        auto [minute, number, is_out] = recs[i];    
        
        if (!numset.count(number)) { 
            numset.emplace(number);
            acc.emplace_back(0);
        }
        
        int fee = 0;
        int diff;
        
        if (is_out) {//out
            int in_min = get<0>(recs[i-1]);
            diff = minute - in_min;
        }
        else {//in
            if (i < recs.size() - 1 && get<1>(recs[i + 1]) == number) continue;
            int out_min = 23 * 60 + 59;
            diff = out_min - minute;
        }
        
        acc.back() += diff;
    }
    
    vector<int> answer;
    
    for (auto diff : acc) { 
        int total = basic_fee;
        
        if (diff > basic_minute) { 
            int extra_minute = diff - basic_minute;
            int extra_unit = extra_minute / unit_minute;
            
            if (extra_minute % unit_minute) extra_unit++;
            
            total += extra_unit * unit_fee;
        }
    
        answer.emplace_back(total);
    }
    
    return answer;
}