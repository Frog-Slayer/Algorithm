#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define _USE_MATH_DEFINES

using namespace std;

struct Vector2 {
	long long x;
	long long y;
	double angle;

	Vector2() { x = 0, y = 0; }

	Vector2(long long _x, long long _y) {
		x = _x;
		y = _y;
		angle = atan2( _y, _x);
	}

	Vector2 operator+(const Vector2 &rhs) {
		return Vector2(x + rhs.x, y + rhs.y);	
	}

	Vector2 &operator+=(const Vector2 &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 operator-(const Vector2 &rhs) {
		return Vector2(x - rhs.x, y - rhs.y);	
	}

	Vector2 &operator-=(const Vector2 &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	bool operator<(const Vector2 &rhs) {
		return angle < rhs.angle;
	}

	long long magnitude(){
		return x * x + y * y;
	}
};

int N;
long long ans = 0;
vector<Vector2> v;

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		v.push_back(Vector2(x,y));
	}

	sort(v.begin(), v.end());

	int start = 0, end = 0;
	bool loop = true;
	Vector2 sum;

	sum = v[0];
	ans = sum.magnitude();

	while (loop) {
		// printf("(%d, %d)\n", start, end);
		end++;
		int end_mod = end % N;
		int cycle = end / N;

		while (v[end_mod].angle - v[start].angle + cycle * (2 * M_PI) > M_PI) {//180도 넘어 가면 볼 필요 없음
			// printf("- (%lld, %lld)(v[%d])", v[start].x, v[start].y, start);
			sum -= v[start++];
			// printf("= (%lld, %lld). magnitude = %lld\n", sum.x, sum.y, sum.magnitude());

			ans = max(ans, sum.magnitude());
			if (start == N) {
				loop = false;
				break;
			}
		}

		// printf("+ (%lld, %lld)(v[%d])", v[end_mod].x, v[end_mod].y, end_mod);
		sum += v[end_mod];

		// printf("= (%lld, %lld). magnitude = %lld\n", sum.x, sum.y, sum.magnitude());
		ans = max(ans, sum.magnitude());
	}

	
	printf("%lld", ans);
}