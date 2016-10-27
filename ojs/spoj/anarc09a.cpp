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

int memo[2123][2123], tempo;
int seen[2123][2123], o[256];
char s[2123];

int solve(int i, int ct) {
	if(ct < 0) return 1e8;
	if(!s[i]) return ct? 1e8 : 0;
	int &r = memo[i][ct];
	if(seen[i][ct] == tempo) return r;
	seen[i][ct] = tempo;
	r = min(solve(i + 1, ct + o[s[i]]), 1 + solve(i + 1, ct + o['{' + '}' - s[i]]));
	return r;
}

int main() {
	o['}'] = -1;
	o['{'] = 1;
	int t = 0;
	while(scanf("%s", s) != EOF && s[0] != '-') {
		tempo++;
		printf("%d. %d\n", ++t, solve(0, 0));
	}
}
