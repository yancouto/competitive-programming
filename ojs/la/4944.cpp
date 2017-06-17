#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }

inline int id(int l, int r) {
	if(l == r) return l;
	return l + r + 2;
}

inline ll up(char c) {
	if(!c) return 26;
	return 'z' - c;
}

inline ll down(char c) {
	if(!c) return 0;
	return c - 'a';
}

const int N = 1000009, K = 3;
char s[K][N];
int n;
int seen[6][N], tempo;
int memo[6][N];
ll solve(int l, int r, int i) {
	//printf("solve(%d, %d, %d)\n", l, r, i);
	if(i == n) return (l == r);
	ll ret = memo[id(l, r)][i];
	if(seen[id(l, r)][i] == tempo) return ret;
	seen[id(l, r)][i] = tempo;
	ret = 0;
	int qt = r - l + 1;
	char any = '?';
	int qqt = 0;
	for(int j = l; j <= r; j++) { if(s[j][i] != '?') any = s[j][i]; else qqt++; }
	bool can_eq = !!any || l == r;
	for(int j = l; j <= r; j++) if(s[j][i] != '?' && s[j][i] != any) can_eq = false;
	if(can_eq) ret += solve(l, r, i + 1) * ll(qqt == qt? 26 : 1);
	//printf("(%d, %d, %d) qt %d qqt %d\n", l, r, i, qt, qqt);
	if(qt == 3) {
		ll nx3 = mod(solve(0, 0, i + 1) * mod(solve(1, 1, i + 1) * solve(2, 2, i + 1)));
		ll nx01 = mod(solve(0, 1, i + 1) * solve(2, 2, i + 1));
		ll nx12 = mod(solve(0, 0, i + 1) * solve(1, 2, i + 1));
		//printf("%lld %lld %lld nxs\n", nx3, nx01, nx12);
		if(qqt == 3) {
			ret += 2600ll * nx3;
			ret += 325ll * (nx01 + nx12);
		} else if(qqt == 2) {
			if(s[0][i] != '?') {
				ll x = up(s[0][i]);
				ret += (x * (x - 1ll) / 2ll) * nx3;
				ret += (!!s[0][i]) * x * nx01;
				ret += x * nx12;
			} else if(s[1][i] != '?') {
				ret += ll(down(s[1][i])) * ll(up(s[1][i])) * nx3;
				ret += (!!s[0][i]) * ll(up(s[1][i])) * nx01;
				ret += ll(down(s[1][i])) * nx12;
			} else if(s[2][i] != '?') {
				ll x = down(s[2][i]);
				ret += (x * (x - 1ll) / 2ll) * nx3;
				ret += x * (nx01 + nx12);
			}
		} else if(qqt == 1) {
			if(s[0][i] == '?') {
				ret += ll(down(s[1][i])) * (s[2][i] > s[1][i]) * nx3;
				ret += (!!s[1][i]) * (s[2][i] > s[1][i]) * nx01;
				ret += ll(down(s[1][i])) * (s[2][i] == s[1][i]) * nx12;
			} else if(s[1][i] == '?') {
				ll x = s[2][i] - s[0][i] - 1;
				if(!s[2][i]) x = 0;
				else if(!s[0][i]) x = s[2][i] - 'a';
				ret += (s[2][i] > s[0][i]) * x * nx3;
				ret += (s[2][i] > s[0][i]) * (!!s[0][i]) * nx01;
				ret += (s[2][i] > s[0][i]) * (!!s[2][i]) * nx12;
			} else if(s[2][i] == '?') {
				ret += ll(up(s[1][i])) * (s[1][i] > s[0][i]) * nx3;
				ret += ll(up(s[1][i])) * (s[1][i] == s[0][i]) * nx01;
				ret += (s[1][i] > s[0][i]) * (!!s[1][i]) * nx12;
			}
		} else if(qqt == 0) {
			ret += (s[0][i] < s[1][i]) * (s[1][i] < s[2][i]) * nx3;
			ret += (s[0][i] == s[1][i]) * (s[1][i] < s[2][i]) * nx01;
			ret += (s[0][i] < s[1][i]) * (s[1][i] == s[2][i]) * nx12;
		}
	} else if(qt == 2) {
		ll nx = mod(solve(l, l, i + 1) * solve(r, r, i + 1));
		if(qqt == 0) ret += (s[r][i] > s[l][i]) * nx;
		else if(qqt == 2) ret += 325ll * nx;
		else if(s[l][i] == '?') ret += ll(down(s[r][i])) * nx;
		else if(s[r][i] == '?') ret += ll(up(s[l][i])) * nx;
	}
	return memo[id(l, r)][i] = mod(ret);
}


int main() {
	int i;
	for_tests(tn, tt) {
		for(i = 0; i < 3; i++) scanf("%s", s[i]);
		tempo++;
		n = max(strlen(s[0]), max(strlen(s[1]), strlen(s[2])));
		for(i = n - 1; i >= 0; i--) {
			solve(0, 0, i); solve(0, 1, i); solve(0, 2, i);
			solve(1, 1, i); solve(1, 2, i); solve(2, 2, i);
		}
		printf("%lld\n", solve(0, 2, 0));
	}
}
