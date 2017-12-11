#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int c[10];

struct v3 {
	int v[3];
	int& operator[](int i) { return v[i]; }
};

int solve21(v3 v) {
	sort(v.v, v.v + 3);
	if(v[0] == 1)
		return min({c[1] + solve21({0, v[1], v[2]}), c[2] + min(solve21({0, v[1] - 1, v[2]}), solve21({0, v[1], v[2] - 1}))});
	return v[1] * min(2 * c[1], c[2]) + (v[2] - v[1]) * c[1];
}

int solve(v3 v) {
	sort(v.v, v.v + 3);
	if((v[0] + v[1] + v[2]) & 1) return c[1] + solve({v[0], v[1], v[2] - 1});
	int x = int(v[0] / 2) * 2;
	int ans = (x / 2) * c[6] + solve21({v[0] - x, v[1] - x, v[2] - x});
	if(v[2] <= v[0] + v[1]) {
		int k = (v[0] + v[1] - v[2]) / 2;
		ans = min(ans, k * c[6] + c[2] * ((v[0] + v[1] + v[2] - 6 * k) / 2));
	} else {
		ans = min(ans, c[2] * (v[0] + v[1]) + (v[2] - v[0] - v[1]) * c[1]);
	}
	return ans;
}

int solve3(v3 v) {
	sort(v.v, v.v + 3);
	int ans = solve(v);
	if(v[0] >= 1)
		ans = min(ans, c[3] + solve({v[0] - 1, v[1] - 1, v[2] - 1}));
	return ans;
}

int main() {
	for_tests(tn, tt) {
		int v[3], i;
		for(i = 0; i < 3; i++) scanf("%d", &v[i]);
		for(i = 1; i <= 3; i++) scanf("%d", &c[i]);
		c[2] = min(c[2], 2 * c[1]);
		c[3] = min({c[3], 3 * c[1], c[1] + c[2]});
		c[6] = min({2 * c[3], 3 * c[2], 6 * c[1]});
		printf("%d\n", solve3({v[0], v[1], v[2]}));
	}
}
