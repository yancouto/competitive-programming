#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
using namespace std;
typedef long long ll;
const int MAX = 100009;
int n, k, m;
int a[MAX];
int cs[MAX];
vector<int> evs[MAX];
int nn;

void calc_cs() {
	multiset<int> s;
	nn = 0;
	for(int i = 0; i < n; i++) {
		for(int v : evs[i])
			if(v > 0)
				s.insert(v);
			else
				s.erase(s.find(-v)); // erase one
		evs[i].clear();
		if(s.size()) {
			// memset(memo[nn], -1, sizeof(ll) * 502);
			a[nn] = -a[i];
			cs[nn++] = *s.begin(); // minimum
		}
	}
}

ll memo[MAX][502];
// ll solve(int i, int money) {
// 	if(i == nn) return 0;
// 	ll &m = memo[i][money];
// 	if(m != -1) return m;
// 	ll sol = solve(i + 1, money);
// 	if(money >= cs[i]) sol = max(sol, solve(i + 1, money - cs[i]) + a[i]);
// 	return m = sol;
// }

void solve_bottom_up() {
	int i, j;
	memset(memo[nn], 0, sizeof(ll) * (k + 2));
	for(i = nn - 1; i >= 0; i--)
		for(j = 0; j <= k; j++) {
			memo[i][j] = memo[i + 1][j];
			if(j >= cs[i])
				memo[i][j] = max(memo[i][j], memo[i + 1][j - cs[i]] + a[i]);
		}
}


int main() {
	int t, i, l, r, c;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d %d", &n, &k, &m);
		ll all = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			all += a[i];
		}
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &l, &r, &c);
			evs[l - 1].push_back(c);
			evs[r].push_back(-c);
		}
		calc_cs();
		solve_bottom_up();
		printf("%lld\n", all + memo[0][k]);
	}
	return 0;
}