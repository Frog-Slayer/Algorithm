#include <bits/stdc++.h>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Author : jinhan814
 * Date : 2021-05-05
 * Source : https://blog.naver.com/jinhan814/222266396476
 * Description : FastIO implementation for cin, cout.
 */
constexpr int SZ = 1 << 20;

class INPUT {
private:
	char read_buf[SZ];
	int read_idx, next_idx;
	bool __END_FLAG__, __GETLINE_FLAG__;
public:
	explicit operator bool() { return !__END_FLAG__; }
	bool IsBlank(char c) { return c == ' ' || c == '\n'; }
	bool IsEnd(char c) { return c == '\0'; }
	char _ReadChar() {
		if (read_idx == next_idx) {
			next_idx = fread(read_buf, sizeof(char), SZ, stdin);
			if (next_idx == 0) return 0;
			read_idx = 0;
		}
		return read_buf[read_idx++];
	}
	char ReadChar() {
		char ret = _ReadChar();
		for (; IsBlank(ret); ret = _ReadChar());
		return ret;
	}
	template<typename T> T ReadInt() {
		T ret = 0; char cur = _ReadChar(); bool flag = 0;
		for (; IsBlank(cur); cur = _ReadChar());
		if (cur == '-') flag = 1, cur = _ReadChar();
		for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret = 10 * ret + (cur & 15);
		if (IsEnd(cur)) __END_FLAG__ = 1;
		return flag ? -ret : ret;
	}
	string ReadString() {
		string ret; char cur = _ReadChar();
		for (; IsBlank(cur); cur = _ReadChar());
		for (; !IsBlank(cur) && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
		if (IsEnd(cur)) __END_FLAG__ = 1;
		return ret;
	}
	double ReadDouble() {
		string ret = ReadString();
		return stod(ret);
	}
	string getline() {
		string ret; char cur = _ReadChar();
		for (; cur != '\n' && !IsEnd(cur); cur = _ReadChar()) ret.push_back(cur);
		if (__GETLINE_FLAG__) __END_FLAG__ = 1;
		if (IsEnd(cur)) __GETLINE_FLAG__ = 1;
		return ret;
	}
	friend INPUT& getline(INPUT& in, string& s) { s = in.getline(); return in; }
} _in;

class OUTPUT {
private:
	char write_buf[SZ];
	int write_idx;
public:
	~OUTPUT() { Flush(); }
	explicit operator bool() { return 1; }
	void Flush() {
		fwrite(write_buf, sizeof(char), write_idx, stdout);
		write_idx = 0;
	}
	void WriteChar(char c) {
		if (write_idx == SZ) Flush();
		write_buf[write_idx++] = c;
	}
	template<typename T> int GetSize(T n) {
		int ret = 1;
		for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;
		return ret;
	}
	template<typename T> void WriteInt(T n) {
		int sz = GetSize(n);
		if (write_idx + sz >= SZ) Flush();
		if (n < 0) write_buf[write_idx++] = '-', n = -n;
		for (int i = sz; i-- > 0; n /= 10) write_buf[write_idx + i] = n % 10 | 48;
		write_idx += sz;
	}
	void WriteString(string s) { for (auto& c : s) WriteChar(c); }
	void WriteDouble(double d) { WriteString(to_string(d)); }
} _out;

/* operators */
INPUT& operator>> (INPUT& in, char& i) { i = in.ReadChar(); return in; }
INPUT& operator>> (INPUT& in, string& i) { i = in.ReadString(); return in; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
INPUT& operator>> (INPUT& in, T& i) {
	if constexpr (is_floating_point_v<T>) i = in.ReadDouble();
	else if constexpr (is_integral_v<T>) i = in.ReadInt<T>(); return in; }

OUTPUT& operator<< (OUTPUT& out, char i) { out.WriteChar(i); return out; }
OUTPUT& operator<< (OUTPUT& out, string i) { out.WriteString(i); return out; }
template<typename T, typename std::enable_if_t<is_arithmetic_v<T>>* = nullptr>
OUTPUT& operator<< (OUTPUT& out, T i) {
	if constexpr (is_floating_point_v<T>) out.WriteDouble(i);
	else if constexpr (is_integral_v<T>) out.WriteInt<T>(i); return out; }

/* macros */
#define fastio 1
#define cin _in
#define cout _out
#define istream INPUT
#define ostream OUTPUT
/////////////////////////////////////////////////////////////////////////////////////////////

typedef long long ll;
const int MAX_N = 1 << 17;

struct Node {
	Node () {}
	Node(ll m, ll M, ll s) : min(m), max(M), sum(s) {}

	ll min = 0;
	ll max = 0;
	ll sum = 0;

	ll lazy1 = 0;
	ll lazy2 = 0;

	Node operator+(const Node& node) {
		return Node(std::min(min, node.min), std::max(max, node.max), sum + node.sum);
	}

	void clear() {
		min = max = sum = lazy2 = lazy1 = 0;
	}
} tree[MAX_N << 1];

void propagate(int node, int start, int end) {
	if (!tree[node].lazy2) { 
		tree[node].min += tree[node].lazy1;
		tree[node].max += tree[node].lazy1;
		tree[node].sum += tree[node].lazy1 * (end - start + 1);

		if (start != end) {
			tree[node * 2].lazy1 += tree[node].lazy1;
			tree[node * 2 + 1].lazy1 += tree[node].lazy1;
		}
	}
	else {
		tree[node].min = tree[node].max = tree[node].lazy1 + tree[node].lazy2;
		tree[node].sum = (end - start + 1) * tree[node].min;
	
		if (start != end) {
			tree[node * 2].lazy1 = tree[node].lazy1;
			tree[node * 2].lazy2 = tree[node].lazy2; 
			tree[node * 2 + 1].lazy1 = tree[node].lazy1;
			tree[node * 2 + 1].lazy2 = tree[node].lazy2;
		}
	}

	tree[node].lazy1 = 0;
	tree[node].lazy2 = 0;
}

void add(int node, int start, int end, int left, int right, int c){
	propagate(node, start, end);
	if (right < start || end < left) return;
	if (left <= start && end <= right) {
		tree[node].lazy1 = c;
		propagate(node, start, end);
		return;
	}

	int mid = (start + end) / 2;

	add(node * 2, start, mid, left, right, c);
	add(node * 2 + 1, mid + 1, end, left, right, c);

	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int gauss(ll n) {
	return floor(sqrt(n));
}

void square(int node, int start, int end, int left, int right){
	propagate(node, start, end);
	if (right < start || end < left) return;
	if (left <= start && end <= right) {
		int min_g = gauss(tree[node].min), max_g = gauss(tree[node].max);
		if (min_g == max_g){
			tree[node].lazy2 = min_g;
			propagate(node, start, end);
			return;
		}
		else if (tree[node].min + 1 == tree[node].max){
			tree[node].lazy1 = min_g - tree[node].min;
			propagate(node, start, end);
			return;
		}
	}

	int mid = (start + end) / 2;

	square(node * 2, start, mid, left, right);
	square(node * 2 + 1, mid + 1, end, left, right);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right) {
	propagate(node, start, end);
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return tree[node].sum;

	int mid = (start + end) / 2;

	return query(node * 2, start, mid, left, right) + query(node * 2 + 1, mid + 1, end, left, right);
}

vector<int> A(MAX_N);

void init(int node, int start, int end) {
	if (start == end){
		tree[node] = Node(A[start], A[start], A[start]);
		return;
	}

	int mid = (start + end) / 2;
	init(node * 2, start, mid);
	init(node * 2 + 1, mid + 1, end);
	tree[node] = tree[node* 2] + tree[node * 2 + 1];
}

int main() {
	fastio;
	int T;
	cin >> T;

	while (T--) {
		int N, Q;
		cin >> N >> Q;
		for (int i = 1; i <= N; i++) cin >> A[i];

		init(1, 0, N);

		for (int i = 0; i < Q; i++) {
			int t, l, r, x;
			cin >> t >> l >> r;

			switch (t) {
				case 1: square(1, 0, N, l, r); break;
				case 2: cout << query(1, 0, N, l, r) << '\n'; break;
				case 3:	cin >> x; add(1, 0, N, l, r, x);
			}
		}
	}

}