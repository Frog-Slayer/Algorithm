#include <string>
#include <vector>
#include <map>

using namespace std;
const int MAX_N = 50;

vector<vector<int>> cnt(MAX_N, vector<int>(MAX_N));
vector<int> index(MAX_N), gift(MAX_N);
map<string, int> m;

pair<string, string> parse(string &s) {
    int delim = s.find(" ", 0);
    string from = s.substr(0, delim);
    string to = s.substr(delim + 1, s.size());
    
    return {from, to};
}

int solution(vector<string> friends, vector<string> gifts) {
    
    int N = friends.size();
    for (auto &name: friends) m.insert({name, m.size()});
    
    for (auto &gift: gifts) {
        pair<string, string> p = parse(gift);
        int from = m[p.first], to = m[p.second];
        cnt[from][to]++;
        cnt[to][from]--;
        
        index[from]++;
        index[to]--;
    }
    
    int answer = 0;
    for (int i = 0; i < N; i++){
        for (int j = i + 1; j < N; j++){
            if (cnt[i][j] > 0) gift[i]++;
            else if (cnt[i][j] < 0) gift[j]++;
            else if (index[i] < index[j]) gift[j]++;
            else if (index[i] > index[j]) gift[i]++;                
        }
    }
    
    for (int i = 0; i < N; i++) answer = max(answer, gift[i]);        
    
    return answer;
}