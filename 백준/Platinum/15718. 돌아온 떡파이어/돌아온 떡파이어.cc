#include <iostream>
#include <vector>
using namespace std;

int T;
long long N, M;
long long factorial[2000];

/**
 * @brief extended euclid 
 * 
 * @param a  
 * @param b 
 * @param p 
 * @return long long
 */
long long extendedEuclid(long long a, long long b){
    long long dividend = a, divisor = b;
    long long quotient, remainder;
    long long s_prev = 1, s_cur = 0, s_next;
    long long t_prev = 0, t_cur = 1, t_next;
    while (a && b){
        quotient = dividend / divisor;
        remainder = dividend % divisor;
        if (!remainder) return s_cur;
        s_next = s_prev - quotient * s_cur;    
        t_next = t_prev - quotient * s_cur;    
        s_prev = s_cur, s_cur = s_next;
        t_prev = t_cur, t_cur = t_next;
        dividend = divisor;
        divisor = remainder;
    }
    return 0;
}

/**
 * @brief find unique solution of homogenous congruence system x === n(mod pn), x === m(mod pm) 
 * 
 * @param n  
 * @param m 
 * @param pn the divisor? of the first linear congruence 
 * @param pm the divisor of the second linear congruence 
 * @param mod the answer is ans % mod 
 * @return long long x: the unique solution of homogenous congruence system 
 */
long long chineseRemainder(long long n, long long m, long long pn, long long pm, long long mod){
    long long euc1 = extendedEuclid(pm, pn);
    long long euc2 = extendedEuclid(pn, pm);
    while (euc1 < 0) euc1 += pn;
    while (euc2 < 0) euc2 += pm;
    return ((n * pm * euc1) % mod + (m * pn * euc2) % mod) % mod;
}

/**
 * @brief Set the factorial array, whose each element is (i!) % p
 * 
 * @param p prime number  
 */
void setFactorial(long long p){
    factorial[0] = 1;
    for (long long i = 1; i < p; i++){
        factorial[i] = (factorial[i-1] * i) % p; 
    }
    return;
}

/**
 * @brief find n^m %p 
 * 
 * @param n base 
 * @param m exponent
 * @param p prime p
 * @return long long: n^m % p 
 */
long long power(long long n, long long m, long long p){
    if (!m) return 1;
    if (m == 1) return n % p;
    long long half = power(n, m / 2, p) % p;

    if (m % 2) return (((half * half) % p) * (n % p)) % p; 
    return (half * half) % p; 
}

/**
 * @brief find nCr % p using Fermat's little theorem 
 * 
 * @param n 
 * @param r 
 * @param p 
 * @return long long 
 */
long long comb(long long n, long long r, long long p){
    if (n < r) return 0; 
    long long ret = factorial[n];
    long long pow = power((factorial[n-r] * factorial[r]) % p, p - 2, p);
    ret *= pow;
    ret %= p;
    return ret;
}

/**
 * @brief nCm % p using lucas' theorem 
 * 
 * @param n   
 * @param m 
 * @param p 
 * @return long long 
 */
long long lucas(long long n, long long m, long long p){
    if (n < m) return 0;
    setFactorial(p);
    vector<long long> vn;
    vector<long long> vm;

    while (n || m){
        vn.push_back(n % p);
        vm.push_back(m % p);
        n /= p;
        m /= p;
    }

    long long ans = 1;
    for (long long i = 0; i < vn.size(); i++){
        ans *= comb(vn[i], vm[i], p);
        ans %= p;
    }
    return ans;
}

void solve(long long N, long long M){
        if (!N && M == 1) {
            printf("1\n");
            return;
        }
        long long c1 = lucas(N-1, M-2, 97); //nCm % 97
        long long c2 = lucas(N-1, M-2, 1031); //nCm % 1031
        printf("%lld\n", chineseRemainder(c1, c2, 97, 1031, 97 * 1031));
}

int main(){
    scanf("%d", &T);
    for (long long t = 0; t < T; t++){
        //100007 = 97 * 1031
        scanf("%lld%lld", &N, &M); 
        solve(N, M); 
    }
}