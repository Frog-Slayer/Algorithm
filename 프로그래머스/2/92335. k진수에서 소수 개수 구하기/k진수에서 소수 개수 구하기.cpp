#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define all(v) v.begin(), v.end()

using namespace std;

string to_k_ary (int n, int k) { 
    string ret = "";
    
    while (n) { 
        ret += (n % k) + '0';
        n /= k;
    }
    
    reverse(all(ret));

    return ret;
}

// 1000000_(3) => 13자리 => long long으로 처리 가능
bool is_prime(long long n) { 
    if (n == 1) return false;
    if (n == 2) return true;
    
    for (long long i = 2; i * i <= n; i++) { 
        if (n % i == 0) return false;
    }
    return true;
}

int solution(int n, int k) {
    //0으로 구분되는 구간들 중 소수가 있는지 확인하기
    string k_ary = to_k_ary(n, k);
    
    int answer = 0;
    string interval = "";
    
    
    for (int i = 0; i < k_ary.size(); i++) { 
        if (k_ary[i] == '0') { 
            if (!interval.empty()) {
                long long n = stoll(interval);
                answer += is_prime(n);
            }
            interval = "";
        }
        else interval += k_ary[i];
    }
    
    if (!interval.empty()) { 
        long long n = stoll(interval);
        answer += is_prime(n);
    }
    
    return answer;
}