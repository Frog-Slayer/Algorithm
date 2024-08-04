#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int cnt[36];
char buffer[53];

struct Number{
	char value[53] = {0, };
	int len = 0;

	Number() {}

	Number(char *val) {
		for (int i = 0; val[i]; i++) {
			value[i] = val[i];
			len++;
		}
	}
	
	Number operator+(Number rhs) {
		char ret[53] = {0, };

		reverse(value, value + len);
		reverse(rhs.value, rhs.value + rhs.len);

		int carry = 0;
		int ret_len = 0;
		for (int i = 0; i < max(len, rhs.len); i++) {
			int sum = to_digit(value[i]) + to_digit(rhs.value[i]) + carry;
			int mod = sum % 36;
			carry = sum / 36;
			ret[i] = to_char(mod);
			ret_len++;
		}
		if (carry){
			ret[max(len, rhs.len)] = to_char(carry); 
			ret_len++;
		}

		reverse(value, value + len);
		reverse(rhs.value, rhs.value + rhs.len);
		reverse(ret, ret + ret_len);

		return Number(ret);
	}

	Number if_change(int change) {//c를 Z로 바꿨을 때 얻는 이득
		char ret[53] = { 0, };

		for (int i = 0; i < len; i++) {
			if (to_digit(value[i]) == change) ret[i] = to_char(35 - to_digit(value[i]));
			else ret[i] = '0';
		}

		return Number(ret);
	}

	bool operator<(const Number& rhs) const {
		if (len != rhs.len) return len < rhs.len;

		for (int i = 0; i < len; i++) {
			if (value[i] != rhs.value[i]) return value[i] < rhs.value[i];
		}
		return false;
	}

	int to_digit(char c) {
		if (c < '0') return c;
		if (c >= '0' && c <= '9') return c - '0';
		return c - 'A' + 10;
	}

	char to_char(int i) {
		if (i < 10) return i + '0';
		return i - 10 + 'A';
	}

	void print(){
		printf("%s\n", value);
	}

	void change(int val) {
		for (int i = 0; i < len; i++) {
			if (to_digit(value[i]) == val) value[i] = 'Z';
		}
	}
};

vector<Number> v;
vector<pair<Number, int>> diff;

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%s", buffer);
		v.emplace_back(buffer);
	}

	for (int i = 0; i < 36; i++) {
		Number diff_sum;

		for (int j = 0; j < N; j++) {
			diff_sum = diff_sum + v[j].if_change(i);
		}

		diff.emplace_back(diff_sum, i);
	}

	sort(diff.begin(), diff.end(), greater());

	int K;
	scanf("%d", &K);

	Number ans;

	for (int i = 0; i < K; i++) {
		for (int j = 0; j < N; j++) {
			v[j].change(diff[i].second);
		}
	}

	for (int i = 0; i < N; i++) ans = ans + v[i];

	ans.print();
}