#include <bits/stdc++.h>
using namespace std;
#define a first
#define b second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
vector<int> R;
vector<pii> P;

int memo[212][212];
int solve(int i, int p) {
	if(p == 0) return i < P.size()? INT_MIN : 0;
	if(i == P.size()) return p <= R.size()? R[p - 1] : INT_MIN;
	int &r = memo[i][p];
	if(r != -1) return r;
	r = INT_MIN;
	for(int j = i; j < P.size() && P[j].a < P[i].b; j++)
		r = max(r, P[i].b - P[j].a + solve(j + 1, p - 1));
	return r;
}
void build(int i, int p) {
	if(p == 0) return;
	if(i == P.size()) { puts("plus some"); return; }
	for(int j = i; j < P.size() && P[j].a < P[i].b; j++)
		if(solve(i, p) == P[i].b - P[j].a + solve(j + 1, p - 1)) {
			for(int k = i; k <= j; k++) printf("(%d, %d)\n", P[k].a, P[k].b);
			puts("----------");
			build(j + 1, p - 1);
			return;
		}
}

pii p[212];

int main() {
	int i, n, pp;
	while(scanf("%d %d", &n, &pp) != EOF) {
		for(i = 0; i < n; i++) scanf("%d %d", &p[i].a, &p[i].b);
		sort(p, p + n, [](pii a, pii b) { if(a.a != b.a) return a.a < b.a; return a.b < b.b; });
		P.clear(); R.clear();
		P.pb(p[0]);
		for(i = 1; i < n; i++) {
			while(!P.empty() && p[i].b <= P.back().b) {
				R.pb(P.back().b - P.back().a); P.pop_back();
			}
			P.push_back(p[i]);
		}
		sort(R.begin(), R.end(), greater<int>());
		for(i = 1; i < R.size(); i++) R[i] += R[i - 1];
		memset(memo, -1, sizeof memo);
		printf("%d\n", solve(0, pp));
		//build(0, pp);
	}
}
