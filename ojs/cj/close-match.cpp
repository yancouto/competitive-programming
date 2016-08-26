#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char c[30], j[20];
ll mn, mc, mj;

// ok 0 - eq, 1 - c big, 2 - j big
void solve(int i, int ok, ll C, ll J) {
	if(!c[i]) {
		if(abs(C - J) > mn) return;
		if(abs(C - J) == mn && C > mc) return;
		if(abs(C - J) == mn && C == mc && J >= mj) return;
		mn = abs(C - J);
		mc = C;
		mj = J;
		return;
	}
	ll NC = C * 10ll + ll(c[i] - '0'), NJ = J * 10ll + ll(j[i] - '0');
	if(c[i] == j[i] && c[i] == '?') {
		if(ok == 0) {
			solve(i + 1, 0, C * 10ll, J * 10ll);
			solve(i + 1, 1, C * 10ll + 1ll, J * 10ll);
			solve(i + 1, 2, C * 10ll, J * 10ll + 1ll);
		} else if(ok == 1) solve(i + 1, 1, C * 10ll, J * 10ll + 9ll);
		else solve(i + 1, 2, C * 10ll + 9ll, J * 10ll);
	} else if(c[i] != '?' && j[i] != '?') {
		if(ok) solve(i + 1, ok, NC, NJ);
		else if(c[i] > j[i]) solve(i + 1, 1, NC, NJ);
		else if(j[i] > c[i]) solve(i + 1, 2, NC, NJ);
		else solve(i + 1, 0, NC, NJ);
	} else if(c[i] == '?') {
		if(ok == 0) {
			solve(i + 1, 0, C * 10ll + ll(j[i] - '0'), NJ);
			if(j[i] < '9') solve(i + 1, 1, C * 10ll + ll(j[i] - '0' + 1), NJ);
			if(j[i] > '0') solve(i + 1, 2, C * 10ll + ll(j[i] - '0' - 1), NJ);
		} else if(ok == 1) solve(i + 1, 1, C * 10ll, NJ);
		else solve(i + 1, 2, C * 10ll + 9ll, NJ);
	} else /*j[i] == '?'*/ {
		if(ok == 0) {
			solve(i + 1, 0, NC, J * 10ll + ll(c[i] - '0'));
			if(c[i] < '9') solve(i + 1, 2, NC, J * 10ll + ll(c[i] - '0' + 1));
			if(c[i] > '0') solve(i + 1, 1, NC, J * 10ll + ll(c[i] - '0' - 1));
		} else if(ok == 1) solve(i + 1, 1, NC, J * 10ll + 9ll);
		else solve(i + 1, 2, NC, J * 10ll);
	}
}

void prn(ll m) {
	char frm[100];
	sprintf(frm, " %%0%dlld", strlen(c));
	printf(frm, m);
}

int main() {
	for_tests(t, tt) {
		scanf("%s %s", c, j);
		mn = LLONG_MAX;
		solve(0, 0, 0, 0);
		printf("Case #%d:", tt);
		prn(mc); prn(mj);
		putchar('\n');
	}
}
