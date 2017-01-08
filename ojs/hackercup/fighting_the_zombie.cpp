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

double memo[412][21][21];
bool seen[412][21][21];
double atleast(int val, int d, int left) {
	if(val <= 0) return 1;
	if(val >= 412) return 0;
	if(left == 0) return 0;
	double &r = memo[val][d][left];
	if(seen[val][d][left]) return r;
	seen[val][d][left] = 1;
	r = 0;
	for(int x = 1; x <= d; x++)
		r += (1. / d) * atleast(max(val - x, 0), d, left - 1);
	return r;
}

char at[110];
int main() {
	int h, s, i;
	for_tests(t, tt) {
		scanf("%d %d", &h, &s);
		double best = 0;
		while(s--) {
			scanf("%s", at);
			for(i = 0; at[i] != 'd'; i++);
			at[i] = 0;
			int qt = atoi(at);
			int j = i;
			for(i++; isdigit(at[i]); i++);
			char c = at[i];
			at[i] = 0;
			int d = atoi(at + j + 1);
			int nh = h;
			if(c == '+') nh -= atoi(at + i + 1);
			else nh += atoi(at + i + 1);
			best = max(best, atleast(nh, d, qt));
		}
		printf("Case #%d: %.10f\n", tt, best);
	}
}
