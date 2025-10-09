#include <string>
#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
typedef tuple<int, int, int> Date;

void printDate(Date date) { 
    auto [y, m, d] = date;
    cout << y << ", " << m << ", " << d << '\n'; 
}

Date toDate(string &s) { 
    int year = stoi(s.substr(0,4));
    int month = stoi(s.substr(5, 2));
    int day = stoi(s.substr(8, 2));
    
    return Date(year, month, day);
}

pair<Date, int> parsePrivacy(string &p) { 
    string d = p.substr(0, 10);
    Date date = toDate(d);
    char tp = p.back();
    
    return {date, tp};
}

Date addMonth(Date date, int m) { 
    //모든 달은 28일까지 있다고 가정
    auto [year, month, day] = date;
    
    month += m;
    day -= 1;
    
    if (!day) { 
        day = 28;
        month -= 1;
    }
    
    year += (month - 1) / 12;
    month = (month - 1) % 12 + 1;
   
    return Date(year, month, day);
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    map<char, int> type;
    
    for (string &t : terms) { 
        char a = t[0];
        int b = stoi(t.substr(2));
        type[a] = b;
    }
    
    Date todayAsDate = toDate(today);
    vector<int> answer;
    
    for (int i = 0; i < privacies.size(); i++) { 
        auto [date, tp] = parsePrivacy(privacies[i]);
        
        date = addMonth(date, type[tp]);
        
        if (date < todayAsDate) answer.emplace_back(i + 1);
    }
    
    return answer;
}