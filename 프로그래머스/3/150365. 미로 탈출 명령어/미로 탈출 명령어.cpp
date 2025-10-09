#include <string>
#include <vector>

using namespace std;
typedef pair<int, int> Point;

//d -> l -> r -> u;
vector<char> dir = {'d', 'l', 'r', 'u'};
vector<int> dx = {1, 0, 0, -1}, dy = {0, -1, 1, 0};

int dist(const Point &p1, const Point &p2) { 
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

string dfs(int n, int m, Point p, Point dst, int k, string s) { 
    int min_dist = dist(p, dst);
    if ((k - min_dist) % 2) return "";
    if (min_dist > k) return "";
    if (!k) { 
        if (p == dst) return s;
        return "";
    }
    
    auto [x, y] = p;
    auto [r, c] = dst;

    for (int i = 0; i < 4; i++) { 
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        Point next(nx, ny);
        
        string res = dfs(n, m, next, dst, k - 1, s + dir[i]);
        if (res.empty()) continue;
        return res;
    }
    
    return "";
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    string answer = dfs(n, m, Point(--x, --y), Point(--r, --c), k, "");
    if (answer.empty()) answer = "impossible";
    return answer;
}