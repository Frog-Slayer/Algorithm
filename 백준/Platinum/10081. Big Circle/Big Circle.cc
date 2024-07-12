#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

const int MAX_DIST = 800000000;
const int MAX_COORD_ABS = 10000;
int N;
int ans = MAX_DIST;
vector<pair<int, int>> v;

long long dist(pair<int, int> p1, pair<int, int> p2) {
	long long x_diff = p2.first - p1.first;	
	long long y_diff = p2.second - p1.second;	

	return x_diff * x_diff + y_diff * y_diff;
}

int pow(int a){
	return a * a;
}

long long divide_and_conquer(int start, int end){

	if (start == end) return MAX_DIST;

	long long min_dist = dist(v[start], v[end]);

	int mid = (start + end) / 2;
	long long left_min = divide_and_conquer(start, mid), right_min = divide_and_conquer(mid + 1, end);

	min_dist = min(min_dist, left_min);
	min_dist = min(min_dist, right_min);

	int sqrt_dist = sqrt(min_dist) + 1;
	
	pair<int, int> left_bound_pair = {v[mid].first - sqrt_dist, -MAX_COORD_ABS};
	pair<int, int> right_bound_pair = {v[mid].first + sqrt_dist, MAX_COORD_ABS};

	int left_bound = lower_bound(v.begin(), v.end(), left_bound_pair) - v.begin();
	left_bound = max(start, left_bound);

	int right_bound = lower_bound(v.begin(), v.end(), right_bound_pair) - v.begin();
	right_bound = min(end, right_bound);

	vector<pair<int, int>> cand;

	for (int i = left_bound; i <= right_bound; i++) {
		cand.emplace_back(v[i].second, v[i].first);
	}

	sort(cand.begin(), cand.end());

	for (int i = 0; i < cand.size(); i++) {
		for (int j = i + 1; j < cand.size(); j++) {
			if (pow(cand[j].first - cand[i].first) >= min_dist) break;
			min_dist = min(min_dist, dist(cand[i], cand[j]));
		}
	}

	return min_dist;
}

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);	
		v.emplace_back(x * 100, y * 100);
	}

	sort(v.begin(), v.end());

	double ans = divide_and_conquer(0, N - 1);

	printf("%f", sqrt(ans)/100);
	


}